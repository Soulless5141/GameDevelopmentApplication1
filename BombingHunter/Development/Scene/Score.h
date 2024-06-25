#pragma once

class Score 
{
private:
	class Scene* owner_scene;
	class Time* owner_time;
	int image[13];
	int s_omote[10];
	int t_omote[3];
	int score;
	int value;

public:
	Score(class Scene* owner);
	Score(class Time* time);
	~Score();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

private:
	void ChangeFont();
};

