#include "Player.h"
#include "../GameManager.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneBattle.h"
#include "../Level.h"
#include "../Battle.h"
#include "../Gui/GuiProgressBar.h"
#include "EnemyGoblin.h"
#include "EnemyGoblinKing.h"
#include "EnemyDemonEye.h"
#include "EnemyReaper.h"
#include "EnemySkeleton.h"
#include "EnemyNecromancer.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool playerAttacked = false;
bool finishedHit = false;
bool finishedDeath = false;
unsigned int maxHP;

Player::Player(sf::Vector2u startPos, PlayerDirection startDir)
	: Entity(3), isInBattle(false), direction(startDir),
	animationState(PlayerAnimationState::Idle), walkedDistance(0.f),
	requiredDistance(GenerateRequiredDistance())
{
	currentPlayer = this;
	animationDeltaTime = sf::milliseconds(128);
	position = sf::Vector2f(
		(float)(startPos.x * Level::GetTileSize()),
		(float)(startPos.y * Level::GetTileSize()));
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile("data/player.png"))
		throw std::exception();
	numOfFrames = {
		{ PlayerAnimationState::Idle, 1 },
		{ PlayerAnimationState::Walking, 4 }
	};
	numOfBattleFrames = {
		{ BattleAnimationState::Idle, 6 },
		{ BattleAnimationState::Attack,	6 },
		{ BattleAnimationState::TakeHit, 3 },
		{ BattleAnimationState::Death, 6 }
	};
	stats = {{Stat::HP, 40}, {Stat::ATK, 5}, {Stat::DEF, 5}, {Stat::AGI, 5}};
	std::ifstream dataFile("data/player.json");
	if (!dataFile.is_open())
		throw std::exception();
	json data = json::parse(dataFile);
	dataFile.close();
	for (int i = 0; i < 20; i++)
		inventory[i] = nullptr;
	for (json &item : data["start-inventory"])
		inventory[item["pos"]] = Item::Create(item["id"], item["count"]);
	hp = GetMaxHP();
	curLevel = 1;
	curExp = 0;
	maxLevel = data["max-lvl"];
	for (unsigned int i = 0; i < maxLevel-1; i++)
	{
		reqExpList.push_back(data["req-exp"][i]);
		statsDiff.push_back({
			{Stat::HP, data["stats-diff"][i][0]},
			{Stat::ATK, data["stats-diff"][i][1]},
			{Stat::DEF, data["stats-diff"][i][2]},
			{Stat::AGI, data["stats-diff"][i][3]} });
	}
	reqExp = reqExpList[0];
	levelString = new sf::String(L"������� ������: 1");
	statsString = new sf::String();
	UpdateStatsString();
}

Player::~Player()
{
	delete levelString;
	delete statsString;
	currentPlayer = nullptr;
}

void Player::Update(sf::Time deltaTime)
{
	if (isInBattle) UpdateInBattle(deltaTime);
	else UpdateInGame(deltaTime);
}

void Player::Render(sf::RenderWindow *window)
{
	if (isInBattle) RenderInBattle(window);
	else RenderInGame(window);
}

sf::Vector2f Player::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y, ps = Player::GetScreenSize() * 0.875f,
		px = Player::GetScreenPos().x, py = Player::GetScreenPos().y;
	return sf::Vector2f(px + ps/2 - w/2, py + h*4);
}

unsigned int Player::Attack()
{
	unsigned int res = stats[Stat::ATK];
	for (int i = 15; i < 20; i++)
		res += inventory[i] ? inventory[i]->GetTemplate()->GetStats()[Stat::ATK] : 0;
	return res;
}

bool Player::FinishedActionAnimation()
{
	if (Battle::GetChosenAction() == TurnAction::Attack)
		return playerAttacked;
	return true;
}

bool Player::FinishedHitAnimation()
{
	return finishedHit;
}

bool Player::FinishedDeathAnimation()
{
	return finishedDeath;
}

void Player::TakeHit(unsigned int damage)
{
	int dmg = (int)damage - (int)stats[Stat::DEF];
	for (int i = 15; i < 20; i++)
		if (inventory[i]) dmg -=
			(int)inventory[i]->GetTemplate()->GetStats()[Stat::DEF];
	dmg = std::max(dmg, 0);
	hp = std::max(hp - dmg, 0);
	battleAnimationState = BattleAnimationState::TakeHit;
	animationCurFrame = 0;
}

unsigned int Player::GetStat(Stat stat)
{
	unsigned int res = stats[stat];
	for (int i = 15; i < 20; i++)
		if (inventory[i]) res = std::max(
			res+inventory[i]->GetTemplate()->GetStats()[stat], 0U);
	return res;
}

