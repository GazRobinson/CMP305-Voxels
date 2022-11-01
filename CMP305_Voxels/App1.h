// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include <wrl/client.h>
#include <memory>

#include "InstanceShader.h"
#include "UnlitShader.h"
#include "InstancedCubeMesh.h"
#include "QuadMeshT.h"
#include "WritableTexture.h"

using std::unique_ptr;

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	void BuildCubeInstances();

private:
	unique_ptr<InstanceShader>		m_InstanceShader;
	unique_ptr<UnlitShader>			m_UnlitShader;

	unique_ptr<InstancedCubeMesh>	m_InstancedCube;
	unique_ptr<QuadMeshT>			m_Quad;

	unique_ptr<Light>				light;

	unique_ptr<WritableTexture>		m_Texture;

};

#endif