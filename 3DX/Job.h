#pragma once

class Step;
class Graphics;
struct Renderable;

class Job
{
public:

	Job(const Step& s, const Renderable& d);
	void Execute(Graphics& gfx);
private:
	const Renderable* const m_Renderable;
	const Step* step;
};