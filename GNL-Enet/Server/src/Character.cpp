#include "Character.h"
#include "World.h"


class World;

Character::Character(std::shared_ptr<Player> player) : m_player(player) {
	m_ID = 0;
	m_curMapID = 0;
	m_World = nullptr;
	pos[0] = 0.0f;
	pos[1] = 0.0f;
}


Character::~Character() {


}

void Character::SetPos(double_t x, double_t y)
{
	pos[0] = x;
	pos[1] = y;
	//m_World->FlagMoveUpdate(*this);
}

void Character::SetVel(double_t x, double_t y)
{
	vel[0] = x;
	vel[1] = y;
	m_World->FlagMoveUpdate(*this);
}