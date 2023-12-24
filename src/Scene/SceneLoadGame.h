#pragma once

#include "Scene.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiList.h"
#include <vector>
#include <map>

class SceneLoadGame final : public Scene
{
public:
	SceneLoadGame();
	~SceneLoadGame();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

	static std::vector<std::string> GetSavePaths();
	static unsigned int GetBtnNum(Gui*);

private:
	void SetPage(unsigned int page);

	GuiText *text;
	GuiList *saves;
	GuiButton *back;
	std::vector<std::string> savePaths;
	std::map<Gui*, unsigned int> btnNum;
	std::vector<sf::String> saveNames;
	unsigned int pagesNum, curPage;

	static inline SceneLoadGame *instance;
};