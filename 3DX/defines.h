#pragma once
#include "config.h"


DEFINE_HANDLE(VertexBufferHandle)
DEFINE_HANDLE(IndexBufferHandle)
DEFINE_HANDLE(VertexLayoutHandle)
DEFINE_HANDLE(ConstantBufferHandle)
DEFINE_HANDLE(ShaderHandle)
DEFINE_HANDLE(RenderTargetHandle)
DEFINE_HANDLE(DepthBufferHandle)
DEFINE_HANDLE(TextureHandle)
DEFINE_HANDLE(SamplerHandle)


struct RenderDrawInfo
{
	DepthBufferHandle dph;
	ShaderHandle ps;
	ShaderHandle vs;
	ConstantBufferHandle cb;

	// RenderTargetHandle
	// renderState RS, DSS, SS, BS
	// 
	//void* command;

};