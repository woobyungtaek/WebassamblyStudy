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

	// �ھ��� �Լ����� ���̵� ����� extern���� ����Ǿ��־�� �Ѵ�.
	// �ھ��� ĳ���� ��ü����.. ���̵� ����� extern���� ����� �����Ѱ�? Ȯ���ʿ�

	// �÷��̾�, �� ��ü ����
	Character* player;
	Character* enemy;

	std::mt19937 gen(time(NULL));
	std::uniform_int_distribution<int> dist(0, 5);

	const int TURN_COUNT = 4;
	int finalAttackArr_player[TURN_COUNT] = { 0, };
	int finalAttackArr_enemy[TURN_COUNT] = { 0, };
	int turnResultArr[TURN_COUNT] = { 0, };

	// �÷��̾�, �� ��ü ���� �� �ʱ�ȭ
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

#pragma region �÷��̾�

	// ü��
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

	// ����
	int EMSCRIPTEN_KEEPALIVE Get_Player_Level()
	{
		if (player == nullptr) { return -1; }
		return player->GetLevel();
	}

	// ����ġ
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

	// ���� ����Ʈ
	int EMSCRIPTEN_KEEPALIVE Get_Player_LevelPoint()
	{
		if (player == nullptr) { return -1; }
		return player->GetLevelPoint();
	}

	// �ֻ���
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

	// �ִ�ü�� ����
	void EMSCRIPTEN_KEEPALIVE IncreaseMaxHP() {
		if (player == nullptr) { return; }
		player->IncreaseMaxHP();
	}

	// �ֻ��� �� ����
	void EMSCRIPTEN_KEEPALIVE IncreaseDiceValue(int slot) {
		if (player == nullptr) { return; }
		if (slot < 0 || slot >= 6) { return; }
		player->IncreaseDiceValue(slot);
	}

#pragma endregion

#pragma region �ֻ��� ������

	// ���� ���� �̱�, �������� �ؾ��� ��
	int EMSCRIPTEN_KEEPALIVE Get_Random_Dice_Point()
	{
		if (player == nullptr) { return 0; }
		int slot = dist(gen);
		player->SetDicePoint(slot);
		return player->GetDice(slot);
	}

#pragma endregion


#pragma region ���� �غ� & ����

	// �÷��̾� ����, �� ���� ��ġ ���
	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point_Player(int slot)
	{
		return player->GetDecValue(slot);
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point_Player(int slot)
	{
		return player->GetAttackValue(slot);
	}

	//  �� ����, �÷��̾� ���� ��ġ ���
	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point_Enemy(int slot)
	{
		return enemy->GetDecValue(slot);
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point_Enemy(int slot)
	{
		return enemy->GetAttackValue(slot);
	}

	// ���� ���ݷ� ���

	// ���� ���ݷ� ���
	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack_Player(int slot)
	{
		return finalAttackArr_player[slot];
	}

	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack_Enemy(int slot)
	{
		return finalAttackArr_enemy[slot];
	}

	// �� ��� ���
	int EMSCRIPTEN_KEEPALIVE Get_Turn_Result(int turnSlot)
	{
		// re <  0 : �÷��̾� �й�
		// re == 0 : ���º�
		// re >  0 : �÷��̾� �¸�
		return turnResultArr[turnSlot];
	}

	// ���� ��� ���
	int EMSCRIPTEN_KEEPALIVE Get_Battle_Result()
	{
		// �Ѵ� ����ִٸ� ���� ���� 0
		int pHP = player->GetHP();
		int eHP = enemy->GetHP();

		if (pHP <= 0) { return 2; } // �÷��̾� HP�� 0���� �۴ٸ� �й� 2
		if (eHP <= 0) { return 1; } // �÷��̾ ����ְ� �� HP�� 0���� �۴ٸ� �¸� 1
		return 0; // ���� ��� ����
	}

	//���̽� ����Ʈ ���, ��ȯ
	void UseDicePoint(int value)
	{
		if (player == nullptr) { return; }

		player->UseDicePoint(value);
	}

	// SlotPoint ����
	void EMSCRIPTEN_KEEPALIVE IncreaseSlotPoint(int slotType, int slotNum)
	{
		if (player == nullptr) { return; }

		// Dice����Ʈ�� �����ִ��� Ȯ���Ѵ�.
		if (player->GetDicePoint() <= 0) { return; }

		// type [0:EnemyAttackDec][1:PlayerAttack]
		// type�� Ȯ���Ѵ�.
		if (slotType == 0) { player->SetDecArr(slotNum, 1); }
		else if (slotType == 1) { player->SetAttackArr(slotNum, 1); }
		else { return; }

		// DicePoint ����
		player->UseDicePoint(-1);

	}

	// SlotPoint ����
	void EMSCRIPTEN_KEEPALIVE DecreaseSlotPoint(int slotType, int slotNum)
	{
		if (player == nullptr) { return; }

		// type [0:EnemyAttackDec][1:PlayerAttack]
		// type�� Ȯ���Ѵ�.
		// slot Ȯ�� �� 0���� ũ�� ����
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

		// DicePoint ����
		player->UseDicePoint(1);
	}
		
	// ���� �ʱ�ȭ
	void EMSCRIPTEN_KEEPALIVE InitBattleArr()
	{
		// �÷��̾�, �� ���� �ʱ�ȭ
		
		// ���� ��� DB�κ��� �޾ƿ� ���� Enemy�� �����Ѵ�.
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			finalAttackArr_player[idx] = 0;
			finalAttackArr_enemy[idx] = 0;
			turnResultArr[idx] = 0;
		}

		// ���� ���� �� ���
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			finalAttackArr_player[idx] = player->GetAttackValue(idx) - enemy->GetDecValue(idx);
			finalAttackArr_enemy[idx]  = enemy->GetAttackValue(idx)  - player->GetDecValue(idx);

			if (finalAttackArr_player[idx] < 0) { finalAttackArr_player[idx] = 0; }
			if (finalAttackArr_enemy[idx]  < 0) { finalAttackArr_enemy[idx] = 0;  }
		}

		// ���� ��� �� ���
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			turnResultArr[idx] = finalAttackArr_player[idx] - finalAttackArr_enemy[idx];
		}

		// HP ���
		for (int idx = 0; idx < TURN_COUNT; ++idx)
		{
			int dmg = turnResultArr[idx];

			if (dmg < 0) {
				// �÷��̾� ������
			}
			else if (dmg > 0) {
				// �� ������
			}
		}
	}

	

#pragma endregion

	// �� ���� ȹ��, ����

#ifdef __cplusplus
}
#endif // __cplusplus
