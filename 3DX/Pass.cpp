#include "Pass.h"
#include "Bindable.h"
#include "Sink.h"

Pass::Pass(const std::string passName) : passName(passName)
{
}

void Pass::RegisterSink(std::unique_ptr<Sink> sinkingObject)
{
	//sinkingObject->SetPassName(passName);
	sinks.emplace_back(std::move(sinkingObject));
}

void Pass::RegisterSource(std::unique_ptr<Source> sourceObject)
{
	sources.emplace_back(std::move(sourceObject));
}


void Pass::SetSinkLinkage(std::string registeredSinkName, std::string targetName)
{
	for (const auto& elem : sinks)
	{
		
		if (elem->GetRegisteredName() == registeredSinkName)
		{
			// For now assume all global names will start with $. and rest the string
			// if targetName doesn't have $ at starting index than interpret is as others

			/*if (targetName[0] == '$')
			{

				elem->SetPassName("$");
				auto tName = [=](std::string s) -> std::string { std::string new_str;
				for (auto elem : s)
				{
					if (elem == '$' || elem == '.')
					{
						continue;
					}
					else
					{
						new_str += elem;
					}
				}
				return new_str; };
				elem->SetTargetName(tName(targetName));

			}
			else
			{*/

				elem->SetPassName(passName);
				elem->SetTargetName(targetName);
			//}
		}
	}
}

Source& Pass::GetSource(std::string name)
{
	for (const auto& so : sources)
	{
		if (so->GetName() == name)
		{
			return *so;
		}
	}
}

const Sink& Pass::GetSinkByName(std::string sinkName)
{
	for (auto& si : sinks)
	{
		if (si->GetRegisteredName() == sinkName)
		{
			return *si;
		}
	}
}


const std::vector<std::unique_ptr<Sink>>& Pass::GetSinks()
{
	return sinks;
	
}

const std::string Pass::GetPassName() const
{
	return passName;
}

