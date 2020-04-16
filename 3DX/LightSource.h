//#pragma once
//#include<Windows.h>
//#include<DirectXMath.h>
//
//namespace dx = DirectX;
//
//
//	struct DirectionalLight
//	{
//		DirectionalLight() { ZeroMemory(this, sizeof(this)); }
//
//		dx::XMFLOAT4 ambient;
//		dx::XMFLOAT4 diff;
//		dx::XMFLOAT4 specular;
//		dx::XMFLOAT3 dir;
//		float padding;
//	};
//
//
//	struct PointLight
//	{
//
//		PointLight() { ZeroMemory(this, sizeof(this)); }
//
//		dx::XMFLOAT4 ambient;
//		dx::XMFLOAT4 diff;
//		dx::XMFLOAT4 specular;
//
//		dx::XMFLOAT3 pos;
//		float range;
//
//		dx::XMFLOAT3 att;
//		float padding;
//
//
//
//	};
//
//	struct SpotLight
//	{
//		SpotLight() { ZeroMemory(this, sizeof(this)); }
//
//		dx::XMFLOAT4 ambient;
//		dx::XMFLOAT4 diff;
//		dx::XMFLOAT4 specular;
//
//		dx::XMFLOAT3 pos;
//		float range;
//
//		//kspot = max(-L,d,0)^s
//		dx::XMFLOAT3 dir;
//		float spot;
//
//		dx::XMFLOAT3 att;
//		float padding;
//
//	};
//
//	struct Material
//	{
//		Material() { ZeroMemory(this, sizeof(this)); }
//
//		dx::XMFLOAT4 ambient;
//		dx::XMFLOAT4 diff;
//		dx::XMFLOAT4 specular; // specular power shinyness
//		dx::XMFLOAT4 reflection;
//	};
//
