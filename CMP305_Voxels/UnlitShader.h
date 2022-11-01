#pragma once
#include "DXF.h"

using namespace std;
using namespace DirectX;
class UnlitShader : public BaseShader
{
private:

public:
	UnlitShader(ID3D11Device* device, HWND hwnd);
	~UnlitShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
};

