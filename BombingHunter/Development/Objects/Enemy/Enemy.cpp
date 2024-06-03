#include "Enemy.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Imagezu/1 (1).png");
	animation[1] = LoadGraph("Resource/Imagezu/2 (1).png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];

	//生成時の移動方向
	if (location.x <= 300.0f)
	{
		velocity.x = 1.0f;
	}
	else 
	{
		velocity.x = -1.0f;
	}

	mode = 2;
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

}

//描画処理
void Enemy::Draw() const
{
	//画面反転フラグ(FALSE=右　TURE=左)
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//ハコテキの画像を描画
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	location = 0;
	delete_flag = true;
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	Finalize();
}

//移動処理
void Enemy::Movement()
{
	/*if (location.x > 640.0f || location.x<-10.0f)
	{
		velocity.x *= -1;
	}*/

	//現在の位置座標に速さを加算する
	location += velocity;

	//
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//アニメーション制御
void Enemy::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
