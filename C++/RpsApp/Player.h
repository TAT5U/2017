class player
{
public:
	//コンストラクタ
	player();

	//デストラクタ
	~player();

	//手を出す
	int showHand();

	//勝った回数を答える
	int getWinCount();

	//審判から結果を受け取る
	void notifyResult(bool result);
private:

	//勝ち数を数える変数
	int winCount;

	//手を格納する変数
	int n;

	//擬似乱数生成関数
	int GetRnd(int min, int max);
};