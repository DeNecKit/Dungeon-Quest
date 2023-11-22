#include "GameManager.h"
#include "ResourceManager.h"

int main()
{
    GameManager::Init();
    while (GameManager::IsRunning())
        GameManager::Update();
    GameManager::Shutdown();
    ResourceManager::Shutdown();
    return 0;
}