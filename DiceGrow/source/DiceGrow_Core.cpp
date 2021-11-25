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

	const int TURN_COUNT = 4;
	int finalAttackArr_player[TURN_COUNT] = { 0, };
	int finalAttackArr_enemy[TURN_COUNT] = { 0, };
	int turnResultArr[TURN_COUNT] = { 0, };

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


#pragma region 전투 준비 & 전투

	// 플레이어 공격, 적 감소 수치 얻기
	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point_Player(int slot)
	{
		return player->GetDecValue(slot);
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point_Player(int slot)
	{
		return player->GetAttackValue(slot);
	}

	//  적 공격, 플레이어 감소 수치 얻기
	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point_Enemy(int slot)
	{
		return enemy->GetDecValue(slot);
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point_Enemy(int slot)
	{
		return enemy->GetAttackValue(slot);
	}

	// 최종 공격력 계산

	// 최종 공격력 얻기
	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack_Player(int slot)
	{
		return finalAttackArr_player[slot];
	}

	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack_Enemy(int slot)
	{
		return finalAttackArr_enemy[slot];
	}

	// 턴 결과 얻기
	int EMSCRIPTEN_KEEPALIVE Get_Turn_Result(int turnSlot)
	{
		// re <  0 : 플레이어 패배
		// re == 0 : 무승부
		// re >  0 : 플레이어 승리
		return turnResultArr[turnSlot];
	}

	// 전투 결과 얻기
	int EMSCRIPTEN_KEEPALIVE Get_Battle_Result()
	{
		// 둘다 살아있다면 전투 진행 0
		int pHP = player->GetHP();
		int eHP = enemy->GetHP();

		if (pHP <= 0) { return 2; } // 플레이어 HP가 0보다 작다면 패배 2
		if (eHP <= 0) { return 1; } // 플레이어가 살아있고 적 HP가 0보다 작다면 승리 1
		return 0; // 전투 계속 진행
	}

	//다이스 포인트 사용, 반환
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
		
	// 전투 초기화
	void EMSCRIPTEN_KEEPALIVE InitBattleArr()
	{
		// 플레이어, 적 상태 초기화
		
		// 적의 경우 DB로부터 받아온 값을 Enemy에 셋팅한다.
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			finalAttackArr_player[idx] = 0;
			finalAttackArr_enemy[idx] = 0;
			turnResultArr[idx] = 0;
		}

		// 최종 공격 값 계산
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			finalAttackArr_player[idx] = player->GetAttackValue(idx) - enemy->GetDecValue(idx);
			finalAttackArr_enemy[idx]  = enemy->GetAttackValue(idx)  - player->GetDecValue(idx);

			if (finalAttackArr_player[idx] < 0) { finalAttackArr_player[idx] = 0; }
			if (finalAttackArr_enemy[idx]  < 0) { finalAttackArr_enemy[idx] = 0;  }
		}

		// 최종 결과 값 계산
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			turnResultArr[idx] = finalAttackArr_player[idx] - finalAttackArr_enemy[idx];
		}

		// HP 계산
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			int dmg = turnResultArr[idx];

			if (dmg < 0) {
				// 플레이어 데미지
			}
			else if (dmg > 0) {
				// 적 데미지
			}
		}
	}

	

#pragma endregion

	// 적 정보 획득, 설정

#ifdef __cplusplus
}
#endif // __cplusplus
