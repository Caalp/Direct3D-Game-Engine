#pragma once
#include <iostream>
#include "Types.h"

#ifndef TORC_MAX_COMMAND_COUNT
#define TORC_MAX_COMMAND_COUNT 10000
#endif


#ifndef TORC_MAX_VERTEX_BUFFER_COUNT
#define TORC_MAX_VERTEX_BUFFER_COUNT 4 << 10
#endif

#ifndef TORC_MAX_INDEX_BUFFER_COUNT
#define TORC_MAX_INDEX_BUFFER_COUNT 4 << 10
#endif




#ifndef MAX_PS_COUNT
#define MAX_PS_COUNT 8
#endif

#ifndef MAX_VS_COUNT
#define MAX_VS_COUNT 8
#endif

#ifndef DEFINE_HANDLER(handler_name)
	#define DEFINE_HANDLER(handler_name)\
	struct handler_name { uint16_t idx; };
#endif

// blend state
#define BS_ALPHA_BLEND 0x0
#define BS_ADDITIVE 0x1
#define BS_OPAQUE 0x2
#define BS_NONPREMULTIPLIED 0x3

// depth stencil state
#define DSS_NONE 0x00
#define DSS_DEFAULT 0x10
#define DSS_DEPTH_READ 0x20

// rasterizer state
#define RS_CULL_NONE 0x000
#define RS_CULL_CLOCKWISE 0x100
#define RS_CULL_COUNTER_CLOCKWISE 0x200
#define RS_WIREFRAME 0x300


// sampler state
#define SS_POINT_WRAP 0x0000
#define SS_POINT_CLAMP 0x1000
#define SS_LINEAR_WRAP 0x2000
#define SS_LINEAR_CLAMP 0x3000
#define SS_ANISOTROPIC_WRAP 0x4000
#define SS_ANISOTROPIC_CLAMP 0x5000

