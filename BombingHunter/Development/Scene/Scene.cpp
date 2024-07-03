#include "Scene.h"
#include "math.h"
#include"DxLib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Player/Bom.h"
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Daiya.h"
#include"../Objects/Enemy/Hapyi.h"
#include"../Objects/Enemy/Tama.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER
#define BOM_COOLTIME (50)          //ボムのクールタイム
#define POP_TIME_HANETEKI (200)    //ハーピィの出現時間
#define POP_TIME_HAKOTEKI (1000)   //ハコテキの出現時間
#define POP_TIME_HAPYI (1200)      //ハネテキの出現時間
#define POP_TIME_DAIYA (2500)      //金敵の出現時間
#define SCORE_PERFECT (200000)     //パーフェクトに必要なスコア
#define SCORE_GOOD    (120000)     //グッドに必要なスコア
#define SCORE_OK      (50000)      //OKに必要なスコア
#define MAX_SOUNDS    (6)          //音源数



//コンストラクタ
Scene::Scene() : objects(), background_image(NULL), sounds(), enemy_count(), result_flag(false),image(NULL),
bom_set(TRUE),cool_count(0),mode(NULL),score(0), score_class(nullptr),time(NULL),sound(NULL),
result_score(),result_count()
{

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f), 0.0);

	background_image = LoadGraph("Resource/Images/BackGround.png");

	result_score[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	result_score[1] = LoadGraph("Resource/Images/Evaluation/Perfect.png");
	result_score[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_score[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_score[4] = LoadGraph("Resource/Images/Evaluation/BAD.png");

	sounds[0] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	sounds[1] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_timeup.wav");
	sounds[2] = LoadSoundMem("Resource/Sounds/Evaluation/SE_perfect.wav");
	sounds[3] = LoadSoundMem("Resource/Sounds/Evaluation/SE_good.wav");
	sounds[4] = LoadSoundMem("Resource/Sounds/Evaluation/SE_ok.wav");
	sounds[5] = LoadSoundMem("Resource/Sounds/Evaluation/SE_bad.wav");

	//エラーチェック(音声)
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] == -1)
		{
			throw("sound_naiyo");
		}
	}

	//エラーチェック(リザルト画像)
	for (int i = 0; i < MAX_RESULT; i++)
	{
		if (result_score[i] == -1)
		{
			throw("result_naiyo");
		}
	}

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/Imagezu/to背景2.pngがないです。\n");
	}

	//BGM再生
	PlaySoundMem(sounds[0], DX_PLAYTYPE_LOOP, TRUE);

	//敵の出現頻度リセット
	for (int i = 0;i < ENEMY_KINDS; i++)
	{
		enemy_count[i] = 0;
	}

	//敵の初期生成処理
	if (GetRand(2) == 1)
	{

		CreateObject<Haneteki>(Vector2D(640.0f, 0.0f),0.0);
	}
	else
	{
		CreateObject<Haneteki>(Vector2D(0.0f, 0.0f),0.0);
	}

	//スコアクラスのinitialize
	score_class = new Score(this);
	score_class->Initialize();
}

