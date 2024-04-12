#include "Scene.h"

#include"../Objects/Player/Player.h"

//コンストラクタ
Scene::Scene() : objects()
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
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

//更新処理