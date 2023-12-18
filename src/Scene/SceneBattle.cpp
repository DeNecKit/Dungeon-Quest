#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiItemSlot.h"
#include "../GameManager.h"
#include "../Entity/Player.h"

sf::Time msgTime = sf::Time::Zero;
bool generatedLoot = false;
unsigned int obtainedExp = 0U;
std::vector<Item*> obtainedLoot;

void setTargetRect(sf::RectangleShape &targetRect)
{
	sf::FloatRect hitbox = Battle::Get()->target->GetClickHitbox();
	targetRect = sf::RectangleShape(hitbox.getSize());
	targetRect.setPosition(hitbox.getPosition());
	targetRect.setFillColor(sf::Color::Transparent);
	targetRect.setOutlineThickness(2.f);
	targetRect.setOutlineColor(sf::Color(0, 255, 0, 100));
}

void setActionMenuEnabled(GuiList *actionsMenu, bool enabled)
{
	for (Gui* gui : actionsMenu->GetChildren())
	{
		GuiButton* btn = dynamic_cast<GuiButton*>(gui);
		if (Battle::CanEscape()) btn->SetEnabled(enabled);
	}
}

SceneBattle::SceneBattle()
	: lastTarget(Battle::Get()->target), isInvMenu(false), victoryMenu(nullptr)
{
	instance = this;
	Player::InBattle(true);
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	playerHealthBar = new GuiProgressBar(
		sf::FloatRect(Player::Get()->GetHealthBarPos(), hbs), Gui::HealthBarFillColor,
		(unsigned int&)Player::Get()->GetHP(), Player::GetMaxHP());
	for (Enemy *enemy : Battle::GetEnemies())
		enemiesHealthBar.push_back(new GuiProgressBar(
		sf::FloatRect(enemy->GetHealthBarPos(), hbs), Gui::HealthBarFillColor,
			(unsigned int&)enemy->GetHP(), enemy->GetStats()[Stat::HP]));
	const float ww = 1920.f, hww = ww/2.f, wh = 1080.f, hwh = wh/2.f;
	messageText = new GuiText(sf::FloatRect(50.f, 50.f, 1.f, 50.f), L"", 24, false);
	const float bw = 250.f, bh = 75.f, d = 25.f, w = bw*3 + d*4, h = bh + d*2,
		x = d, y = GameManager::WindowHeight() - d - h;
	actionsMenu = new GuiList(sf::FloatRect(x, y, w, h), true);
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d, y+d, bw, bh),
		L"Атака", 24, [](const sf::Event&) { Battle::MakeTurn(TurnAction::Attack); }));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*2+bw, y+d, bw, bh),
		L"Предмет", 24, [](const sf::Event&) { Battle::MakeTurn(TurnAction::UseItem); }));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*3+bw*2, y+d, bw, bh),
		L"Побег", 24, [](const sf::Event&) { Battle::MakeTurn(TurnAction::Flee); }));
	inventoryGui = GuiList::CreatePlayerInventory();
	const sf::FloatRect id = inventoryGui->dimensions;
	inventoryCancel = new GuiButton(sf::FloatRect(
		id.left + id.width/2 - bw/2, id.top + id.height + d, bw, bh),
		L"Отмена", 24, [](const sf::Event&) { ShowInventory(false); });
	const float mbw = 500.f, mbh = 100.f, bd = 50.f,
		vmw = mbw + bd*2, vmh = mbh*2 + bd*3,
		vmx = hww - vmw/2, vmy = hwh - vmh/2;
	const float dmw = mbw + bd*2, dmh = mbh*2 + bd*3,
		dmx = hww - dmw/2, dmy = hwh - dmh/2;
	defeatMenu = new GuiList(sf::FloatRect(dmx, dmy, dmw, dmh));
	defeatMenu->Append(new GuiText(sf::FloatRect(dmx+bd, dmy + bd, mbw, mbh), L"Поражение!", 48));
	defeatMenu->Append(new GuiButton(sf::FloatRect(dmx+bd, dmy+mbh+bd*2, mbw, mbh),
		L"Вернуться в главное меню", 24, [](const sf::Event&) { Battle::End(); }));
	setTargetRect(targetRect);
	generatedLoot = false;
	obtainedExp = 0U;
	for (auto item : obtainedLoot)
		Item::Delete(item);
	obtainedLoot.clear();
	if (!Battle::CanEscape())
		dynamic_cast<GuiButton*>(actionsMenu->GetChildren()[2])->SetEnabled(false);
}

