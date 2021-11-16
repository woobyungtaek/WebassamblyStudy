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

public:
	void IncreaseMaxHP();
	void IncreaseDiceValue(int slot);
};