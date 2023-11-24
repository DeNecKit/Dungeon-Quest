#include "GameManager.h"

int main()
{
    GameManager::Init();
    while (GameManager::IsRunning())
        GameManager::Update();
    GameManager::Shutdown();
    return 0;
}