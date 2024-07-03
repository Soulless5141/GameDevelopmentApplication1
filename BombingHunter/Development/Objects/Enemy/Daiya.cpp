#include "Daiya.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"
#include"stdlib.h"

//コンストラクタ
Daiya::Daiya() : animation_count(0), direction(0.0f)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Daiya::~Daiya()
{

}

//初期化処理
void Daiya::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");//ダイア1
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");//ダイア2
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");//ダイア3
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");//ダイア4
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");//ダイア5


	//エラーチェック
	for (int i = 0; i < 5; i++)
	{
		if (animation[i] == -1)
		{
			throw("ダイヤの画像がありません\n");
		}
	}
	
	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 40.0;

	//初期画像の設定
	image = animation[0];
	
	//スコア設定
	enemy_score = 77777;

	//生成時の移動方向&速度ランダム
	if (location.x <= 300.0f)
	{
		velocity.x = GetRand(7) / 10.0f + 0.3f;
	}
	else
	{
		velocity.x = -(GetRand(7) / 10.0f + 0.3);
	}

	//オブジェクト設定
	//0;プレイヤー  1;ボム  2;テキ  3;敵の弾
	mode = 2;
}

//更新処理
void Daiya::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

}

//描画処理
void Daiya::Draw() const
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

	//ダイアの画像を描画
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//終了時処理
void Daiya::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	delete_flag = true;
	//使用した画像を開放する
	for (int i = 0; i <= 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	//メモリ開放
	DeleteGraph(image);
}

//当たり判定通知処理
void Daiya::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	Finalize();
}

//移動処理
void Daiya::Movement()
{
	//現在の位置座標に速さを加算する
	location += velocity;

	//画面外に行くと消える
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//アニメーション制御
void Daiya::AnimeControl()
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
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else if (image == animation[4])
		{
			image = animation[0];
		}
	}
}