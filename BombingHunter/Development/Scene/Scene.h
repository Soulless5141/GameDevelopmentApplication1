#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include "Score.h"

class Scene
{
private:
	int background_image;
	int sound;
	int enemy_count[4];
	int bom_set;
	int cool_count;
	int mode;
	int score;
	int attack_flag;

	std::vector<GameObject*>objects;
	Score* score_class;

public:
	Scene();
	~Scene();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

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
		new_object->GetVelocity(velocity);
		//初期化処理
		new_object->Initialize();

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;

	}
};

