#include <cstdlib>
#include <iostream>
#include <chrono>
#include <random>

#include <emscripten.h>

#include "Character.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	// 코어의 함수들이 사이드 모듈의 extern으로 선언되어있어야 한다.
	// 코어의 캐릭터 객체들이.. 사이드 모듈의 extern으로 사용이 가능한가? 확인필요

	// 플레이어, 적 객체 선언
	Character* player;
	Character* enemy;

	std::mt19937 gen(time(NULL));
	std::uniform_int_distribution<int> dist(0, 5);

	// 적 공격력 감소, 공격력 배열, 포인트 투자 한 값이 들어간다.
	int decArr[4];
	int attackArr[4];

	// 플레이어, 적 객체 생성 및 초기화
	int EMSCRIPTEN_KEEPALIVE Init()
	{
		srand(time(NULL));

		if (player == nullptr)
		{
			player = new Character();
			player->Init();
		}

		if (enemy == nullptr)
		{
			enemy = new Character();
			enemy->Init();
		}
		
		return 0;
	}

#pragma region 플레이어

	// 체력
	int EMSCRIPTEN_KEEPALIVE Get_Player_HP()
	{
		if (player == nullptr) { return -1; }
		return player->GetHP();
	}
	int EMSCRIPTEN_KEEPALIVE Get_Player_MaxHP()
	{
		if (player == nullptr) { return -1; }
		return player->GetMaxHP();
	}

	// 레벨
	int EMSCRIPTEN_KEEPALIVE Get_Player_Level()
	{
		if (player == nullptr) { return -1; }
		return player->GetLevel();
	}

	// 경험치
	int EMSCRIPTEN_KEEPALIVE Get_Player_Exp()
	{
		if (player == nullptr) { return -1; }
		return player->GetExp();
	}
	int EMSCRIPTEN_KEEPALIVE Get_Player_MaxExp()
	{
		if (player == nullptr) { return -1; }
		return player->GetMaxExp();
	}

	// 레벨 포인트
	int EMSCRIPTEN_KEEPALIVE Get_Player_LevelPoint()
	{
		if (player == nullptr) { return -1; }
		return player->GetLevelPoint();
	}

	// 주사위
	int EMSCRIPTEN_KEEPALIVE Get_Player_Dice(int slot)
	{
		if (player == nullptr) { return -1; }
		if (slot < 0 || slot >= 6) { return -1; }
		return player->GetDice(slot);
	}

	int EMSCRIPTEN_KEEPALIVE Get_Player_DicePoint()
	{
		if (player == nullptr) { return -1; }
		return player->GetDicePoint();
	}

	// 최대체력 증가
	void EMSCRIPTEN_KEEPALIVE IncreaseMaxHP() {
		if (player == nullptr) { return; }
		player->IncreaseMaxHP();
	}

	// 주사위 값 증가
	void EMSCRIPTEN_KEEPALIVE IncreaseDiceValue(int slot) {
		if (player == nullptr) { return; }
		if (slot < 0 || slot >= 6) { return; }
		player->IncreaseDiceValue(slot);
	}

#pragma endregion

#pragma region 주사위 굴리기

	// 랜덤 숫자 뽑기, 서버에서 해야할 일
	int EMSCRIPTEN_KEEPALIVE Get_Random_Dice_Point()
	{
		if (player == nullptr) { return 0; }
		int slot = dist(gen);
		player->SetDicePoint(slot);
		return player->GetDice(slot);
	}

#pragma endregion


#pragma region 전투 준비


	void EMSCRIPTEN_KEEPALIVE InitBattleArr()
	{
		for (int index = 0; index < 4; ++index)
		{
			decArr[index] = 0;
			attackArr[index] = 0;
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point(int slot)
	{
		// 2배수 적용
		return decArr[slot] * 2;
	}
	
	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point(int slot)
	{
		return attackArr[slot];
	}	

	void UseDicePoint(int value)
	{
		if (player == nullptr) { return; }

		player->UseDicePoint(value);
	}

	// 고려사항 Dice포인트가 남아있나.
	// 해당 슬롯에서 제거할 포인트가 남아있나. 
	void EMSCRIPTEN_KEEPALIVE SetEnemyAttackDecPoint(int slot, bool isInc)
	{
		if (isInc == true) 
		{
			decArr[slot] += 1;
			UseDicePoint(-1);
		}
		else
		{
			decArr[slot] -= 1;
			UseDicePoint(1);
		}	
	}
	void EMSCRIPTEN_KEEPALIVE SetPlayerAttackPoint(int slot, bool isInc)
	{
		if (isInc == true)
		{
			attackArr[slot] += 1;
			UseDicePoint(-1);
		}
		else
		{
			attackArr[slot] -= 1;
			UseDicePoint(1);
		}
	}

#pragma endregion


	// 적 정보 획득, 설정

#ifdef __cplusplus
}
#endif // __cplusplus
