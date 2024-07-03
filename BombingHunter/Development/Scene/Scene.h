#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include "Score.h"

#define ENEMY_KINDS   (4)//敵の数
#define MAX_RESULT    (5)//リザルト画像数

class Scene
{
private:
	int background_image;  //背景画像
	int sounds[6];         //音源
	int sound;             //再生用音源
	int enemy_count[ENEMY_KINDS];    //敵の出現頻度
	int bom_set;           //ボムの発射フラグ
	int cool_count;        //ボムのクールタイム
	int mode;              //オブジェクト識別番号
	int score;             //スコア
	int time;              //時間
	int result_count;      //リザルトの進行時間
	int result_score[MAX_RESULT];   //リザルトの画像
	int image;             //代入用画像変数
	bool result_flag;      //リザルト繊維フラグ

	std::vector<GameObject*>objects;
	Score* score_class;

public:
	Scene();
	~Scene();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

	//倒した敵のスコア情報取得処理
	int GetScore();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

private:
	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location, const Vector2D& velocity)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//位置情報の設定
		new_object->SetLocation(location);
		//進行方向取得処理
		new_object->GetVelocity(velocity);
		//初期化処理
		new_object->Initialize();

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;

	}
};