SceneBattle::~SceneBattle()
{
	delete playerHealthBar;
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		delete enemyBar;
	delete actionsMenu;
	delete messageText;
	delete inventoryGui;
	delete inventoryCancel;
	if (victoryMenu != nullptr) delete victoryMenu;
	delete defeatMenu;
	Player::InBattle(false);
	instance = nullptr;
}

void SceneBattle::ProcessEvent(const sf::Event &event)
{
	if (Battle::IsEnd())
	{
		if (Battle::IsVictory()) victoryMenu->ProcessEvent(event);
		else defeatMenu->ProcessEvent(event);
		return;
	}
	if (isInvMenu)
	{
		inventoryGui->ProcessEvent(event);
		inventoryCancel->ProcessEvent(event);
		return;
	}
	if (Battle::IsPlayerTurn()) actionsMenu->ProcessEvent(event);
	if (Battle::Get() == nullptr) return;
	for (Enemy *enemy : Battle::GetEnemies())
		if (!enemy->IsOut()) enemy->ProcessEvent(event);
}

void SceneBattle::Update(sf::Time deltaTime)
{
	if (Battle::Get() != nullptr)
		if (!Battle::IsEnd()) Battle::Get()->Update(deltaTime);
	if (Battle::Get() == nullptr) return;
	if (isInvMenu && !Battle::IsEnd())
	{
		inventoryGui->Update(deltaTime);
		inventoryCancel->Update(deltaTime);
		return;
	}
	if (Battle::IsEnd())
	{
		if (!generatedLoot)
		{
			std::vector<Item*> tmpLoot;
			for (Enemy* enemy : Battle::GetEnemies())
			{
				obtainedExp += enemy->DropExp();
				auto loot = enemy->DropLoot();
				tmpLoot.insert(tmpLoot.end(), loot.begin(), loot.end());
			}
			for (size_t i = 0; i < tmpLoot.size(); i++)
			{
				bool found = false;
				for (size_t j = 0; j < obtainedLoot.size(); j++)
					if (tmpLoot[i]->GetTemplate() == obtainedLoot[j]->GetTemplate())
					{
						obtainedLoot[j]->SetCount(
							obtainedLoot[j]->GetCount() + tmpLoot[i]->GetCount());
						Item::Delete(tmpLoot[i]);
						found = true;
						break;
					}
				if (!found) obtainedLoot.push_back(tmpLoot[i]);
			}
			for (auto item : obtainedLoot) Player::AddItem(new Item(*item));
			Player::AddExp(obtainedExp);
			const bool droppedLoot = obtainedLoot.size() > 0;
			const int bc = droppedLoot ? 4 : 3;
			const float hww = 1920.f/2, hwh = 1080.f/2,
				bw = 500.f, bh = 100.f, bd = 50.f,
				vmw = bw+bd*2, vmh = bh*bc+bd*(bc+1),
				vmx = hww-vmw/2, vmy = hwh-vmh/2;
			victoryMenu = new GuiList(sf::FloatRect(vmx, vmy, vmw, vmh));
			victoryMenu->Append(new GuiText(
				sf::FloatRect(vmx+bd, vmy+bd, bw, bh), L"Победа!", 48));
			victoryMenu->Append(
				new GuiText(sf::FloatRect(vmx+bd, vmy+bh+bd*2, bw, bh),
					L"+" + std::to_wstring(obtainedExp) + L" опыта", 24));
			if (droppedLoot)
			{
				const size_t n = obtainedLoot.size();
				const float s = 100.f, h = 125.f,
					x = vmx+vmw/2-(s*n+bd*(n-1))/2, y = vmy+bh*2+bd*3;
				auto loot = new GuiList(sf::FloatRect(vmx+bd, y, bw, h), true);
				for (int i = 0; i < n; i++)
					loot->Append(new GuiItemSlot(sf::FloatRect(x+(s+bd)*i, y+h/2-s/2, s, s),
						nullptr, i, SlotType::Any, obtainedLoot[i], false));
				victoryMenu->Append(loot);
			}
			victoryMenu->Append(new GuiButton(
				sf::FloatRect(vmx+bd, vmy+bh*(bc-1)+bd*bc, bw, bh),
				L"Продолжить", 24, [](const sf::Event&) { Battle::End(); }));
			generatedLoot = true;
		}
		if (Battle::IsVictory()) victoryMenu->Update(deltaTime);
		else defeatMenu->Update(deltaTime);
		return;
	}
	setActionMenuEnabled(instance->actionsMenu,
		Battle::IsPlayerTurn() && Battle::GetStage() == TurnStage::Waiting);
	playerHealthBar->Update(deltaTime);
	int i = 0;
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		if (!Battle::GetEnemies()[i++]->IsOut())
			enemyBar->Update(deltaTime);
	if (Battle::IsPlayerTurn()) actionsMenu->Update(deltaTime);
	if (lastTarget != Battle::Get()->target)
	{
		setTargetRect(targetRect);
		lastTarget = Battle::Get()->target;
	}
	if (msgTime > sf::Time::Zero)
		msgTime = std::max(msgTime - deltaTime, sf::Time::Zero);
}

