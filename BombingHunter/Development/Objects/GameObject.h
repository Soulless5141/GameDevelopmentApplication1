#pragma once

#include"../Utility/Vector2D.h"

#define D_PIVOT_CENTER     //座標の原点を画像の中心にする

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;   //位置情報
	Vector2D box_size;        //矩形大きさ
	double scale;        //大きさ
	double radian;       //向き
	int image;           //描画する画像
	int sound;           //再生する音源
	int mode;            //0;プレイヤー  1;ボム  2;テキ  3;敵の弾
	int delete_flag;     //メモリ開放判定処理
	int enemy_score;     //各敵のスコア設定変数
	int attack_flag;     //攻撃判定
	//移動の速さ
	Vector2D velocity = 0.0f;  //デフォルトの動き設定

public:
	GameObject();
	virtual~GameObject();

	virtual void Initialize();  //初期化処理
	virtual void Update();      //更新処理
	virtual void Draw() const;  //描画処理
	virtual void Finalize();    //終了処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	int GetMode();         //オブジェクトモード取得処理
	bool DeleteFlag();     //メモリ開放フラグ取得処理
	int GetScore();        //各敵のスコア取得処理
	bool GetAttackFlag();  //攻撃判定取得処理

	void GetVelocity(const Vector2D& velocity);  //進行方向取得処理
};