unsigned int &Player::GetMaxHP()
{
	maxHP = currentPlayer->stats[Stat::HP];
	for (int i = 15; i < 20; i++)
		if (currentPlayer->inventory[i]) maxHP +=
			currentPlayer->inventory[i]->GetTemplate()->GetStats()[Stat::HP];
	return maxHP;
}

void Player::Heal(unsigned int healing)
{
	currentPlayer->hp = std::min(currentPlayer->hp + healing, GetMaxHP());
}

void Player::UpdateStatsString()
{
	sf::String *str = currentPlayer->statsString;
	*str = "";
	auto statNames = new std::map<Stat, sf::String>({
		{ Stat::HP, L"���� ��������: "}, { Stat::ATK, L"�����: "},
		{ Stat::DEF, L"������: "}, { Stat::AGI, L"��������: "} });
	std::map<Stat, unsigned int> curStats = currentPlayer->stats;
	for (int i = 15; i < 20; i++)
	{
		if (currentPlayer->inventory[i] == nullptr) continue;
		for (Stat statType = Stat::HP; statType <= Stat::AGI;
			statType = (Stat)((int)statType + 1))
		{
			curStats[statType] = std::max(
				curStats[statType] + currentPlayer->inventory[i]
				->GetTemplate()->GetStats()[statType], 0U);
		}
	}
	bool added = false;
	for (auto &[statType, stat] : curStats)
	{
		if (added) *str += "\n";
		else added = true;
		unsigned int baseStat = currentPlayer->stats[statType];
		int diff = (int)stat - (int)baseStat;
		*str += statNames->at(statType) + std::to_string(stat) + " (" +
			std::to_string(baseStat) + (diff < 0 ? " - " : " + ") +
			std::to_string(std::abs(diff)) + ")";
	}
	Heal(0);
	delete statNames;
}

const sf::String &Player::GetLevelString()
{
	return *currentPlayer->levelString;
}

const sf::String& Player::GetStatsString()
{
	return *currentPlayer->statsString;
}

unsigned int &Player::GetExp()
{
	return currentPlayer->curExp;
}

unsigned int &Player::GetReqExp()
{
	return currentPlayer->reqExp;
}

void Player::AddItem(Item *item)
{
	bool found = false;
	for (unsigned int i = 0; i < 20; i++)
	{
		auto curItem = GetItem(i);
		if (curItem != nullptr && curItem->GetTemplate() == item->GetTemplate())
		{
			curItem->SetCount(curItem->GetCount() + item->GetCount());
			found = true;
			break;
		}
	}
	if (!found)
		for (unsigned int i = 0; i < 20; i++)
			if (Player::GetItem(i) == nullptr)
			{
				Player::SetItem(i, item);
				found = true;
				break;
			}
}

void Player::AddExp(unsigned int exp)
{
	auto p = currentPlayer;
	if (p->curLevel == 20) return;
	p->curExp += exp;
	bool updateGui = false;
	unsigned int hpAdded = 0U;
	while (p->curExp >= p->reqExp)
	{
		if (p->curLevel == 20) break;
		p->curExp -= p->reqExp;
		p->reqExp = p->reqExpList[p->curLevel - (p->curLevel < 19 ? 0 : 1)];
		if (p->curLevel == 19) p->curExp = p->reqExp;
		for (Stat statType = Stat::HP; statType <= Stat::AGI;
			statType = (Stat)((int)statType + 1))
			p->stats[statType] += p->statsDiff[p->curLevel-1][statType];
		hpAdded += p->statsDiff[p->curLevel-1][Stat::HP];
		p->curLevel++;
		updateGui = true;
	}
	if (updateGui)
	{
		*p->levelString = L"������� ������: " + std::to_wstring(p->curLevel);
		UpdateStatsString();
	}
	Heal(hpAdded);
}

void Player::ResetBattleDist()
{
	currentPlayer->walkedDistance = 0.f;
}

json Player::Save()
{
	json res;
	auto p = currentPlayer;
	res["x"] = p->position.x;
	res["y"] = p->position.y;
	res["hp"] = p->hp;
	res["lvl"] = p->curLevel;
	res["exp"] = p->curExp;
	res["dir"] = (int)p->direction;
	std::vector<json> inv;
	for (int i = 0; i < 20; i++)
		if (p->inventory[i] != nullptr)
			inv.push_back({
				{"pos", i},
				{"id", p->inventory[i]->GetTemplate()->GetId()},
				{"count", p->inventory[i]->GetCount()} });
	res["inventory"] = inv;
	res["walked-dist"] = p->walkedDistance;
	res["req-dist"] = p->requiredDistance;
	return res;
}

