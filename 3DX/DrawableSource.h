#pragma once
#include "DrawableBase.h"

template<class T>
class DrawableSource : public DrawableBase
{
	
protected:
	bool isBindsEmpty() const;
	void AddToBinds(std::unique_ptr<Bindables> ubind);
	void AddToStaticBind(std::unique_ptr<Bindables> sBinds);
	
protected:
	const std::vector<std::unique_ptr<Bindables>>& GetStaticBindables()
	{
		
			return staticBinds;
		
		
	}
protected:
	
	static std::vector<std::unique_ptr<Bindables>> staticBinds;

};
template<class T>
std::vector < std::unique_ptr<Bindables>> DrawableSource<T>::staticBinds;

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
	staticBinds.push_back(std::move(sBinds));
}
