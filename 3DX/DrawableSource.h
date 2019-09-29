#pragma once
#include "DrawableBase.h"

template<class T>
class DrawableSource : public DrawableBase
{
public:
	bool isBindsEmpty() const;
	void AddToBinds(std::unique_ptr<Bindables> ubind);
	void AddToStaticBind(std::unique_ptr<Bindables> sBinds);
	
protected:
	const std::vector<unique_ptr<Bindables>>& GetStaticBindables()
	{
		if (!isBindsEmpty())
		{
			return staticBinds;
		}
	}
protected:
	static std::vector<std::unique_ptr<Bindables>>  staticBinds;

};

template<class T>
inline bool DrawableSource<T>::isBindsEmpty() const
{
	if (staticBinds.empty())
	{
		return false;
	}
	return true;
}

template<class T>
inline void DrawableSource<T>::AddToBinds(std::unique_ptr<Bindables> ubind)
{
	staticBinds.push_back(std::move(ubind));
}

template<class T>
inline void DrawableSource<T>::AddToStaticBind(std::unique_ptr<Bindables> sBinds)
{
	   
}
