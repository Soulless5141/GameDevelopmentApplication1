#include"DxLib.h"
#include "Score.h"
#include "Scene.h"

Score::Score(Scene* owner) : owner_scene(owner), score(0),value(NULL)
{
	for (int i = 0; i <= 10; i++)
	{
		image[i] = NULL;
	}
	for (int i = 0; i <= 9; i++)
	{
		omote[i] = NULL;
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

	score = 0;

	omote[0] = image[0];
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

	DrawRotaGraph(50, 460, 1.3, 0, image[10], TRUE);//スコア

	for (int i = 0; i < 10; i++)
	{
		if (omote[j] != NULL)
		{
			DrawRotaGraph(100 + (k * 20), 460, 0.1, 0, omote[j], TRUE);
			k++;
		}
		j--;
	}
}

void Score::Finalize()
{

}

void Score::ChangeFont()
{
	int i = 1;
	int j = 1;
	int k = 0;

	for (int i = 0; i <= 9; i++)
	{
		omote[i] = NULL;
	}

	while (score != 0)
	{
		i = i * 10;
		value = score % i;
		value = value / j;
		omote[k] = image[value];
		score -= score % i;
		j = j * 10;
		k++;
	}
	if (omote[0] == NULL)
	{
		omote[0] = image[0];
	}

}

