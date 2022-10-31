#include "App1.h"
#include <vector>
App1::App1()
{
	m_InstanceShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Load textures
	textureMgr->loadTexture(L"block", L"res/BlockTex.png");
	textureMgr->loadTexture(L"grass", L"res/grass.png");

	// Create Mesh object and shader object
	m_InstancedCube.reset( new InstancedCubeMesh(renderer->getDevice(), renderer->getDeviceContext(), 1));
	m_InstanceShader.reset(new InstanceShader(renderer->getDevice(), hwnd));
	m_LightShader.reset(new LightShader(renderer->getDevice(), hwnd));

	// Initialise light
	light.reset(new Light());
	light->setDiffuseColour(0.8f, 0.8f, 0.8f, 1.0f);
	light->setAmbientColour(0.1f, 0.1f,0.1f, 1.0f);
	light->setDirection(-0.578f, -0.578f, 0.1f);

	//Initialise Camera Position
	camera->setPosition(-16, 60, -15);
	camera->setRotation(25, 45, 0);

	BuildCubeInstances();
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}
void App1::BuildCubeInstances() {

	constexpr int width = 64;
	constexpr int maxCubes = width * width * width;

	vector<XMFLOAT3> positions;
	vector<XMFLOAT2> uvs;

	int instanceCount = 0;
	//Loop through our scalar field
	//Create two crossing sine waves and only draw the cubes that are under the "height" value
	for (int i = 0; i < maxCubes; i++) {
		const int x = i % width;
		const int y = ((i / width) % width);
		const int z = (i / (width * width));

		float y1 = sin((float)(x) / 8.0f);
		y1 += 1.0f;
		y1 *= 16.f;

		float y2 = sin((float)(z) / 4.0f);
		y2 += 1.0f;
		y2 *= 16.f;

		if (y < y1 && y < y2) {
			positions.push_back( XMFLOAT3(2.0f * x, 2.0f * y, 2.0f * z));
			if ((y+1 < y1 && y+1 < y2)) {
				//Is not on top				
				uvs.push_back(XMFLOAT2{ 0.5,0.0 });
			}
			else {
				//If it's high up, use the snow section of the texture
				if (y > 20)
					uvs.push_back(XMFLOAT2{ 0.0,0.5 });
				else
					uvs.push_back(XMFLOAT2{ 0.0,0.0 });
			}
			instanceCount++;
		}
	}

	m_InstancedCube->initBuffers(renderer->getDevice(), &(positions.front()), &(uvs.front()), instanceCount);
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	// Send geometry data, set shader parameters, render object with shader
	m_InstanceShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"block"), light.get());
	m_InstancedCube->sendDataInstanced(renderer->getDeviceContext());
	m_InstanceShader->renderInstanced(renderer->getDeviceContext(), m_InstancedCube->getIndexCount(), m_InstancedCube->GetInstanceCount());
	
	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("Camera Pos: (%.2f, %.2f, %.2f)", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	ImGui::Text("Rendering %i cubes", m_InstancedCube->GetInstanceCount());

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

