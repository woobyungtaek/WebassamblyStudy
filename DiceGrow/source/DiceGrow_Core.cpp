#include <cstdlib>
#include <iostream>
#include <emscripten.h>
#include "Character.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	// �ھ��� �Լ����� ���̵� ����� extern���� ����Ǿ��־�� �Ѵ�.

	// �÷��̾�, �� ��ü ����
	Character* player;
	Character* enemy;

	// �÷��̾�, �� ��ü ���� �� �ʱ�ȭ
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


	// �� ���� ȹ��, ����

#ifdef __cplusplus
}
#endif // __cplusplus
