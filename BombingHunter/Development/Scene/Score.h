#pragma once

#define MAX_SCORE_DIGIT (10)   //スコアの最大桁数
#define MAX_TIME_DIGIT (3)     //時間の最大桁数
#define MAX_IMAGES (13)        //画像の数

class Score 
{
private:
	class Scene* owner_scene;  //sceneへのアクセス
	int image[MAX_IMAGES];             //最大画像枚数
	int s_omote[MAX_SCORE_DIGIT];      //スコアの最大桁数
	int t_omote[MAX_TIME_DIGIT];       //時間の最大桁数
	int score;                 //スコア
	int time;                  //時間
	int count_time;            //1秒の計算
	int lost_time;             //変動させていい時間
	int value;                 //数字の画像を入れるための変わり

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了処理

	void DamegeFlag();  //プレイヤー被弾処理

	int GetTime();      //時間取得処理

private:
	void ChangeFont();  //UI変更処理
};

