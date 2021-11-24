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

	int finalAttackValue[8] = { 0, };

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
		player->ResetBattleArr();

		for (int idx = 0; idx < 8; ++idx)
		{
			finalAttackValue[idx] = 0;
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point(int slot)
	{
		// 0~3 : 적 ui, 4~7 : 플레이어 ui

		if (slot < 4)
		{
			// 적
			return enemy->GetDecValue(slot);
		}
		else
		{
			//플레이어
			return player->GetDecValue(slot - 4);
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point(int slot)
	{
		// 0~3 : 적 ui, 4~7 : 플레이어 ui

		if (slot < 4)
		{
			// 적
			return enemy->GetAttackValue(slot);
		}
		else
		{
			//플레이어
			return player->GetAttackValue(slot - 4);
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack(int slot)
	{
		// 0~3 : 적 ui, 4~7 : 플레이어 ui
		int arrIdx = slot % 4;
		if (slot < 0 || slot >= 8) { return 0; }
		if (slot < 4)
		{
			finalAttackValue[slot] = enemy->GetAttackValue(arrIdx) - player->GetDecValue(arrIdx);
		}
		else
		{
			finalAttackValue[slot] = player->GetAttackValue(arrIdx) - enemy->GetDecValue(arrIdx);
		}

		return finalAttackValue[slot];
	}

	int EMSCRIPTEN_KEEPALIVE Get_Result_Damage(int turnSlot)
	{
		// 0~3 : 적 최종 공격력, 4~7 : 플레이어 최종 공격력
		// turnSlot : 0 ~ 3값
		// turnSlot+4

		// re <  0 : 플레이어 패배
		// re == 0 : 무승부
		// re >  0 : 플레이어 승리
		return finalAttackValue[turnSlot + 4] - finalAttackValue[turnSlot];
	}

	void UseDicePoint(int value)
	{
		if (player == nullptr) { return; }

		player->UseDicePoint(value);
	}

	// SlotPoint 증가
	void EMSCRIPTEN_KEEPALIVE IncreaseSlotPoint(int slotType, int slotNum)
	{
		if (player == nullptr) { return; }

		// Dice포인트가 남아있는지 확인한다.
		if (player->GetDicePoint() <= 0) { return; }

		// type [0:EnemyAttackDec][1:PlayerAttack]
		// type을 확인한다.
		if (slotType == 0) { player->SetDecArr(slotNum, 1); }
		else if (slotType == 1) { player->SetAttackArr(slotNum, 1); }
		else { return; }

		// DicePoint 감소
		player->UseDicePoint(-1);

	}

	// SlotPoint 감소
	void EMSCRIPTEN_KEEPALIVE DecreaseSlotPoint(int slotType, int slotNum)
	{
		if (player == nullptr) { return; }

		// type [0:EnemyAttackDec][1:PlayerAttack]
		// type을 확인한다.
		// slot 확인 후 0보다 크면 감소
		if (slotType == 0)
		{
			if (player->GetDecValue(slotNum) <= 0) { return; }
			player->SetDecArr(slotNum, -1);
		}
		else if (slotType == 1)
		{
			if (player->GetAttackValue(slotNum) <= 0) { return; }
			player->SetAttackArr(slotNum, -1);
		}
		else { return; }

		// DicePoint 증가
		player->UseDicePoint(1);
	}

#pragma endregion

#pragma region 전투

	// 최초 상태로 초기화

	// 

#pragma endregion


	// 적 정보 획득, 설정

#ifdef __cplusplus
}
#endif // __cplusplus
