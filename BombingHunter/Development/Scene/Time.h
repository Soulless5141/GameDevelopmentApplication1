#pragma once
class Time
{
private:
	Score* score_class;
	class Scene* owner_scene;
	int time;

public:
	Time();
	/*Time();*/
	~Time();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

	int GetTime();

	void DamegeFlag();

private:
	
};