void Player::Load(json data)
{
	auto p = currentPlayer;
	while (p->curLevel < data["lvl"])
		p->AddExp(p->reqExp);
	p->curExp = data["exp"];
	p->hp = data["hp"];
	p->direction = (PlayerDirection)data["dir"];
	p->requiredDistance = data["req-dist"];
	p->walkedDistance = data["walked-dist"];
	p->position = {data["x"], data["y"]};
	for (int i = 0; i < 20; i++)
	{
		Item::Delete(p->inventory[i]);
		p->inventory[i] = nullptr;
	}
	for (json &item : data["inventory"])
		p->inventory[item["pos"]] = Item::Create(item["id"], item["count"]);
}

void Player::UpdateInGame(sf::Time deltaTime)
{
	float s = (float)Level::GetTileSize(), ps = GetSize(),
		bx = Level::GetBossTile().x, by = Level::GetBossTile().y;
	if (!Level::IsBossDefeated() &&
		position.x+ps > bx && position.x < bx+s &&
		position.y+ps > by && position.y < by+s)
	{
		std::vector<Enemy*> enemies;
		switch (Level::GetNum())
		{
		case 1:
			enemies = { new EnemyGoblinKing(1), new EnemyGoblin(2), new EnemyGoblin(3) };
			break;
		case 2:
			enemies = { new EnemyReaper(1), new EnemyDemonEye(2), new EnemyDemonEye(3) };
			break;
		case 3:
			enemies = { new EnemyNecromancer(1), new EnemySkeleton(2), new EnemySkeleton(3) };
			break;
		default: throw new std::exception();
		}
		Battle::Start(this, enemies, false);
		Level::SetBossDefeated();
		return;
	}
	const float ex = Level::GetEndTile().x, ey = Level::GetEndTile().y;
	if (position.x+ps > ex && position.x < ex+s &&
		position.y+ps > ey && position.y < ey+s)
	{
		Level::Next();
		return;
	}

	float sprint = sf::Keyboard::isKeyPressed(
		sf::Keyboard::LShift) ? sprintCoef : 1.f;

	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime / sprint)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame = (animationCurFrame + 1)
			% numOfFrames[animationState];
	}

	bool walking = false;
	float speed = this->speed * GameManager::ResCoefX(),
		deltaDist = speed * sprint * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		walking = true;
		direction = PlayerDirection::Right;
		TryMove(deltaDist, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		walking = true;
		direction = PlayerDirection::Left;
		TryMove(-deltaDist, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		walking = true;
		TryMove(0.f, deltaDist);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		walking = true;
		TryMove(0.f, -deltaDist);
	}
	if (walking)
	{
		animationState = PlayerAnimationState::Walking;
		walkedDistance += deltaDist;
		if (walkedDistance > requiredDistance)
		{
			walkedDistance = 0.f;
			requiredDistance = GenerateRequiredDistance();
			std::vector<Enemy*> enemies;
			int g = std::rand() % 3 + 1;
			for (int i = 1; i <= 3; i++)
				if (i == g || std::rand() % 2)
					switch (Level::GetNum())
					{
					case 1: enemies.push_back(new EnemyGoblin(i)); break;
					case 2: enemies.push_back(new EnemyDemonEye(i)); break;
					case 3: enemies.push_back(new EnemySkeleton(i)); break;
					default: throw new std::exception();
					}
			Battle::Start(this, enemies);
		}
	} else animationState = PlayerAnimationState::Idle;
}

void Player::UpdateInBattle(sf::Time deltaTime)
{
	if (Battle::IsPlayerTurn() &&
		Battle::GetStage() == TurnStage::Waiting)
	{
		playerAttacked = false;
		finishedHit = false;
	}
	bool attack = Battle::IsPlayerTurn() && !playerAttacked
		&& Battle::GetStage() == TurnStage::Action
		&& Battle::GetChosenAction() == TurnAction::Attack;
	if (battleAnimationState != BattleAnimationState::Attack && attack)
	{
		battleAnimationState = BattleAnimationState::Attack;
		animationCurFrame = 0;
	}
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame++;
		bool animLastFrame = animationCurFrame == numOfBattleFrames[battleAnimationState];
		if (battleAnimationState == BattleAnimationState::TakeHit && animLastFrame)
		{
			battleAnimationState = IsAlive()
				? BattleAnimationState::Idle : BattleAnimationState::Death;
			finishedHit = true;
			animationCurFrame = 0;
			animLastFrame = false;
		}
		if (battleAnimationState == BattleAnimationState::Death && animLastFrame)
		{
			finishedDeath = true;
			animationCurFrame--;
		}
		if (attack && animLastFrame)
		{
			playerAttacked = true;
			battleAnimationState = BattleAnimationState::Idle;
			animationCurFrame = 0;
		}
		else if (battleAnimationState == BattleAnimationState::Idle)
			animationCurFrame %= numOfBattleFrames[battleAnimationState];
	}
}

