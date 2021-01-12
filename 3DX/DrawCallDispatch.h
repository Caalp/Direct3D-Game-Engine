#pragma once
#include "Graphics.h"

class IBackendDispatch
{

public:
	
	IBackendDispatch() = default;
	virtual void Draw(Graphics& gfx) const = 0;
	virtual ~IBackendDispatch() = default;
};


class DrawIndexed : public IBackendDispatch
{
public:
	DrawIndexed() = default;
	DrawIndexed(unsigned int startIndex, unsigned int indexCount) : mStartIndex(startIndex), mIndexCount(indexCount)
	{
		m_vertexBaseIndex = 0;
	}
	DrawIndexed(uint32_t indexCount, uint32_t startIndex, int vertexBaseIndex ) : mStartIndex(startIndex), mIndexCount(indexCount),m_vertexBaseIndex(vertexBaseIndex)
	{

	}
	
	virtual void Draw(Graphics& gfx)const  override
	{
		gfx.DrawIndexed(mIndexCount,mStartIndex,m_vertexBaseIndex);
	}

private:
	unsigned int mStartIndex;
	unsigned int mIndexCount;
	int m_vertexBaseIndex;
};

class _Draw: public IBackendDispatch
{
public:
	_Draw() = default;

	_Draw(uint32_t vertexCount, uint32_t vertexStartIndex) :m_vertexCount(vertexCount),m_vertexStartIndex(vertexStartIndex)
	{

	}
	virtual void Draw(Graphics& gfx)const  override
	{
		gfx.Draw(m_vertexCount, m_vertexStartIndex);
	}

private:
	unsigned int m_vertexCount;
	unsigned int m_vertexStartIndex;
	

};


