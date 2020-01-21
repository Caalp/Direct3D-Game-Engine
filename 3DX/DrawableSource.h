//#pragma once
//#include "DrawableBase.h"
//#include "Model.h"
//
//template<class T>
//class DrawableSource : public DrawableBase
//{
//protected:
//	bool isStaticallyBinded() const;
//	void AddBind(std::unique_ptr<Bindables> ubind);
//	void AddStaticBind(std::unique_ptr<Bindables> sBinds);
//private:
//	const std::vector<std::unique_ptr<Bindables>>& GetStaticBinds() const noexcept override
//	{
//		return staticBindables;
//	}
//private:
//	static std::vector<std::unique_ptr<Bindables>> staticBindables;
//};
//
//template<class T>
//inline bool DrawableSource<T>::isStaticallyBinded() const
//{
//	if (staticBindables.empty())
//	{
//		return false;
//	}
//	return true;
//}
//
//template<class T>
//inline void DrawableSource<T>::AddBind(std::unique_ptr<Bindables> ubind)
//{
//	bindables.push_back(std::move(ubind));
//}
//
//template<class T>
//inline void DrawableSource<T>::AddStaticBind(std::unique_ptr<Bindables> sBinds)
//{
//	staticBindables.push_back(std::move(sBinds));
//}
//template<typename T>
//std::vector<std::unique_ptr<Bindables>> DrawableSource<T>::staticBindables;