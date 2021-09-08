#pragma once
#include <DirectXMath.h>
#include <cstdlib>


namespace dx = DirectX;
const float Pi = 3.1415926535f;
#define XM_PI               3.141592654f
#define XM_2PI              6.283185307f

namespace MathUtils
{
	inline DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& r, const DirectX::XMFLOAT3& l)
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&r);
		DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&l);
		DirectX::XMVECTOR result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMFLOAT3 resultFloat3;

		DirectX::XMStoreFloat3(&resultFloat3, result);

		return resultFloat3;
	}
	inline DirectX::XMFLOAT2 operator+(const DirectX::XMFLOAT2& r, const DirectX::XMFLOAT2& l)
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat2(&r);
		DirectX::XMVECTOR v2 = DirectX::XMLoadFloat2(&l);
		DirectX::XMVECTOR result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMFLOAT2 resultFloat2;

		DirectX::XMStoreFloat2(&resultFloat2, result);

		return resultFloat2;
	}
	inline	DirectX::XMFLOAT2 operator*(float scaler, const DirectX::XMFLOAT2& l)
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat2(&l);
		DirectX::XMVECTOR resultVec = DirectX::XMVectorScale(v1, scaler);

		DirectX::XMFLOAT2 resultFloat2;
		DirectX::XMStoreFloat2(&resultFloat2, resultVec);

		return resultFloat2;

	}

	inline	DirectX::XMFLOAT3 operator*(float scaler, const DirectX::XMFLOAT3& l)
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&l);
		DirectX::XMVECTOR resultVec = DirectX::XMVectorScale(v1, scaler);

		DirectX::XMFLOAT3 resultFloat3;
		DirectX::XMStoreFloat3(&resultFloat3, resultVec);

		return resultFloat3;

	}
	

		static float dot(const dx::XMFLOAT3& f1, const dx::XMFLOAT3& f2)
		{
			return ((f1.x * f2.x) + (f1.y * f2.y) + (f1.z * f2.z));
		}
		static float randF()
		{
			return (float)(rand()) / (float)32767;
		}
		static float randF(float a, float b)
		{
			return a + randF() * (b - a);
		}
		static DirectX::XMFLOAT3 normalize(const DirectX::XMFLOAT3& xmf)
		{
			DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&xmf);


			DirectX::XMVECTOR normalized = DirectX::XMVector3Normalize(v1);

			DirectX::XMFLOAT3 resultFloat3;

			DirectX::XMStoreFloat3(&resultFloat3, normalized);

			return resultFloat3;
		}

		static float AngleFromXY(float x, float y)
		{
			float theta = 0.0f;

			// Quadrant I or IV
			if (x >= 0.0f)
			{
				// If x = 0, then atanf(y/x) = +pi/2 if y > 0
				//                atanf(y/x) = -pi/2 if y < 0
				theta = atanf(y / x); // in [-pi/2, +pi/2]

				if (theta < 0.0f)
					theta += 2.0f * Pi; // in [0, 2*pi).
			}

			// Quadrant II or III
			else
				theta = atanf(y / x) + Pi; // in [0, 2*pi).

			return theta;
		}
		///<summary>
		/// Calculates reflection ray and loads into out
		///</summary>
		static void reflect(const dx::XMFLOAT3& f1, const dx::XMFLOAT3& f2, dx::XMFLOAT3& out)
		{
			dx::XMVECTOR t1 = dx::XMLoadFloat3(&f1);
			t1 = dx::XMVectorScale(t1, -1);
			dx::XMVECTOR t2 = dx::XMLoadFloat3(&f2);
			dx::XMVECTOR n;

			dx::XMVector4Normalize(t2);
			n = dx::XMVectorAdd(t1, dx::XMVectorMultiply({ -2,-2,-2 }, dx::XMVectorMultiply(dx::XMVector3Dot(t1, t2), t2)));
			dx::XMStoreFloat3(&out, n);
		}
		static DirectX::XMFLOAT3 CrossXMFloat3(const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
		{
			DirectX::XMFLOAT3 result;
			result.x = (v1.y * v2.z) - (v1.z * v2.y);
			result.y = (v1.z * v2.x) - (v1.x * v2.z);
			result.z = (v1.x * v2.y) - (v1.y * v2.x);

			return result;
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

		// This function can be stored somewhere else
		
	
}

