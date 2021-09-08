#include "Technique.h"
#include "Drawable.h"

#include "RenderGraph.h"
#include "RenderableComponent.h"

Technique::Technique(std::string graphName,std::string techName, bool status) : m_targetGraphName(graphName),techniqueName(techName), isActive(status)
{
}

Technique::Technique(std::string graphName, std::string techName, size_t techChannel, bool status): m_targetGraphName(graphName), techniqueName(techName), techniqueChannel(techChannel), isActive(status)
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



void Technique::Submit(Renderable& rd, size_t channel)
{
	if (isActive && ((techniqueChannel & channel) != 0))
	{
		for (auto& s : steps)
		{

			s.Submit(rd);

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

std::string Technique::GetTargetGraphName() const
{
	return m_targetGraphName;
}

