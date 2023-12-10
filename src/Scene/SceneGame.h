#pragma once

#include "Scene.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiList.h"
#include "../Gui/Gui.h"
#include "../Tile/TileChest.h"

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
	static void RenderOnTop(sf::Drawable *r);
	static std::vector<Gui*> GetInventoryGui();

private:
	GuiText *interText;
	GuiList *pauseMenu,
		*inventoryGui, *equipmentGui, *chestGui;
	TileChest *openedChest;
	bool isInterTextVisible, isPaused, isInvMenu;
	sf::Drawable *renderOnTop;

	static inline SceneGame *instance;
};