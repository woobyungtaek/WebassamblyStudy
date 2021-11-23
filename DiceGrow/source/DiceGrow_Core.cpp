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

	// �� ���ݷ� ����, ���ݷ� �迭, ����Ʈ ���� �� ���� ����.
	int decArr[4];
	int attackArr[4];

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
		for (int index = 0; index < 4; ++index)
		{
			decArr[index] = 0;
			attackArr[index] = 0;
		}
	}

	int EMSCRIPTEN_KEEPALIVE Get_Dec_Point(int slot)
	{
		// 2��� ����
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

	// ������� Dice����Ʈ�� �����ֳ�.
	// �ش� ���Կ��� ������ ����Ʈ�� �����ֳ�. 
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


	// �� ���� ȹ��, ����

#ifdef __cplusplus
}
#endif // __cplusplus