//更新処理
void Scene::Update()
{
	//現在タイムを取得
	time = score_class->GetTime();
	if (time >= 0)
	{
		//シーンに存在するオブジェクトの更新処理
		for (GameObject* obj : objects)
		{
			obj->Update();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			//敵の攻撃の生成＆向き設定処理
			if (objects[i]->GetAttackFlag() == true)
			{
				//自機に向かう処理
				Vector2D p = objects[0]->GetLocation();
				Vector2D t = objects[i]->GetLocation();
				Vector2D l = Vector2D(p.x - t.x, p.y - t.y);
				int z = sqrt((l.x * l.x) + (l.y * l.y));

				//弾生成処理
				CreateObject<Tama>(objects[i]->GetLocation(), l / z);

			}
		}

		//時間経過で敵の生成
		for (int i = 0; i < ENEMY_KINDS; i++)
		{
			enemy_count[i] += 1;
		}

		//ハネテキ出現頻度
		if (enemy_count[0] >= POP_TIME_HANETEKI)
		{
			if (GetRand(1) == 1)
			{
				CreateObject<Haneteki>(Vector2D(640.0f, 0.0f), 0.0);
			}
			else
			{
				CreateObject<Haneteki>(Vector2D(0.0f, 0.0f), 0.0);
			}
			//生成タイミングをランダムにする
			enemy_count[0] = GetRand(150);
		}

		//ハコテキ出現頻度
		if (enemy_count[1] >= POP_TIME_HAKOTEKI)
		{
			if (GetRand(1) == 1)
			{
				CreateObject<Hakoteki>(Vector2D(640.0f, 390.0f), 0.0);
			}
			else
			{
				CreateObject<Hakoteki>(Vector2D(0.0f, 391.0f), 0.0);
			}
			//生成タイミングをランダムにする
			enemy_count[1] = GetRand(600) + 100;
		}

		//ダイア出現頻度
		if (enemy_count[2] >= POP_TIME_DAIYA)
		{
			if (GetRand(1) == 1)
			{

				CreateObject<Daiya>(Vector2D(640.0f, 400.0f), 0.0);
			}
			else
			{
				CreateObject<Daiya>(Vector2D(0.0f, 400.0f), 0.0);
			}
			//生成タイミングをランダムにする
			enemy_count[2] = (GetRand(1000) + 700);
		}


		//ハーピィ出現頻度
		if (enemy_count[3] >= POP_TIME_HAPYI)
		{
			if (GetRand(1) == 1)
			{

				CreateObject<Hapyi>(Vector2D(640.0f, 0.0f), 0.0);
			}
			else
			{
				CreateObject<Hapyi>(Vector2D(0.0f, 0.0f), 0.0);
			}
			//生成タイミングをランダムにする
			enemy_count[3] = GetRand(200);
		}

		//オブジェクト同士の当たり判定チェック
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				//当たり判定チェック処理 now(preyer,その他)
				HitCheckObject(objects[i], objects[j]);
			}
		}

		//zキーを押したら、ボムを生成する
		if (InputControl::GetKeyDown(KEY_INPUT_Z) && bom_set == TRUE)
		{
			CreateObject<Bom>(objects[0]->GetLocation(), 0.0);
			bom_set = FALSE;
		}

		//ボムのクールタイム設定処理
		if (bom_set == FALSE)
		{
			cool_count++;
			if (cool_count >= BOM_COOLTIME) //ボムのクールタイム
			{
				bom_set = TRUE;  //再装填完了
				cool_count = 0;  //カウントリセット
			}
		}

		//オブジェクトのメモリ開放判定処理
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->DeleteFlag() == true)
			{
				objects.erase(objects.begin() + i);
			}
		}
		//スコアcppのアップデート処理
		score_class->Update();
	}
	else  //タイムが0になったら実行
	{
		if (result_count == 0)
		{
			result_flag = true;
			//サウンドストップ
			DeleteSoundMem(sounds[0]);
			PlaySoundMem(sounds[1], DX_PLAYTYPE_BACK, TRUE);

			//スコアによって評価が変わる
			if (score >= SCORE_PERFECT)    //100000以上パーフェクト
			{
				image = result_score[1];
				sound = sounds[2];
			}
			else if (score >= SCORE_GOOD)  //70000以上グッド
			{
				image = result_score[2];
				sound = sounds[3];
			}
			else if (score >= SCORE_OK)    //10000以上 OK
			{
				image = result_score[3];
				sound = sounds[4];
			}
			else                           //それ例外バッド
			{
				image = result_score[4];
				sound = sounds[5];
			}

			//各オブジェクトを削除する
			for (GameObject* obj : objects)
			{
				obj->Finalize();
				delete obj;
			}

			//動的配列の解放
			objects.clear();
		}

		//リザルトの進行カウント
		result_count++;
	}
}

//描画処理
void Scene::Draw() const
{
	//背景の描画
	DrawExtendGraph(0, 0, 640, 480, background_image, FALSE);

	//シーンに存在するオブジェクトの描画
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	//評価画面の文字描画
	if (result_flag == true && result_count < 500)
	{
		DrawRotaGraph(320, 240, 1.5, 0, result_score[0], TRUE);
	}
	else if (result_flag == true && result_count >= 500)
	{
		DrawRotaGraph(320, 240, 1, 0, image, TRUE);
	}

	//評価に合わせた音を流す
	if (result_count == 500)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);
	}

	//スコアシーンの描画処理
	score_class->Draw();
	
}

//終了時処理
void Scene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);

	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		DeleteSoundMem(sounds[0]);
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

	//スコアクラスの削除
	delete score_class;
}

//現在スコア取得処理
int Scene::GetScore()
{
	return score;
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定をとる)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	int fr, gt;
	fr = a->GetMode(); //0;プレイヤー  1;ボム  2;テキ  3;敵の弾
	gt = b->GetMode(); //0;プレイヤー  1;ボム  2;テキ  3;敵の弾

	//敵とボムがぶつかったらの処理
	if ((fr != gt) && (fr != 0 && gt != 0) && (fr != 3 && gt != 3))
	{
		//2つのオブジェクトの距離を取得
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//2つのオブジェクトの当たり判定の大きさを取得
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

		//距離より大きさが大きい場合、Hit判定とする
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//当たったことをオブジェクトに通知する
			a->OnHitCollision(b);
			b->OnHitCollision(a);

			//スコア加算処理
			if (fr == 2)
			{
				score += a->GetScore();
			}
			else if (gt == 2)
			{
				score += b->GetScore();
			}
			if (score < 0)   //スコアが0以下なら0にする
			{
				score = 0;
			}
		}
	}
	//敵の弾とプレイヤー
	else if (fr == 0 && gt == 3)
	{
		//2つのオブジェクトの距離を取得
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//2つのオブジェクトの当たり判定の大きさを取得
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize());

		//距離より大きさが大きい場合、Hit判定とする
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//当たったことをオブジェクトに通知する
			a->OnHitCollision(b);
			b->OnHitCollision(a);
			score_class->DamegeFlag();   //秒数を減らす
		}
	}
}

#else

//当たり判定チェック処理(左上頂点の座標から当たり判定計算を行う)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右上頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIVOT_CNETER