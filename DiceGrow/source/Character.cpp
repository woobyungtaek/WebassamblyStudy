#include<Character.h>

Character::Character() : mHP(0), mMaxHP(0), mLevel(0), mExp(0), mCurrentExp(0)
{

}

Character::~Character()
{

}

void Character::Init()
{
	mMaxHP = 15;
	mHP = mMaxHP;

	mLevel = 1;
	mExp = 3;
	mCurrentExp = 0;

	for (int cnt = 0; cnt < 0; ++cnt)
	{
		mDice[cnt] = 0;
	}
}