#pragma once

#include "Scene.h"
#include "../Gui/GuiProgressBar.h"
#include "../Gui/GuiList.h"
#include "../Entity/Enemy.h"
#include "../Gui/GuiButton.h"
#include <vector>
#include <variant>

class SceneBattle final : public Scene
{
public:
	SceneBattle();
	~SceneBattle();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;
	static void Message(const sf::String &str);
	static void ShowInventory(bool show);
	static bool IsInventoryOpen();
	static std::vector<Gui*> GetInventoryGui();
	static void RenderOnTop(std::variant<sf::Drawable*, Gui*> obj);

private:
	GuiProgressBar *playerHealthBar;
	std::vector<GuiProgressBar*> enemiesHealthBar;
	GuiList *actionsMenu, *inventoryGui, *victoryMenu, *defeatMenu;
	GuiButton *inventoryCancel;
	GuiText *messageText;
	Enemy *lastTarget;
	sf::RectangleShape targetRect;
	bool isInvMenu;
	std::vector<std::variant<sf::Drawable*, Gui*>> renderOnTop;

	static inline SceneBattle *instance;
};