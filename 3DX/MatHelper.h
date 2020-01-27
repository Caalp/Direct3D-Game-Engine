#pragma once
#include <DirectXMath.h>

namespace dx = DirectX;

class MatHelper
{
	
public:
	 
	static float dot(const dx::XMFLOAT3& f1, const dx::XMFLOAT3& f2)
	{
		return ((f1.x*f2.x) + (f1.y*f2.y) + (f1.z*f2.z));
	}
	
	///<summary>
	/// Calculates reflection ray and loads into out
	///</summary>
	static void reflect(const dx::XMFLOAT3& f1, const dx::XMFLOAT3& f2,dx::XMFLOAT3& out)
	{
		dx::XMVECTOR t1 = dx::XMLoadFloat3(&f1);
		t1 = dx::XMVectorScale(t1, -1);
		dx::XMVECTOR t2 = dx::XMLoadFloat3(&f2);
		dx::XMVECTOR n;

		dx::XMVector4Normalize(t2);
		n = dx::XMVectorAdd(t1,dx::XMVectorMultiply({ -2,-2,-2 }, dx::XMVectorMultiply(dx::XMVector3Dot(t1, t2), t2)));
		dx::XMStoreFloat3(&out, n);
	}
	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}
	static dx::XMMATRIX inverseTranspose(const dx::FXMMATRIX xm)
	{
		dx::XMMATRIX temp = xm;
		temp.r[3] = dx::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		dx::XMVECTOR det = dx::XMMatrixDeterminant(temp);

		return dx::XMMatrixTranspose(dx::XMMatrixInverse(&det, temp));
	}
	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
	//static const float Infinity;
	//static const float Pi;
};