#pragma once
#include "Types.h"
#include "VertexBuffer.h"
#include "IndexBuff.h"

class Step;
class Graphics;
class RenderableComponent;
class Renderable;


class Job
{
public:
	Job(const Step& s, const Renderable& d);
	void Execute(Graphics& gfx);
private:
	const Renderable& m_renderable;
	const Step& m_step;
};

