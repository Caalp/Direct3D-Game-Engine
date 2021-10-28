#include "Loader.h"





Loader* Loader::GetInstance()
{
	static Loader loader;
	return &loader;
}

void Loader::AddList(CallBackFunc init, CallBackFunc shutdown)
{
	m_loadQueue.push_back(std::make_pair(init, shutdown));
}

void Loader::Init()
{
	for (auto& e : m_loadQueue)
	{
		e.first();
	}
}

void Loader::Shutdown()
{
	for (auto& e : m_loadQueue)
	{
		e.second();
	}
}
