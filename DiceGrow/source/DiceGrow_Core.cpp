#include <cstdlib>
#include <iostream>
#include <emscripten.h>
#include "Character.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	// 코어의 함수들이 사이드 모듈의 extern으로 선언되어있어야 한다.

	// 플레이어, 적 객체 선언
	Character* player;
	Character* enemy;

	// 플레이어, 적 객체 생성 및 초기화
	int EMSCRIPTEN_KEEPALIVE Init()
	{
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


	// 적 정보 획득, 설정

#ifdef __cplusplus
}
#endif // __cplusplus
