#pragma once

//#include "Time.h"

class Score 
{
private:
	class Scene* owner_scene;
	int image[13];
	int s_omote[10];
	int t_omote[10];
	int score;
	int time;
	int count_time;
	int lost_time;
	int value;

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

	void DamegeFlag();

private:
	void ChangeFont();
};

