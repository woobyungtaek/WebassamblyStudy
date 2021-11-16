#include "Character.h"

Character::Character() : mHP(0), mMaxHP(0), mLevel(0), mExp(0), mMaxExp(0), mLevelPoint(0)
{

}

Character::~Character()
{

}

void Character::Init()
{
	mMaxHP = 15;
	mHP = mMaxHP;

	mLevelPoint = 9;

	mLevel = 1;
	mExp = 0;
	mMaxExp = 3;


	for (int cnt = 0; cnt < 0; ++cnt)
	{
		mDice[cnt] = 0;
	}
}

#pragma region Get함수

int Character::GetHP()				{ return mHP; }
int Character::GetMaxHP()			{ return mMaxHP; }
int Character::GetLevel()			{ return mLevel; }
int Character::GetExp()				{ return mExp; }
int Character::GetMaxExp()			{ return mMaxExp; }
int Character::GetLevelPoint()		{ return mLevelPoint; }
int Character::GetDice(int slot)	{ return mDice[slot]; }

#pragma endregion

#pragma region 포인트 투자 함수

void Character::IncreaseMaxHP()
{
	if (mLevelPoint <= 0) { return; }
	mLevelPoint -= 1;

	mMaxHP += 1;

	return;
}

void Character::IncreaseDiceValue(int slot)
{
	if (mLevelPoint <= 0) { return; }
	mLevelPoint -= 1;

	mDice[slot] += 1;

	return;
}

#pragma endregion


