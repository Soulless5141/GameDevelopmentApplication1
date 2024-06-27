#include "Hapyi.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//コンストラクタ
Hapyi::Hapyi() : animation_count(0), direction(0.0f),ptn(GetRand(2)),animation()
{
	
}

//デストラクタ
Hapyi::~Hapyi()
{

}

//初期化処理
void Hapyi::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");//ハーピィ1
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");//ハーピィ1

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハーピィの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];
	
	switch (ptn)
	{
	case 1:
		location.y = 140;
		break;
	case 2:
		location.y = 230;
		break;
	default:
		location.y = 320;
		break;
	}

	enemy_score = -3000;
	

	//生成時の移動方向
	if (location.x <= 300.0f)
	{
		velocity.x = (rand() % 6) / 10.0f + 0.5f;
	}
	else
	{
		velocity.x = -((rand() % 6) / 10.0f + 0.5);
	}

	mode = 2;
}

//更新処理
void Hapyi::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

}

//描画処理
void Hapyi::Draw() const
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
void Hapyi::Finalize()
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
void Hapyi::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	Finalize();
}

//移動処理
void Hapyi::Movement()
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
void Hapyi::AnimeControl()
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
		else if (image == animation[1])
		{
			image = animation[0];
		}
	}
}