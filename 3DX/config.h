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