void Player::RenderInGame(sf::RenderWindow *window)
{
	unsigned int texSize = 16;
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * texSize, 0, texSize, texSize));
	s.setPosition(GetScreenPos());
	float factor = GetScreenSize()/16;
	int right = direction == PlayerDirection::Right ? 1 : -1;
	s.setScale(sf::Vector2f(factor * right, factor));
	window->draw(s);
}

void Player::RenderInBattle(sf::RenderWindow* window)
{
	unsigned int texSize = 64;
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * texSize,
			16 + (int)battleAnimationState * texSize, texSize, texSize));
	s.setPosition(GetScreenPos());
	float factor = GetScreenSize() / texSize;
	s.setScale(factor, factor);
	window->draw(s);
}

void Player::TryMove(float deltaX, float deltaY)
{
	sf::Vector2f newPos = sf::Vector2f(
		position.x + deltaX,
		position.y + deltaY);
	float tileSize = (float)Level::GetTileSize(),
		playerSize = tileSize * sizeCoef,
		px = newPos.x, py = newPos.y;
	for (Tile *tile : Level::GetOtherTiles())
	{
		float x = tile->GetPos().x, y = tile->GetPos().y;
		if (tile->IsWall()
			&& px + playerSize > x && px < x + playerSize
			&& py + playerSize > y && py < y + playerSize)
			newPos = GetFixedPos(deltaX, deltaY, newPos, playerSize, x, y);
	}
	for (int dx = -1; dx <= 1; dx++)
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0) continue;
			float x = newPos.x + tileSize * dx,
				y = newPos.y + tileSize * dy;
			int ix = (int)std::roundf(x / tileSize),
				iy = (int)std::roundf(y / tileSize);
			x = ix * tileSize, y = iy * tileSize;
			if (Level::IsWall(ix, iy)
				&& px + playerSize > x && px < x + playerSize
				&& py + playerSize > y && py < y + playerSize)
				newPos = GetFixedPos(deltaX, deltaY, newPos, playerSize, x, y);
		}
	position = newPos;
}

sf::Vector2f Player::GetFixedPos(float deltaX, float deltaY,
	sf::Vector2f playerPos, float playerSize,
	float otherX, float otherY)
{
	if (deltaX > 0)
		playerPos = sf::Vector2f(otherX - playerSize, playerPos.y);
	else if (deltaX < 0)
		playerPos = sf::Vector2f(otherX + playerSize, playerPos.y);
	else if (deltaY > 0)
		playerPos = sf::Vector2f(playerPos.x, otherY - playerSize);
	else if (deltaY < 0)
		playerPos = sf::Vector2f(playerPos.x, otherY + playerSize);
	return playerPos;
}

float Player::GenerateRequiredDistance()
{
	return std::rand() / (float)RAND_MAX * 8*speed + 7*speed;
	//return 30*speed;
	//return 10.f;
}

void Player::SetStartPos(sf::Vector2u startPos)
{
	currentPlayer->position = sf::Vector2f(
		(float)(startPos.x * Level::GetTileSize()),
		(float)(startPos.y * Level::GetTileSize()));
}

sf::Vector2f Player::GetPos()
{
	return currentPlayer->position;
}

float Player::GetSize()
{
	return Level::GetTileSize() * sizeCoef;
}

Item *Player::GetItem(unsigned int pos)
{
	return currentPlayer->inventory[pos];
}

bool Player::HasItem(ItemTemplate *itemTemplate)
{
	for (int i = 0; i < 20; i++)
		if (currentPlayer->inventory[i] != nullptr &&
			currentPlayer->inventory[i]->GetTemplate() == itemTemplate)
			return true;
	return false;
}

void Player::SetItem(unsigned int pos, Item *item)
{
	currentPlayer->inventory[pos] = item;
}

void Player::InBattle(bool set)
{
	currentPlayer->isInBattle = set;
	currentPlayer->animationCurFrame = 0;
}

std::map<Stat, unsigned int> Player::GetStats()
{
	return currentPlayer->stats;
}

sf::Vector2f Player::GetScreenPos()
{
	if (currentPlayer->isInBattle)
	{
		float size = GameManager::WindowHeight()/2.f;
		return sf::Vector2f(0.f, GameManager::WindowHeight()/2.f - size/2);
	}
	else
	{
		int right = currentPlayer->direction == PlayerDirection::Right ? 1 : -1;
		return sf::Vector2f(
			GameManager::WindowWidth()/2 - Level::GetTileSize()*sizeCoef/2 * right,
			GameManager::WindowHeight()/2 - Level::GetTileSize()*sizeCoef/2);
	}
}

float Player::GetScreenSize()
{
	if (currentPlayer->isInBattle) return GameManager::WindowHeight()/2.f;
	else return Level::GetTileSize()*sizeCoef;
}

Player* Player::Get()
{
	return currentPlayer;
}