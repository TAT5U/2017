#include<string>
using namespace std;
class player
{
public:
	//引数付きコンストラクタ
	//プレイヤーの名前設定
	player(string _name);

	//デストラクタ
	~player();

	//手を出す
	int showHand();

	//勝った回数を答える
	int getWinCount();

	//審判から結果を受け取る
	void notifyResult(bool result);

	string getName();
private:

	//勝ち数を数える変数
	int winCount;

	//手を格納する変数
	int n;

	//擬似乱数生成関数
	int GetRnd(int min, int max);

	string name;
};