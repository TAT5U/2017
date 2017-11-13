/*Player.cpp*/

#include "Player.h"

//staticなので外部で宣言
TCHAR Player::name[4][128];

Player::Player()
{
}


Player::~Player()
{
}

//プレイヤー作成
Player **Player::Create()
{
	int count = 0, posX = 50;
	static Player *player[4];
	while (count < PLAYER_MAX)
	{
		player[count]->PlayerScore(name[count], count, player[count]);
		player[count] = static_cast<Player*>(Label::Create(name[count], "MS ゴシック", 20));
		player[count]->SetAnchorPoint(0, 0);
		player[count]->SetPosition(posX, g.WINDOW_HEIGHT / 12);
		posX += player[count]->GetSize().x * 2;
		count++;
	}

	return player;
}

//プレイヤーの名前とスコアを表示
void Player::PlayerScore(TCHAR *label, int count, Player *player)
{
	wsprintf(label, TEXT("プレイヤー%d\n       %d     "), count + 1, player->GetScore(count));
}

//プレイヤーのスコアをセット
void Player::SetPlayerScore(Player *player, int count)
{
	player->PlayerScore(name[count], count, player);
	player->SetString(player->name[count]);
}
