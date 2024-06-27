#include"DxLib.h"
#include "Score.h"
#include "Scene.h"
#include "Time.h"

#define MAX_SCORE (10)
#define MAX_TIME (2)

Score::Score(Scene* owner) : owner_scene(owner), score(0),value(NULL),time(0),lost_time(0),count_time(0)
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

//�f�X�g���N�^
Score::~Score()
{
	//�Y��h�~
	Finalize();
}

void Score::Initialize()
{
	LoadDivGraph("Resource/Images/Score/ScoreAll.png", 10, 5, 2, 160, 214, image);
	image[10] = LoadGraph("Resource/Images/Score/font-21.png");
	image[11] = LoadGraph("Resource/Images/Score/hs.png");
	image[12] = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	score = 0;
	time = 60;
	count_time = 0;

	s_omote[0] = image[0];    //�X�R�A��UI�����ݒ�
	t_omote[0] = image[0];    //�^�C����UI�����ݒ�
}

void Score::Update()
{
	count_time++;
	
	if (count_time >= 144)
	{
		time--;
		count_time = 0;
	}

	//�V�[��cpp����X�R�A�̏��������Ă���
	this->score = owner_scene->GetScore();

	//�󂯎�����l����ɁAUI�ݒ�
	ChangeFont();
}

void Score::Draw() const
{
	int j = 9;     //�����̌�납��\��(��Ԍ��ɂ���)
	int k = 0;

	DrawRotaGraph(180, 460, 1.3, 0, image[10], TRUE);//�X�R�A
	DrawRotaGraph(440, 460, 1.3, 0, image[11], TRUE);//�n�C�X�R�A
	DrawRotaGraph(20, 460, 0.5, 0, image[12], TRUE);//�^�C�}�[�C���X�g

	//�X�R�A�̕`�揈��
	for (int i = 0; i < MAX_SCORE; i++)
	{
		if (s_omote[j] != NULL)
		{
			//�����̌�납��\��
			DrawRotaGraph(225 + (k * 18), 460, 0.11, 0, s_omote[j], TRUE);
			k++;
		}
		j--;
	}

	j = 1;
	k = 0;

	//�^�C���̕`�揈��
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
	for (int i = 0; i <= 12; i++)
	{
		DeleteGraph(image[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(s_omote[i]);
		DeleteGraph(t_omote[i]);
	}
}

void Score::DamegeFlag()
{
	//�v���C���[��e�ŕb�����炷
	time = time - 2;
}

//������UI�ύX����
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

	//�X�R�A��0�ɂȂ�܂Ńt�H���g�ϊ�����
	while (score != 0)
	{
		i = i * 10;       //���߂����ʂ̈ړ�
		value = score % i;   //���߂�����*10���ċ��߂�
		value = value / j;      //2���ڈȍ~�A�]���Ȍ�������
		s_omote[k] = image[value]; //�t�H���g�ϊ�
		score -= score % i;     //���߂������폜()
		j = j * 10;        //�]���Ȍ��ύX
		k++;          //�z��ړ�
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

