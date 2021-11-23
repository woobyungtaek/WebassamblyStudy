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

public:
	// ���� �� ����Ʈ
	void IncreaseMaxHP();
	void IncreaseDiceValue(int slot);

	// �ֻ��� ����Ʈ
	void SetDicePoint(int slot); // �ֻ��� ����Ʈ ����
	void UseDicePoint(int value); // �ֻ��� ����Ʈ ���, ��ȯ

};