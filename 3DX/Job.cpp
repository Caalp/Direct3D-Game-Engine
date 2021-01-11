#include "Job.h"
#include "Drawable.h"
#include "DrawCallDispatch.h"
#include "Step.h"

Job::Job(const Step& s, const Drawable& d) :step(&s), drawable(&d)
{}

void Job::Execute(Graphics& gfx)
{
	
	drawable->Bind(gfx);
	step->Bind(gfx);
	step->Draw(gfx);
	//gfx.DrawIndexed(drawable.GetIndexCount());
}

