#include "ImGuiStuff.h"
#ifndef MENU
#define MENU

namespace Menu {
	ImVec4 color = ImVec4(1, 1, 1, 1);

	void DrawMenu() {
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		std::string text = "FPS: " + std::to_string((int)io.Framerate);
		draw_list->AddText(ImVec2(6, 6), ImColor(1.0f, 1.0f, 1.0f, 1.0f), text.c_str());

		ImGui::Begin("Town Restoration");
		{
			static float f = 0.0f;
			static int counter = 0;


			// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			if (ImGui::CollapsingHeader("Information and Links", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::Button("GitHub Repo")) OpenURL("https://github.com/zUltimaPG3D/town-restoration/");
				if (ImGui::Button("Community Discord")) OpenURL("https://discord.gg/keB3RNumVt");
                ImGui::Text("* town-restoration by sSAR");
                ImGui::Text("* Saturn by sSAR");
                ImGui::Text("  - partially based on puzzle by synzr");
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
