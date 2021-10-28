#pragma once
#include <functional>
#include <list>

enum class ELoadPriority
{
	VeryHigh = 0u,
	High,
	Medium,
	Low,
	Count

};

class Loader
{
	typedef std::function<void()> CallBackFunc;
public:
	static Loader* GetInstance();
	void AddList(CallBackFunc init, CallBackFunc shutdown);
	void Init();
	void Shutdown();

private:
	std::list<std::pair<CallBackFunc, CallBackFunc>> m_loadQueue;
};