void SceneBattle::RenderGUI(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	playerHealthBar->Render(window);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Render(window);
	window->draw(targetRect);
	if (msgTime > sf::Time::Zero)
		messageText->Render(window);
	if (Battle::IsEnd())
	{
		sf::RectangleShape r((sf::Vector2f)window->getSize());
		r.setFillColor(sf::Color(0, 0, 0, 127));
		window->draw(r);
		if (Battle::IsVictory()) victoryMenu->Render(window);
		else defeatMenu->Render(window);
	} else
	{
		actionsMenu->Render(window);
		if (isInvMenu)
		{
			inventoryGui->Render(window);
			inventoryCancel->Render(window);
		}
	}
	if (renderOnTop.size() > 0)
	{
		for (std::variant<sf::Drawable*, Gui*> obj : renderOnTop)
			if (std::holds_alternative<sf::Drawable*>(obj))
				window->draw(*std::get<sf::Drawable*>(obj));
			else std::get<Gui*>(obj)->Render(window);
		renderOnTop.clear();
	}
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	window->clear(sf::Color(58, 51, 62));
	Battle::Get()->Render(window);
}

void SceneBattle::Message(const sf::String& str)
{
	msgTime = sf::seconds(1.f);
	instance->messageText->SetString(str);
}

void SceneBattle::ShowInventory(bool show)
{
	instance->isInvMenu = show;
	if (show)
	{
		setActionMenuEnabled(instance->actionsMenu, false);
		for (int i = 0; i < 15; i++)
			instance->inventoryGui->SetItem(i, Player::GetItem(i));
	}
	else Battle::SetTurnStage(TurnStage::Waiting);
}

bool SceneBattle::IsInventoryOpen()
{
	return instance->isInvMenu;
}

std::vector<Gui*> SceneBattle::GetInventoryGui()
{
	return instance->inventoryGui->GetChildren();
}

void SceneBattle::RenderOnTop(std::variant<sf::Drawable*, Gui*> obj)
{
	instance->renderOnTop.push_back(obj);
}