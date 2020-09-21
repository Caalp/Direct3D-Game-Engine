#pragma once
#include <directxmath.h>
#include <memory>
typedef DirectX::XMFLOAT3 Vec3;
struct Transformation
{
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
	Transformation() = default;
	Transformation(const DirectX::XMMATRIX& transformXM)
	{
		transform = transformXM;
	}
	template<typename T>
	void Update(T object)
	{
		object.Update(0.05f);
	}

};
struct Position
{
	Position() = default;
	Vec3 position = { 0.0f,0.0f,0.0f };
	Position(Vec3 p): position(p){}
	template<typename T>
	void Update(T object)
	{
		
	}
};
struct Player
{

};
struct Velocity
{
	Velocity() = default;
	Vec3 velocity = { 0.0f,0.0f,0.0f };
	Velocity(Vec3 v) :velocity(v) {}

};
struct Rotation
{
	Vec3 rotation = { 0.0f,0.0f,0.0f };
	// x as pitch , y as yaw, z as roll
	Rotation() = default;
	Rotation(Vec3 rot) :rotation(rot) {}


};
// Camera is also entity however can be attached to the player as component

struct SolidObject
{


};