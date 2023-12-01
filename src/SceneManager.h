#pragma once

#include "Scene.h"

class SceneManager
{
public:
	static void Init();
	template<typename T> static void ChangeScene();
	static void ProccessEvent(const sf::Event &);
	static void Update(sf::Time);
	static void RenderGUI(sf::RenderWindow*);
	static void RenderSFML(sf::RenderWindow*);
	static void Shutdown();

private:
	static inline Scene *currentScene, *tmpScene;
	static inline bool isSceneChanged;
};

template<typename T>
void SceneManager::ChangeScene()
{
	tmpScene = new T();
	isSceneChanged = true;
}