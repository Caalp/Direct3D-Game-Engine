#pragma once

class Drawable;
class Step;
class Graphics;

class Job
{
public:
	Job(const Step& s, const Drawable& d);
	void Execute(Graphics& gfx);
private:
	const Drawable* const drawable;
	const Step* step;
};