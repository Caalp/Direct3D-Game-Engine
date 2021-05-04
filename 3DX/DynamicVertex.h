#pragma once
#include "Bindable.h"
#include <vector>
#include <iostream>
// Element types
//Position3D
//Position2D
//Float

#define Define_Vertex_Elements\
	X(Position2D)\
	X(Position3D)\
	X(TextureCoord2D)\
	X(TextureCoord3D)\
	X(Float)\
	X(Normal)\
	X(BoneIndices)\
	X(BoneWeights)
using namespace DirectX;


namespace dvbuff
{
	enum ElementType
	{
#define X(elm) elm,
		Define_Vertex_Elements
#undef x
	};
	class VertexLayout
	{
	public:
		

#pragma region ElementDesc
		template<ElementType> struct ElementDesc {};

		template<> struct ElementDesc<TextureCoord2D>
		{
			using type = XMFLOAT2;
			static constexpr const char* semanticName = "TextureCoord";
			static constexpr const size_t format = DXGI_FORMAT_R32G32_FLOAT;

		}; 
		template<> struct ElementDesc<TextureCoord3D>
		{
			using type = XMFLOAT3;
			static constexpr const char* semanticName = "TextureCoord";
			static constexpr const size_t format = DXGI_FORMAT_R32G32B32_FLOAT;

		};
		template<> struct ElementDesc<BoneIndices>
		{
			using type = XMFLOAT4;
			static constexpr const char* semanticName = "BoneIndices";
			static constexpr const size_t format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		};
		template<> struct ElementDesc<BoneWeights>
		{
			using type = XMFLOAT4;
			static constexpr const char* semanticName = "BoneWeights";
			static constexpr const size_t format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		};
		template<> struct ElementDesc<Position2D>
		{
			using type = XMFLOAT2;
			static constexpr const char* semanticName = "Position2D";
			static constexpr const size_t format = DXGI_FORMAT_R32G32_FLOAT;

		};

		template<> struct ElementDesc<Float>
		{
			using type = FLOAT;
			static constexpr const char* semanticName = "Float";
			static constexpr const size_t format = DXGI_FORMAT_R32_FLOAT;

		};
		template<> struct ElementDesc<Position3D>
		{
			using type = XMFLOAT3;
			static constexpr const char* semanticName = "Position"; // reflected to the shader
			static constexpr const size_t format = DXGI_FORMAT_R32G32B32_FLOAT;
		};
		template<> struct ElementDesc<Normal>
		{
			using type = XMFLOAT3;
			static constexpr const char* semanticName = "Normal"; // reflected to the shader
			static constexpr const size_t format = DXGI_FORMAT_R32G32B32_FLOAT;
		};

#pragma endregion

		VertexLayout() = default;

		class Element
		{
			friend class VertexLayout;
			
		public:
			Element(ElementType type, size_t offset) : mElemType(type), mOffset(offset)
			{

			}
			const size_t GetFormat() const;

			const auto GetType() const
			{
				return mElemType;
			}
			const size_t GetOffset() const
			{
				return mOffset;
			}

			const char* GetSemanticName() const
			{	
				return Solve<NameLookUp>(mElemType);
			}
			
		private:
			ElementType mElemType;
			size_t mOffset;
		};

		/*------------------------------------------------------------*/
	    inline size_t Size() const
		{
			return mElems.size();
		}
		template<template<ElementType> class F, typename... Args>
		static constexpr auto Solve(ElementType elem, Args&&... args)
		{
			switch (elem)
			{
				#define X(el) case el: return F<el>::Exec(std::forward<Args>(args)...);
				Define_Vertex_Elements
				#undef X
			}
			
			//assert("Invalid Type ", false);
		}
		template<ElementType type>
		struct NameLookUp
		{
			static constexpr auto Exec() noexcept
			{

				return VertexLayout::ElementDesc<type>::semanticName;
			}
		};
		template<ElementType type>
		struct SizeLookUp
		{
			static constexpr auto Exec() noexcept
			{

				return sizeof(VertexLayout::ElementDesc<type>::type);
			}
		};
		template<ElementType type>
		struct ElemLookUp
		{
			static constexpr auto Exec() noexcept
			{
				//return VertexLayout::ElementDesc<type;
			}
		};
		inline ElementType GetType(int idx) const noexcept
		{
			return mElems[idx].mElemType;
		}
		static constexpr size_t SizeOf(ElementType elem)
		{
			
			return Solve<SizeLookUp>(elem);
		}

