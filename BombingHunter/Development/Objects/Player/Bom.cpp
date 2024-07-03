#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"
#include"Player.h"

//コンストラクタ
Bom::Bom() : animation_count(0),next_flag(false)
{
	for (int i = 0; i < ANIMATION_IMAGES; i++)
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
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//画像の読み込み
	tmp = rm->GetImages("Resource/Images/Bomb/Bomb.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/1.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/2.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/3.png");
	animation_data.push_back(tmp[0]);

	//音源の読み込み
	tmp = rm->GetSounds("Resource/Sounds/explosion.wav");
	sounds_data.push_back(tmp[0]);

	sound = sounds_data[0];

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("ボムの画像がありません\n");
	}

	//左移動しながら撃った設定
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		//向きの設定
		radian = 180 * 3.14 / 180;
		//初期移動設定
		direction = Vector2D(-1.4, 1.7); 
	}
	//右移動しながら撃った設定
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		//向きの設定
		radian = 0 * 3.14 / 180;
		//初期移動設定
		direction = Vector2D(1.4, 1.7);
	}
	//止まって撃ったら
	else
	{
		//向きの設定
		radian = 90 * 3.14 / 180;
		//初期移動設定
		direction = Vector2D(0, 1.5);
	}

	//大きさの設定
	box_size = 32.0;

	//初期画像の設定
	image = animation_data[0];

	//オブジェクト設定
	//0;プレイヤー  1;ボム  2;テキ  3;敵の弾
	mode = 1;

	//爆発モーションに移っていいかの確認
	next_flag = false;

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
	//メモリ開放フラグ
	delete_flag = true;
	//使用した画像や音源を開放する
	DeleteGraph(image);
	DeleteSoundMem(sounds_data[0]);
}

//当たり判定通知処理
void Bom::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	next_flag = true;
	box_size = 0;
	direction = 0.0f;
	/*Vector2D velocity = 0.0f;*/
	direction = Vector2D(0.0, 0.0);
}

//移動処理
void Bom::Movement()
{
	//現在の位置座標に速さを加算する
	location += direction;

	//一定座標到達後、起爆モーション
	if (location.y >= 410)
	{
		next_flag = true;  //起爆アニメーションにする
		direction = 0.0f;  //座標を止める
	}

	//カーブスローした時の動き
	if (direction.x < 0 && image == animation_data[0])
	{
		direction.x = direction.x + (1.2/ 90);
	}
	if (direction.x > 0 && image == animation_data[0])
	{
		direction.x = direction.x - (1.2 / 90);
	}
}

//アニメーション制御
void Bom::AnimeControl()
{
	//カーブスローした時の見た目
	if (radian < 90 * 3.14 / 180 && image == animation_data[0])
	{
		radian = radian + (1 * 3.14 / 180);
	}
	if (radian > 90 * 3.14 / 180 && image == animation_data[0])
	{
		radian = radian - (1 * 3.14 / 180);
	}

	//爆破した時の画像の切り替え
	if (next_flag == true)
	{
		animation_count++;

		if (image == animation_data[0])
		{
			box_size = 0;
			radian = 0;
			image = animation_data[1];
			animation_count = 0;
			PlaySoundMem(sounds_data[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (animation_count >= 10 && image == animation_data[1])
		{
			image = animation_data[2];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation_data[2])
		{
			image = animation_data[3];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation_data[3])
		{
			DeleteGraph(image);
		}
		if (animation_count > 100)  //音源が再生しきったら終了処理
		{
			Finalize();
		}
	}
}
	

