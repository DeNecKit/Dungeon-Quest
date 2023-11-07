#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "SceneManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
        "Dungeon Quest", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    GameManager::Init(window);
    SceneManager::Init();

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            SceneManager::ProccessEvent(event);
        }
        sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        SceneManager::RenderGUI();

        window.clear(sf::Color(36, 36, 36));
        SceneManager::RenderSFML();
        ImGui::SFML::Render(window);
        window.display();
    }

    SceneManager::Shutdown();
    ImGui::SFML::Shutdown();
    return 0;
}