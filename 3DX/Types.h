#pragma once

#include <stdint.h>

typedef uint64_t U64;
typedef unsigned int U32;
typedef char Byte;
typedef unsigned char U8;
typedef unsigned short U16;



#include <memory>
template<typename T>
using Ptr = std::unique_ptr<T>;


template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;