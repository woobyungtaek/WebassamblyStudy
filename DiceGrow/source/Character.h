class Character
{
public:
	Character();
	~Character();

private:
	int mHP;
	int mMaxHP;

	int mLevel;
	int mCurrentExp;
	int mExp;

	int mDice[6] = { 0, };

public:
	void Init();
};