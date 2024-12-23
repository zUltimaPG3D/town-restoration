#include "ImGuiStuff.h"
#ifndef MENU
#define MENU

namespace Menu {

	ImVec4 color = ImVec4(1, 1, 1, 1);

	void DrawMenu() {
		static bool show_demo_window = false;
		static bool show_another_window = false;
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		std::string text = "FPS: " + std::to_string((int)io.Framerate);
		draw_list->AddText(ImVec2(6, 6), ImColor(1.0f, 1.0f, 1.0f, 1.0f), text.c_str());

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Town Restoration");

			// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			if (ImGui::CollapsingHeader("Information and Links", ImGuiTreeNodeFlags_DefaultOpen)) 
			{
				if (ImGui::Button("GitHub Repo")) OpenURL("https://github.com/zUltimaPG3D/town-restoration/");
				if (ImGui::Button("Community Discord")) OpenURL("https://discord.gg/keB3RNumVt");
                ImGui::Text("* town-restoration by sSAR");
                ImGui::Text("* toro-webserver by sSAR");
                ImGui::Text("  - partially based on puzzle by synzr");
			}

			ImGui::Checkbox("Software Cursor Rendering", &io.MouseDrawCursor);

			if (ImGui::CollapsingHeader("Misc. features"))
			{
                ImGui::BeginDisabled(SaveData == nullptr);
                if (ImGui::Button("Clear Data")) {
                    old_SaveDataClear(SaveData);
                }
                ImGui::EndDisabled();
				if (ImGui::Checkbox("Unlock FPS", &uncap_fps))
                {
                    if (uncap_fps) {
                        set_vSyncCount(0);
                        set_targetFrameRate(144);
                    }
                }
			}

			ImGui::End();
		}
	}

	void DrawImGui() {
		if (init && UnityEngine::Screen::is_done) {

			ImGuiIO &io = ImGui::GetIO();

			static bool WantTextInputLast = false;
//            if (io.WantTextInput && !WantTextInputLast)
//                displayKeyboard(true);
//            WantTextInputLast = io.WantTextInput;

			ImGui_ImplOpenGL3_NewFrame();

			ImGui_ImplAndroid_NewFrame(UnityEngine::Screen::Width(), UnityEngine::Screen::Height());

			ImGui::NewFrame();
			DrawMenu();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			/*
			 * Don't uncomment this after updating imgui this part crash xD
			 * I have to update imgui else InputTextWithHint bork on touch.
			 */
//            io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Home]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_End]] = false;
//            io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = false;
			ImGui::EndFrame();

		}
	}
}
#endif MENU