#include"DxLib.h"
#include "Score.h"
#include "Scene.h"
#include "time.h"

#define MAX_SCORE (10)
#define MAX_TIME (2)

Score::Score(Scene* owner) : owner_scene(owner), score(0),value(NULL)
{
	for (int i = 0; i <= 12; i++)
	{
		image[i] = NULL;
	}
	for (int i = 0; i <= 9; i++)
	{
		s_omote[i] = NULL;
	}
}

Score::Score(Time* time) : owner_time(time)
{
	
}

//デストラクタ
Score::~Score()
{
	//忘れ防止
	Finalize();
}

void Score::Initialize()
{
	LoadDivGraph("Resource/Images/Score/ScoreAll.png", 10, 5, 2, 160, 214, image);
	image[10] = LoadGraph("Resource/Images/Score/font-21.png");
	image[11] = LoadGraph("Resource/Images/Score/hs.png");
	image[12] = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	score = 0;

	s_omote[0] = image[0];
}

void Score::Update()
{
	this->score = owner_scene->GetScore();

	ChangeFont();
}

void Score::Draw() const
{
	int j = 9;
	int k = 0;

	DrawRotaGraph(180, 460, 1.3, 0, image[10], TRUE);//スコア
	DrawRotaGraph(460, 460, 1.3, 0, image[11], TRUE);//ハイスコア
	DrawRotaGraph(20, 460, 0.5, 0, image[12], TRUE);//タイマーイラスト

	for (int i = 0; i < MAX_SCORE; i++)
	{
		if (s_omote[j] != NULL)
		{
			DrawRotaGraph(225 + (k * 18), 460, 0.11, 0, s_omote[j], TRUE);
			k++;
		}
		j--;
	}
}

void Score::Finalize()
{

}

//数字のUI変更処理
void Score::ChangeFont()
{
	int i = 1;
	int j = 1;
	int k = 0;

	for (int i = 0; i <= 9; i++)
	{
		s_omote[i] = NULL;
	}

	while (score != 0)
	{
		i = i * 10;
		value = score % i;
		value = value / j;
		s_omote[k] = image[value];
		score -= score % i;
		j = j * 10;
		k++;
	}
	if (s_omote[0] == NULL)
	{
		s_omote[0] = image[0];
	}

}

