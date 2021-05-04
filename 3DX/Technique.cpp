#include "Technique.h"
#include "Drawable.h"

#include "RenderGraph.h"
#include "Components.h"

Technique::Technique(std::string graphName,std::string techName, bool status) : m_TargetGraphName(graphName),techniqueName(techName), isActive(status)
{
}

Technique::Technique(std::string graphName, std::string techName, size_t techChannel, bool status): m_TargetGraphName(graphName), techniqueName(techName), techniqueChannel(techChannel), isActive(status)
{

}

void Technique::Link(RenderGraph& rg)
{
	
		for (auto& s : steps)
		{
			if (s.isLinked() == false)
			{
				s.Link(rg);
			}
			
			
		}
	

}



void Technique::Submit(Renderable& d, size_t channel)
{
	if (isActive && ((techniqueChannel & channel) != 0))
	{
		for (auto& s : steps)
		{

			s.Submit(d);

		}
	}
}


void Technique::Deactivate()
{
	isActive = false;
}

void Technique::SetTechID(uint32_t id)
{
	techID = id;
}

uint32_t Technique::GetTechID() const
{
	return techID;
}

void Technique::AddStep(Step& step)
{
	//assert(this->step == nullptr);
	steps.push_back(step);
}

std::string Technique::GetName() const
{
	return techniqueName;
}

