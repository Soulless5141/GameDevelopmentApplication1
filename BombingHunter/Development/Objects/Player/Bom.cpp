#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"Player.h"

//コンストラクタ
Bom::Bom() : animation_count(0), bom_count(0),next_flag(false)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Bom::~Bom()
{

}

//初期化処理
void Bom::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Imagezu/爆弾.png");
	animation[1] = LoadGraph("Resource/Imagezu/baku1.png");
	animation[2] = LoadGraph("Resource/Imagezu/baku2.png");
	animation[3] = LoadGraph("Resource/Imagezu/baku3.png");

	//エラーチェック
	if (animation[0] == -1)
	{
		throw("ボムの画像がありません\n");
	}
	if (animation[1] == -1)
	{
		throw("ボムの画像がありません\n");
	}

	//向きの設定
	radian = 90 * 3.14 / 180;

	//大きさの設定
	box_size = 32.0;

	//初期画像の設定
	image = animation[0];

	mode = 1;

	//爆発モーションに移っていいかの確認
	next_flag = false;

	direction = Vector2D(0.0, 1.5);

	enemy_score = 0;

}

//更新処理
void Bom::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Bom::Draw() const
{
	//プレイヤーの画像を描画
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	__super::Draw();
}

//終了時処理
void Bom::Finalize()
{
	box_size = 0;
	location = 0;
	delete_flag = true;
	//使用した画像を開放する
	DeleteGraph(image);
}

//当たり判定通知処理
void Bom::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	next_flag = true;
	direction = 0.0f;
	Vector2D velocity = 0.0f;
}

//移動処理
void Bom::Movement()
{
	//現在の位置座標に速さを加算する
	location += direction;

	if (location.y >= 410)
	{
		next_flag = true;
		direction = 0.0f;
	}
}

//アニメーション制御
void Bom::AnimeControl()
{
	//画像の切り替え
	if (next_flag == true)
	{
		animation_count++;
		if (image == animation[0])
		{
			box_size = 0;
			radian = 0;
			image = animation[1];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[1])
		{
			image = animation[2];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[2])
		{
			image = animation[3];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[3])
		{
			Finalize();
		}
	}
}
	

//void Bom::Func(Vector2D player)
//{
//	player = 0;
//}
