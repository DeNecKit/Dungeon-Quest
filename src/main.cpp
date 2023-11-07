#include "GameManager.hpp"

int main()
{
    GameManager::Init();
    while (GameManager::IsRunning())
        GameManager::Update();
    GameManager::Shutdown();
    return 0;
}