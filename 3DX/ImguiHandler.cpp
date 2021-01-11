#include "ImguiHandler.h"
#include "Imgui\\imgui.h"

ImguiHandler::ImguiHandler()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
}

ImguiHandler::~ImguiHandler()
{
	ImGui::DestroyContext();
}
