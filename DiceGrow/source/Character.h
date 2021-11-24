class Character
{
public:
	Character();
	~Character();

private:
	int mHP;
	int mMaxHP;
		
	int mLevel;
	int mExp;
	int mMaxExp;
	
	int mLevelPoint;

	int mDice[6] = { 0, };

	int mDicePoint;
	int mMaxPoint;

	int mDecArr[4] = { 0, };
	int mAttackArr[4] = { 0, };

public:
	void Init();

public:
	int GetHP();
	int GetMaxHP();

	int GetLevel();

	int GetExp();
	int GetMaxExp();

	int GetLevelPoint();

	int GetDice(int slot);
	int GetDicePoint();

	int GetDecValue(int slot);
	int GetAttackValue(int slot);

public:
	// ���� �� ����Ʈ
	void IncreaseMaxHP();
	void IncreaseDiceValue(int slot);

	// �ֻ��� ����Ʈ
	void SetDicePoint(int slot); // �ֻ��� ����Ʈ ����
	void UseDicePoint(int value); // �ֻ��� ����Ʈ ���, ��ȯ

	void ResetBattleArr();
	void SetDecArr(int slot, int value);
	void SetAttackArr(int slot, int value);

};