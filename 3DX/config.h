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