#include "Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{

	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Tri-Pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-Pilot/2.png");
	sound = LoadSoundMem("Resource/Sounds/bishi.wav");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 16.0;

	//初期画像の設定
	image = animation[0];

	//オブジェクト設定
	//0;プレイヤー  1;ボム  2;テキ  3;敵の弾
	mode = 0;
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Player::Draw() const
{
	//プレイヤーの画像を描画
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, filp_flag);


	//デバッグ用
//#if _DEBUG
//	//当たり判定の可視化
//	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) * (float)scale / 2.0f);
//	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) * (float)scale / 2.0f);
//
//	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
//		box_collision_lower_right.x, box_collision_lower_right.y,
//		GetColor(255, 0, 0), FALSE);
//#endif
}

//終了時処理
void Player::Finalize()
{
	delete_flag = true;
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}

//移動処理
void Player::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.3f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.3f;
		filp_flag = FALSE;
	}

	//壁判定生成
	if (location.x > 630.0f)
	{
		location.x = 630.0f;
	}
	if (location.x < 10.0f)
	{
		location.x = 10.0f;
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 15)
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