		uint32_t GetSizeInBytes() const
		{
			uint32_t size = 0;
			for (const auto& e : mElems)
			{
				size += SizeOf(e.mElemType);
			}
			return size;
		}
		static constexpr auto GetElemDesc(ElementType elem)
		{
			return Solve<ElemLookUp>(elem);
		}
		template<ElementType type>
		constexpr VertexLayout& Add()
		{
			
			size_t offset = (mElems.size() == 0u) ? 0u : mElems.back().mOffset + SizeOf(mElems.back().mElemType);
			mElems.emplace_back(type, offset);
			return *this;
			
		}
		size_t GetOffset(ElementType e)
		{
			for (const auto& el : mElems)
			{
				if (el.mElemType == e)
				{
					return el.mOffset;
				}
			}
			return -1;
		}
		 inline bool Has(ElementType elem) const
		{
			for (const auto& e : mElems)
			{
				if (e.mElemType == elem)
				{
					return true;
				}
			}
			return false;
		}
	public:
		std::vector<Element> mElems;

	};

	// Use this as a proxy type
	class Vertex
	{

	public:
		Vertex(char* data, VertexLayout& vLayout) : mVertexLayout(vLayout),mData(data)
		{}
		~Vertex() = default;
		
		template<ElementType elemType, typename T>
		void SetElem(T elem)
		{
			

		}
		
		template<ElementType ElemType, typename T>
		void Set(T elem)
		{
			//using T = typename VertexLayout::ElementDesc<ElemType>::type;
			auto e = reinterpret_cast<T*>(mData + mVertexLayout.GetOffset(ElemType));
			std::memcpy(e, &elem, sizeof(T));
		}
		//template<ElementType El = Position3D>
		VertexLayout::ElementDesc<Position3D>::type& operator[](int idx)
		{
			using T = typename VertexLayout::ElementDesc<Position3D>::type;
			return *reinterpret_cast<T*>(mData + mVertexLayout.GetOffset(Position3D));
			
		}
		template<ElementType ElemType>
		constexpr auto Get()
		{
			using T = typename VertexLayout::ElementDesc<ElemType>::type;
			if (mVertexLayout.Has(ElemType))
			{
				return reinterpret_cast<T*>(mData + mVertexLayout.GetOffset(ElemType));
			}
			return reinterpret_cast<T*>(nullptr);

		}
	public:
		VertexLayout& mVertexLayout;
		char* mData;

	};

	class VertexBuffer
	{
	public:
		VertexBuffer(VertexLayout& vl) : mVertexLayout(vl)
		{}
		~VertexBuffer() = default;

		Vertex operator[] (int idx)
		{

			return Vertex{&mData[idx* mVertexLayout.GetSizeInBytes()],mVertexLayout};
			//return Vertex{mData.data(),mVertexLayout};
		}

		// User only can push if elements in the container have same type
		template<ElementType elemType,typename T>
		void PushBack(T elem)
		{
		
			assert(mVertexLayout.GetSizeInBytes() == sizeof(T) && "[WARN]-PushBack on DynamicVertex can be performed if stream has same type of element.");

			size_t size = mData.size();
			size_t elemSize = VertexLayout::SizeOf(elemType);
		
			mData.resize(size + elemSize);
			size = mData.size();
			std::memmove(&mData[size - elemSize], &elem, sizeof(T));
		}

		template<ElementType elemType,typename T>
		void Insert(size_t idx,T elem)
		{
		}
		void Resize(int size)
		{
			mData.resize(size);
		}
	
		size_t GetVertexSizeInBytes()
		{
			return mVertexLayout.GetSizeInBytes();
		}
		UINT SizeInBytes()
		{
			return mData.size();
		}
		auto Data()
		{
			return mData.data();
		}
	private:
		VertexLayout& mVertexLayout;
		std::vector<char> mData;
	};
}

