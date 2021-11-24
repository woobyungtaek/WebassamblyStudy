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

	int finalAttackValue[8] = { 0, };

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


#pragma region ���� �غ�


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
		// 0~3 : �� ui, 4~7 : �÷��̾� ui

		if (slot < 4)
		{
			// ��
			return enemy->GetDecValue(slot);
		}
		else
		{
			//�÷��̾�
			return player->GetDecValue(slot - 4);
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Attack_Point(int slot)
	{
		// 0~3 : �� ui, 4~7 : �÷��̾� ui

		if (slot < 4)
		{
			// ��
			return enemy->GetAttackValue(slot);
		}
		else
		{
			//�÷��̾�
			return player->GetAttackValue(slot - 4);
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Final_Attack(int slot)
	{
		// 0~3 : �� ui, 4~7 : �÷��̾� ui
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
		// 0~3 : �� ���� ���ݷ�, 4~7 : �÷��̾� ���� ���ݷ�
		// turnSlot : 0 ~ 3��
		// turnSlot+4

		// re <  0 : �÷��̾� �й�
		// re == 0 : ���º�
		// re >  0 : �÷��̾� �¸�
		return finalAttackValue[turnSlot + 4] - finalAttackValue[turnSlot];
	}

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

#pragma endregion

#pragma region ����

	// ���� ���·� �ʱ�ȭ

	// 

#pragma endregion


	// �� ���� ȹ��, ����

#ifdef __cplusplus
}
#endif // __cplusplus
