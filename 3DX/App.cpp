#include "App.h"
#include "Box.h"
#include <random>
#include "Channels.h"
#include <Xinput.h>
#include <sstream>
#include "Events.h"
#include "StaticTimer.h"
#include <fstream>
#include "Imgui/imgui.h"

App::App() :
	wnd(1600, 1200, "Hello"),last_x(0),last_y(0),
	dirLight(wnd.gfx()),
	pointLight(wnd.gfx()),
	mPhi(1.5f*3.1415926535f),mTheta(1.5f*3.1415926535f),mRadius(80.0f)
	
{
	
	cam.SetCameraLens(0.25f*3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);


	
	spotLight.LinkTechnique(rg);
	pointLight.LinkTechnique(rg);
	chr.LinkTechnique(rg);
	box0.LinkTechnique(rg);
	//testCube.LinkTechnique(rg);
	floor.LinkTechnique(rg);
	box0.LinkTechnique(rgMirror);
	mirror.LinkTechnique(rgMirror);
	sky.LinkTechnique(rg);
	
}

App::~App()
{
	

}

int App::Go()
{
	
	timer.StartTimer();
	while (true)
	{
		if (const auto error_code = Window::ProcessMessages())
		{
			return *error_code;
		}
		timer.StopTimer();
		float b = timer.GetTime();
		float a = timer.GetTime() / 1000;

		wnd.gfx().BeginFrame();

		Update(a);
		
		wnd.gfx().EndFrame();
		
		

	}
}

void App::Update(float dt)
{

	
	// Xinput experiment code here
	static float alpha = dt*10.0f;
	if (alpha < 1.0f)
	{
		alpha -= dt;
	}
	
	
	//DWORD dwResult;
	//XINPUT_STATE state{0};
	//dwResult = XInputGetState(0, &state); // if 0 then connected

	//float LX = state.Gamepad.sThumbLX;
	//float LY = state.Gamepad.sThumbLY;
	//
	//float magnitude = sqrt(LX * LX + LY * LY);

	//float normalizedLX = LX / magnitude;
	//float normalizedLY = LY / magnitude;
	//std::ostringstream ss;
	//ss << normalizedLX << " " << normalizedLY<<std::endl;
	//std::string s(ss.str());
	//OutputDebugString(s.c_str());
	//XINPUT_VIBRATION vibration{0};
	//vibration.wLeftMotorSpeed = 65000;
	//XInputSetState(0, &vibration);
	

	static float v = 30.0f;
	float dtheta = 0.2f;

	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());
	spotLight.Update();
	pointLight.Update();
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
		
	if (wnd.kbd.KeyIsPressed('W'))
	{
		//printf("W pressed\n");
		cam.Walk(v*dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Walk(v*-dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Strafe(v*-dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Strafe(v*dt);
	}


	
	if (wnd.mouse.IsInWindow())
	{
		//NOTE: Left mouse button and imgui in intereacting fix!!!
		if (wnd.mouse.IsInWindow() && wnd.mouse.RightIsPressed())
		{

			float dx = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosX() - last_x));
			float dy = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosY() - last_y));

			cam.Pitch(dy);
			cam.Yaw(dx);
		}
		last_x = (float)wnd.mouse.GetPosX();
		last_y = (float)wnd.mouse.GetPosY();

	}

	chr.GetFinalTransforms("defaultAnim_0", animTimer);
	//chr.GetFinalTransforms("Spider_Armature|Attack", animTimer);
	//chr.GetFinalTransforms("Walk", 0.5f);
	//chr.GetFinalTransforms("Salute", animTimer);
	//chr.GetFinalTransforms("Aim", 0.9f);
	//chr.GetFinalTransforms("Human Armature|Jump", 0.0f);
	
	
	//chr.GetFinalTransforms("Run", animTimer);
	//chr.GetFinalTransforms("mixamo.com", 0.05f);
	//chr.GetFinalTransforms("defaultAnim_0", dt);
	chr.Update(wnd.gfx());
	//chr.UpdateXM();
	
	
	spotLight.Submit(channel1::defaultChannel);
	pointLight.Submit(channel1::defaultChannel);
	
	chr.Submit(channel1::defaultChannel);
	box0.Submit(channel1::defaultChannel);
	floor.Submit(channel1::defaultChannel);
	mirror.Submit(channel1::defaultChannel);
	sky.Submit(channel1::defaultChannel);
	//emgr->ProcessEvents();
	//testScene.UpdateTest(alpha);
	//testCube.Submit(channel1::defaultChannel); // only submitting this w/o linking technique causing vector error!!!
	
	

	
	rg.Execute(wnd.gfx());
	rgMirror.Execute(wnd.gfx());
	
	/*Reset back to default render target*/
	//wnd.gfx().pTarget->BindAsBuffer(wnd.gfx());


	/* Do Imgui stuff */
	if (wnd.gfx().IsImguiEnabled())
	{


		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		//if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			//window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}


		/*{
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			vMin.x += ImGui::GetWindowPos().x;
			vMin.y += ImGui::GetWindowPos().y;
			vMax.x += ImGui::GetWindowPos().x;
			vMax.y += ImGui::GetWindowPos().y;

			ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
		}*/

		//ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		//float windowWidth = (float)ImGui::GetWindowWidth();
		//float windowHeight = (float)ImGui::GetWindowHeight();


		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
				if (ImGui::MenuItem("New", "Ctrl+N"))
					return;
				//NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					return;
				//OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					return;
				//SaveSceneAs();

			//if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


		/*-----------------------------------------------------------------------------------------------------------*/

		//const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD"};
		//static int item_current_idx = 0;                    // Here our selection data is an index.
		//const char* combo_label = items[item_current_idx];
		//if (ImGui::BeginCombo("Combo Test", combo_label, ImGuiComboFlags_PopupAlignLeft))
		//{
		//	for (int n = 0; n < 4; n++)
		//	{
		//		const bool is_selected = (item_current_idx == n);
		//		if (ImGui::Selectable(items[n], is_selected))
		//			item_current_idx = n;

		//		// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
		//		if (is_selected)
		//			ImGui::SetItemDefaultFocus();
		//	}
		//	ImGui::EndCombo();
		//}

		//static bool showDemoWindow = true;
		//ImGui::ShowDemoWindow(&showDemoWindow);
		ImGui::Begin("Info");
		//ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / (1 / dt), 1 / dt);
		ImGui::End();
		ImGui::End();
		
		//wnd.gfx().CreateViewport(width, height, maxDepth, minDepth, topXPos, topYPos);

		ImGui::Begin("AnimSpeed");

		ImGui::SliderFloat("dt", &animTimer, 0.0f, 2.0f, "%.5f", 1.0f);

		ImGui::End();
	}
	
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	//HRESULT hr = wnd.gfx().pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
	//	reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf()));
	
	//DX::ThrowIfFailed(hr);
	
	rg.Reset();
	rgMirror.Reset();
	
	
	
}
