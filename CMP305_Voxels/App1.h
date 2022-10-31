// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "InstanceShader.h"
#include "LightShader.h"
#include "InstancedCubeMesh.h"
#include <memory>

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
	unique_ptr<InstanceShader> m_InstanceShader;
	unique_ptr<InstancedCubeMesh> m_InstancedCube;

	unique_ptr<Light> light;
};

#endif