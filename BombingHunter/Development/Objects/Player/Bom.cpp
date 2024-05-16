#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
Bom::Bom() : animation_count(0)
{
	animation[0] = NULL;
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

	//エラーチェック
	if (animation[0] == -1)
	{
		throw("ボムの画像がありません\n");
	}

	//向きの設定
	radian = 0.5;

	//大きさの設定
	scale = 32.0;

	//初期画像の設定
	image = animation[0];
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


	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) * (float)scale / 2.0f);
	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) * (float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Bom::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
}

//当たり判定通知処理
void Bom::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

//移動処理
void Bom::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.5f;

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Bom::AnimeControl()
{
	//画像の切り替え
	/*if (image == animation[0])
	{
		image = animation[1];
	}
	else
	{
		image = animation[0];
	}*/
}
