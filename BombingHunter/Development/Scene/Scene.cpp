#include "Scene.h"
#include"DxLib.h"
#include"stdlib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Player/Bom.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(), background_image(NULL), sound(NULL),enemy_count(),bom_set(TRUE),bom_count(0),mode(NULL)
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
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//CreateObject<Bom>(Vector2D(320.0f, 60.0f));
	CreateObject<Enemy>(Vector2D(640.0f, 380.0f));    //ハコテキ右から
	CreateObject<Enemy>(Vector2D(0.0f, 380.0f));      //ハコテキ左から

	background_image = LoadGraph("Resource/Imagezu/背景2.png");

	sound = LoadSoundMem("Resource/Imagezu/BGM_arrows.wav");

	if (sound == -1)
	{
		throw("ne-yo");
	}

	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/Imagezu/to背景2.pngがないです。\n");
	}

	enemy_count = 0;
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//時間経過で敵の生成
	enemy_count++;
	if (enemy_count >= 600)
	{
		CreateObject<Enemy>(Vector2D(640.0f, 380.0f));
		CreateObject<Enemy>(Vector2D(0.0f, 381.0f));
		enemy_count = ((rand() % 300) + 200);
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
		//CreateObject<Bom>(Vector2D())->Func();
		CreateObject<Bom>(objects[0]->GetLocation());
		//CreateObject<Bom>(Vector2D(50,50));
		bom_set = FALSE;
	}

	if (InputControl::GetKey(KEY_INPUT_X) && bom_set == TRUE)
	{
		CreateObject<Bom>(objects[0]->GetLocation());
	}

	if (bom_set == FALSE)
	{
		bom_count++;
		if (bom_count >= 0)
		{
			bom_set = TRUE;
			bom_count = 0;
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteFlag() == true)
		{
			objects.erase(objects.begin() + i);
		}
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
		DeleteSoundMem(sound);
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定をとる)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	int fr, gt;
	fr = a->GetMode();
	gt = b->GetMode();

	if ((fr != gt) && (fr != 0 && gt != 0) )
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