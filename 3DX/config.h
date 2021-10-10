#pragma once
#include <iostream>
#include "Types.h"

#ifndef TORC_MAX_VERTEX_BUFFER_COUNT
	#define TORC_MAX_VERTEX_BUFFER_COUNT 4096
#endif

#ifndef TORC_MAX_INDEX_BUFFER_COUNT
	#define TORC_MAX_INDEX_BUFFER_COUNT 4096
#endif

#ifndef TORC_MAX_SHADER_COUNT
	#define TORC_MAX_SHADER_COUNT 256
#endif

#ifndef TORC_MAX_COMMAND_COUNT
#define TORC_MAX_COMMAND_COUNT 10000
#endif

#ifndef TORC_MAX_RENDER_TARGET_COUNT
	#define TORC_MAX_RENDER_TARGET_COUNT 8
#endif

#ifndef TORC_MAX_DEPTH_BUFFER_COUNT
	#define TORC_MAX_DEPTH_BUFFER_COUNT 8
#endif

#ifndef TORC_MAX_VERTEX_BUFFER_COUNT
#define TORC_MAX_VERTEX_BUFFER_COUNT 4 << 10
#endif

#ifndef TORC_MAX_INDEX_BUFFER_COUNT
#define TORC_MAX_INDEX_BUFFER_COUNT 4 << 10
#endif

#ifndef DEFINE_HANDLER(handler_name)
	#define DEFINE_HANDLE(handler_name)\
	struct handler_name { \
	inline uint16_t get() {return idx&0x0000ffff;}\
	uint32_t idx; };// index with first 16 bit as ref_count
#endif

// blend state
#define BS_ALPHA_BLEND 0
#define BS_ADDITIVE 1
#define BS_OPAQUE 2
#define BS_NONPREMULTIPLIED 3

// depth stencil state
#define DSS_NONE	0 << 2
#define DSS_DEFAULT 1 << 2
#define DSS_DEPTH_READ 2 << 2

// rasterizer state
#define RS_CULL_NONE 0 << 5
#define RS_CULL_CLOCKWISE 1 << 5
#define RS_CULL_COUNTER_CLOCKWISE 2 << 5
#define RS_WIREFRAME 3 << 5


// sampler state
#define SS_POINT_WRAP 0 << 7
#define SS_POINT_CLAMP 1 << 7
#define SS_LINEAR_WRAP 2 << 7
#define SS_LINEAR_CLAMP 3 << 7
#define SS_ANISOTROPIC_WRAP 4 << 7
#define SS_ANISOTROPIC_CLAMP 5 << 7

