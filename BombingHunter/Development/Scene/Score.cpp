#include"DxLib.h"
#include "Score.h"
#include "Scene.h"
#include "Time.h"

#define MAX_SCORE (10)
#define MAX_TIME (2)

Score::Score(Scene* owner) : owner_scene(owner), score(0),value(NULL),time(0),lost_time(0)
{
	
	for (int i = 0; i <= 9; i++)
	{
		s_omote[i] = NULL;
	}
	for (int i = 0; i <= 9; i++)
	{
		t_omote[i] = NULL;
	}
	for (int i = 0; i <= 12; i++)
	{
		image[i] = NULL;
	}
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
	time = 9900;

	s_omote[0] = image[0];
	t_omote[0] = image[0];
}

void Score::Update()
{
	time = time - 1;
	this->score = owner_scene->GetScore();

	ChangeFont();
}

void Score::Draw() const
{
	int j = 9;
	int k = 0;

	DrawRotaGraph(180, 460, 1.3, 0, image[10], TRUE);//スコア
	DrawRotaGraph(440, 460, 1.3, 0, image[11], TRUE);//ハイスコア
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

	j = 3;
	k = 0;

	for (int i = 0; i < MAX_TIME; i++)
	{
		if (t_omote[j] != NULL)
		{
			DrawRotaGraph(55 + (k * 18), 460, 0.11, 0, t_omote[j], TRUE);
			k++;
		}
		j--;
	}
}

void Score::Finalize()
{
	
}

void Score::DamegeFlag()
{
	time = time - 200;
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
		t_omote[i] = NULL;
	}

	//スコアが0になるまでフォント変換する
	while (score != 0)
	{
		i = i * 10;       //求めたい位の移動
		value = score % i;   //求めたい桁*10して求める
		value = value / j;      //2桁目以降、余分な桁を消す
		s_omote[k] = image[value]; //フォント変換
		score -= score % i;     //求めた桁を削除()
		j = j * 10;        //余分な桁変更
		k++;          //配列移動
	}

	i = 1;
	j = 1;
	k = 0;

	lost_time = time;

	while (lost_time != 0)
	{
		i = i * 10;
		value = lost_time % i;
		value = value / j;
		t_omote[k] = image[value];
		lost_time -= lost_time % i;
		j = j * 10;
		k++;
	}
	if (s_omote[0] == NULL)
	{
		s_omote[0] = image[0];
	}
	if (t_omote[0] == NULL)
	{
		t_omote[0] = image[0];
	}

}

