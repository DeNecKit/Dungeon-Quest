#pragma once

#include "Scene.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiList.h"
#include "../Gui/Gui.h"
#include "../Tile/TileChest.h"
#include <variant>

class SceneGame final : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

	static void InteractionNotify();
	static void SetPause(bool pause);
	static void OpenChest(TileChest *chest);
	static void RefreshPlayerInventory();
	static void RenderOnTop(std::variant<sf::Drawable*, Gui*> obj);
	static std::vector<Gui*> GetInventoryGui();
	static void UpdateStatsText();

private:
	GuiText *interText;
	GuiList *pauseMenu, *statusGui,
		*inventoryGui, *equipmentGui, *chestGui;
	TileChest *openedChest;
	bool isInterTextVisible, isPaused, isInvMenu;
	std::vector<std::variant<sf::Drawable*, Gui*>> renderOnTop;

	static inline SceneGame *instance;
};