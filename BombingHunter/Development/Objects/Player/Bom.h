#pragma once

#include "vector"

#include"../GameObject.h"

#define ANIMATION_IMAGES (4) //画像枚数

class Bom :public GameObject
{
private:
	int animation[ANIMATION_IMAGES];      //アニメーション画像
	int animation_count;   //アニメーション変更時間
	bool next_flag;        //爆破モーションに移行判定
	Vector2D direction;    //進行方向

	std::vector<int> animation_data;  //アニメーションデータ
	std::vector<int> sounds_data;  //アニメーションデータ

public:
	Bom();
	~Bom();

	virtual void Initialize() override;  //初期化処理
	virtual void Update() override;      //更新処理
	virtual void Draw() const override;  //描画処理
	virtual void Finalize() override;    //終了時処理
	

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimeControl();
};

