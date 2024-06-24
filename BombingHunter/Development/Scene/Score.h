#pragma once

class Score 
{
private:
	class Scene* owner_scene;
	int image[11];
	int omote[10];
	int score;
	int value;

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

private:
	void ChangeFont();
};

