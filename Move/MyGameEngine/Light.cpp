#include "Light.h"

Light::~Light()
{

}


Light* Light::Create()
{
	D3DLIGHT9 lightState;
	ZeroMemory(&lightState, sizeof(lightState));

	lightState.Type = D3DLIGHT_DIRECTIONAL;

	lightState.Direction = D3DXVECTOR3(1, -1, 1);

	lightState.Diffuse.r = 1.0f;
	lightState.Diffuse.g = 1.0f;
	lightState.Diffuse.b = 1.0f;

	lightState.Ambient.r = 1.0f;
	lightState.Ambient.g = 1.0f;
	lightState.Ambient.b = 1.0f;


	g.pDevice->SetLight(0, &lightState);

	g.pDevice->LightEnable(0, TRUE);

	Light* light = new Light;
	return light;
}
