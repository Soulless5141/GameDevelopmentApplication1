#include "Tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//コンストラクタ
Tama::Tama() : animation_count(0), direction(0.0f),next_flag(false)
{
	for (int i = 0; i <= 3 ; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Tama::~Tama()
{

}

//初期化処理
void Tama::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");//弾1
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");//弾2
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");//弾3
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");//弾4

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("弾の画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 20.0;

	//初期画像の設定
	image = animation[0];

	//enemy_score = -5;

	//生成時の移動方向
	velocity.y = -1;

	mode = 3;
}

//更新処理
void Tama::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

}

//描画処理
void Tama::Draw() const
{
	//ハコテキの画像を描画
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	__super::Draw();
}

//終了時処理
void Tama::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	location = 0;
	delete_flag = true;
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(image);
}

//当たり判定通知処理
void Tama::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	next_flag = true;
	box_size = 0;
	direction = 0.0f;
	velocity.y = 0.0f;
	direction = Vector2D(0.0, 0.0);
}

//移動処理
void Tama::Movement()
{
	//現在の位置座標に速さを加算する
	location += velocity;

	//
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//アニメーション制御
void Tama::AnimeControl()
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