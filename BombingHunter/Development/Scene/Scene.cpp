#include "Scene.h"
#include"DxLib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Player/Bom.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"

//コンストラクタ
Scene::Scene() : objects(), background_image(NULL), sound(NULL),enemy_count()
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
	CreateObject<Bom>(Vector2D(320.0f, 60.0f));
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
	enemy_count++;

	if (enemy_count >= 500)
	{
		CreateObject<Enemy>(Vector2D(640.0f, 380.0f));
		CreateObject<Enemy>(Vector2D(0.0f, 380.0f));
		enemy_count = 0;
	}

	//zキーを押したら、敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Bom>(Vector2D(100.0f, 60.0f));
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
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