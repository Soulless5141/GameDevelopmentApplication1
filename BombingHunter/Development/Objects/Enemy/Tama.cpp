#include "Tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//コンストラクタ
Tama::Tama() : animation_count(0), direction(0.0f)
{

}

//デストラクタ
Tama::~Tama()
{

}

//初期化処理
void Tama::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Imagezu/eff1.png");//弾1
	animation[1] = LoadGraph("Resource/Imagezu/eff2.png");//弾2
	animation[2] = LoadGraph("Resource/Imagezu/eff3.png");//弾3
	animation[3] = LoadGraph("Resource/Imagezu/eff4.png");//弾4

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

	enemy_score = -5;

	//生成時の移動方向
	velocity = 1;

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
	//GetScore();
	//当たった時の処理
	Finalize();
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