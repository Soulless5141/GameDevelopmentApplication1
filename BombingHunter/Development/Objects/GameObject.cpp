#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0),
	radian(0.0),
	image(0),
	sound(0),
	scale(0),
	mode(0),
	delete_flag(false),
	enemy_score(NULL),
	attack_flag(false)
{

}

//デストラクタ
GameObject::~GameObject()
{
	
}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{
	//当たり判定の可視化
//#ifdef D_PIVOT_CENTER
//
//	Vector2D tl = location - (box_size / 2.0f);
//	Vector2D br = location + (box_size / 2.0f);
//
//	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#else
//	Vector2D tl = location;
//	Vector2D br = location + box_size;
//
//	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#endif  // D_PIVOT_CENTER
}

//終了処理
void GameObject::Finalize()
{
	
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	Finalize();
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//敵の大きさ取得処理
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//オブジェクトの種類取得処理
int GameObject::GetMode()
{
	return mode;
}

//削除フラグ処理
bool GameObject::DeleteFlag()
{
	return delete_flag;
}

//倒した敵のスコア取得処理
int GameObject::GetScore()
{
	return enemy_score;
}

//敵の攻撃判定処理
bool GameObject::GetAttackFlag()
{
	return attack_flag;
}

//初期動作情報取得処理
void GameObject::GetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}