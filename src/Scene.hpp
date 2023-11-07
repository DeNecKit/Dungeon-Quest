#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

class Scene
{
public:
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void RenderGUI() = 0;
	virtual void RenderSFML() = 0;
};

bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Button(label);
}

class SceneMainMenu final : public Scene
{
public:
	void ProcessEvent(const sf::Event &) override {}

	void RenderGUI() override
	{
		ImGui::Begin("Menu", (bool *)1,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_AlwaysAutoResize);
		/*ButtonCenteredOnLine((const char*)u8"������ ����� ����");
		ButtonCenteredOnLine((const char*)u8"��������� ����");
		if (ButtonCenteredOnLine((const char*)u8"�����"))
			GameManager::CloseWindow();*/
		ImGui::Button((const char*)u8"������ ����� ����");
		ImGui::Button((const char*)u8"��������� ����");
		if (ImGui::Button((const char*)u8"�����"))
			GameManager::CloseWindow();
		ImGui::End();
	}

	void RenderSFML() override {}
};