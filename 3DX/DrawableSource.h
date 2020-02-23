//#pragma once
//#include "DrawableBase.h"
//#include "Model.h"
//
//template<class T>
//class DrawableSource : public DrawableBase
//{
//protected:
//	bool isStaticallyBinded() const;
//	void AddBind(std::unique_ptr<Bindable> ubind);
//	void AddStaticBind(std::unique_ptr<Bindable> sBinds);
//private:
//	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept override
//	{
//		return staticBindable;
//	}
//private:
//	static std::vector<std::unique_ptr<Bindable>> staticBindable;
//};
//
//template<class T>
//inline bool DrawableSource<T>::isStaticallyBinded() const
//{
//	if (staticBindable.empty())
//	{
//		return false;
//	}
//	return true;
//}
//
//template<class T>
//inline void DrawableSource<T>::AddBind(std::unique_ptr<Bindable> ubind)
//{
//	Bindable.push_back(std::move(ubind));
//}
//
//template<class T>
//inline void DrawableSource<T>::AddStaticBind(std::unique_ptr<Bindable> sBinds)
//{
//	staticBindable.push_back(std::move(sBinds));
//}
//template<typename T>
//std::vector<std::unique_ptr<Bindable>> DrawableSource<T>::staticBindable;