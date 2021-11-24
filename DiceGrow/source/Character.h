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
	// 레벨 업 포인트
	void IncreaseMaxHP();
	void IncreaseDiceValue(int slot);

	// 주사위 포인트
	void SetDicePoint(int slot); // 주사위 포인트 설정
	void UseDicePoint(int value); // 주사위 포인트 사용, 반환

	void ResetBattleArr();
	void SetDecArr(int slot, int value);
	void SetAttackArr(int slot, int value);

};