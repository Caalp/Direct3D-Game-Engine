#pragma once
#include <vector>

/* Sigleton class to handle basic imgui functionalities */
class ImguiHandler
{
	// Pointer to class instance 
	typedef void* INSTANCE_PTR;
	// Function pointer to the function which will call member function with use of class instance
	typedef void(*IMGUI_FUNCTION)(INSTANCE_PTR);
	// pair that will store instance and the member function
	using funcPair = std::pair<INSTANCE_PTR, IMGUI_FUNCTION>;
	

	// Static function to return the member function
	template<class C, void (C::*Function)()>
	static inline void CreateFuncPair(INSTANCE_PTR instance)
	{
		return (static_cast<C*>(instance)->*Function)();
	}

	// Static function to return the free function
	template<void (*Function)()>
	static inline void CreateFuncPair(INSTANCE_PTR instance)
	{
		return Function();
	}

private:

	ImguiHandler();
	~ImguiHandler();
public:

	static ImguiHandler& GetInstance();
	// Callback function template for member functions
	template<class C, void (C::* Function)()>
	void BindCallback(C* instance)
	{
		funcPair myFuncPair;

		myFuncPair.first = instance;
		myFuncPair.second = &CreateFuncPair<C, Function>;


		imguiFuncCallbacks.push_back(myFuncPair);
		//printf("Binding member function pointer...\n");
		return;
	}

	// Callback function template for free functions
	template<void (*Function)()>
	void BindCallback()
	{
		funcPair myFuncPair;

		myFuncPair.first = nullptr;
		myFuncPair.second = &CreateFuncPair<Function>;


		imguiFuncCallbacks.push_back(myFuncPair);

		return;
	}

	void ProcessImguiCalls();
	void EnableImgui();
	void DisableImgui();
	bool IsImguiEnabled();
	void EnableDockspace();
private:
	bool imguiEnabled = true;
	std::vector<funcPair> imguiFuncCallbacks;

};