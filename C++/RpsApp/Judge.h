class judge
{
public:
	//コンストラクタ
	judge();

	//デストラクタ
	~judge();

	//ジャンケンの判定
	void Judgement(int pl1,int pl2);

	//最終結果の判定
	void WinnerJudge();

	//ゲーム進行
	void Disp();
private:

	//勝負数を数える変数
	int i;

	//プレイヤー1の手を格納する変数
	int p1;

	//プレイヤー2の手を格納する変数
	int p2;
};