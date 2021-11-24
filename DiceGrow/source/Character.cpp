#include "Character.h"

Character::Character() : mHP(0), mMaxHP(0), mLevel(0), mExp(0), mMaxExp(0), mLevelPoint(0), mDicePoint(0)
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

	mDicePoint = 0;
}

#pragma region Get함수

int Character::GetHP()				{ return mHP; }
int Character::GetMaxHP()			{ return mMaxHP; }
int Character::GetLevel()			{ return mLevel; }
int Character::GetExp()				{ return mExp; }
int Character::GetMaxExp()			{ return mMaxExp; }
int Character::GetLevelPoint()		{ return mLevelPoint; }
int Character::GetDice(int slot)	
{
	if (slot < 0 || slot >= 6) { return 0; }
	return mDice[slot]; 
}
int Character::GetDicePoint()		{ return mDicePoint; }
int Character::GetDecValue(int slot)
{
	if (slot < 0 || slot >= 4) { return 0; }
	return mDecArr[slot] * 2;
}
int Character::GetAttackValue(int slot)
{
	if (slot < 0 || slot >= 4) { return 0; }
	return mAttackArr[slot];
}

#pragma endregion

#pragma region  레벨 업 포인트

void Character::IncreaseMaxHP()
{
	if (mLevelPoint <= 0) { return; }
	mLevelPoint -= 1;

	mMaxHP += 1;
	mHP = mMaxHP;

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

#pragma region  주사위 포인트

void Character::SetDicePoint(int slot)
{
	mDicePoint = mDice[slot];
	mMaxPoint = mDicePoint;
}

void Character::UseDicePoint(int value)
{
	mDicePoint += value;
	if (mDicePoint > mMaxPoint) { mDicePoint = mMaxPoint; }
	else if (mDicePoint < 0) { mDicePoint = 0; }
}

void Character::ResetBattleArr()
{
	for (int idx = 0; idx < 4; ++idx)
	{
		mDecArr[idx] = 0;
		mAttackArr[idx] = 0;
	}
}

void Character::SetDecArr(int slot, int value)
{
	if (slot < 0 || slot >= 4) { return; }
	mDecArr[slot] += value;
}

void Character::SetAttackArr(int slot, int value)
{
	if (slot < 0 || slot >= 4) { return; }
	mAttackArr[slot] += value;
}

#pragma endregion



