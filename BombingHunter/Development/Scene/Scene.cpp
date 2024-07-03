#include "Scene.h"
#include "math.h"
#include"DxLib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Player/Bom.h"
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Daiya.h"
#include"../Objects/Enemy/Hapyi.h"
#include"../Objects/Enemy/Tama.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER
#define BOM_COOLTIME (50)          //�{���̃N�[���^�C��
#define POP_TIME_HANETEKI (200)    //�n�[�s�B�̏o������
#define POP_TIME_HAKOTEKI (1000)   //�n�R�e�L�̏o������
#define POP_TIME_HAPYI (1200)      //�n�l�e�L�̏o������
#define POP_TIME_DAIYA (2500)      //���G�̏o������
#define SCORE_PERFECT (200000)     //�p�[�t�F�N�g�ɕK�v�ȃX�R�A
#define SCORE_GOOD    (120000)     //�O�b�h�ɕK�v�ȃX�R�A
#define SCORE_OK      (50000)      //OK�ɕK�v�ȃX�R�A
#define MAX_SOUNDS    (6)          //������



//�R���X�g���N�^
Scene::Scene() : objects(), background_image(NULL), sounds(), enemy_count(), result_flag(false),image(NULL),
bom_set(TRUE),cool_count(0),mode(NULL),score(0), score_class(nullptr),time(NULL),sound(NULL),
result_score(),result_count()
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f), 0.0);

	background_image = LoadGraph("Resource/Images/BackGround.png");

	result_score[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	result_score[1] = LoadGraph("Resource/Images/Evaluation/Perfect.png");
	result_score[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_score[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_score[4] = LoadGraph("Resource/Images/Evaluation/BAD.png");

	sounds[0] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	sounds[1] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_timeup.wav");
	sounds[2] = LoadSoundMem("Resource/Sounds/Evaluation/SE_perfect.wav");
	sounds[3] = LoadSoundMem("Resource/Sounds/Evaluation/SE_good.wav");
	sounds[4] = LoadSoundMem("Resource/Sounds/Evaluation/SE_ok.wav");
	sounds[5] = LoadSoundMem("Resource/Sounds/Evaluation/SE_bad.wav");

	//�G���[�`�F�b�N(����)
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] == -1)
		{
			throw("sound_naiyo");
		}
	}

	//�G���[�`�F�b�N(���U���g�摜)
	for (int i = 0; i < MAX_RESULT; i++)
	{
		if (result_score[i] == -1)
		{
			throw("result_naiyo");
		}
	}

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/Imagezu/to�w�i2.png���Ȃ��ł��B\n");
	}

	//BGM�Đ�
	PlaySoundMem(sounds[0], DX_PLAYTYPE_LOOP, TRUE);

	//�G�̏o���p�x���Z�b�g
	for (int i = 0;i < ENEMY_KINDS; i++)
	{
		enemy_count[i] = 0;
	}

	//�G�̏�����������
	if (GetRand(2) == 1)
	{

		CreateObject<Haneteki>(Vector2D(640.0f, 0.0f),0.0);
	}
	else
	{
		CreateObject<Haneteki>(Vector2D(0.0f, 0.0f),0.0);
	}

	//�X�R�A�N���X��initialize
	score_class = new Score(this);
	score_class->Initialize();
}

//�X�V����
void Scene::Update()
{
	//���݃^�C�����擾
	time = score_class->GetTime();
	if (time >= 0)
	{
		//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
		for (GameObject* obj : objects)
		{
			obj->Update();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			//�G�̍U���̐����������ݒ菈��
			if (objects[i]->GetAttackFlag() == true)
			{
				//���@�Ɍ���������
				Vector2D p = objects[0]->GetLocation();
				Vector2D t = objects[i]->GetLocation();
				Vector2D l = Vector2D(p.x - t.x, p.y - t.y);
				int z = sqrt((l.x * l.x) + (l.y * l.y));

				//�e��������
				CreateObject<Tama>(objects[i]->GetLocation(), l / z);

			}
		}

		//���Ԍo�߂œG�̐���
		for (int i = 0; i < ENEMY_KINDS; i++)
		{
			enemy_count[i] += 1;
		}

		//�n�l�e�L�o���p�x
		if (enemy_count[0] >= POP_TIME_HANETEKI)
		{
			if (GetRand(1) == 1)
			{
				CreateObject<Haneteki>(Vector2D(640.0f, 0.0f), 0.0);
			}
			else
			{
				CreateObject<Haneteki>(Vector2D(0.0f, 0.0f), 0.0);
			}
			//�����^�C�~���O�������_���ɂ���
			enemy_count[0] = GetRand(150);
		}

		//�n�R�e�L�o���p�x
		if (enemy_count[1] >= POP_TIME_HAKOTEKI)
		{
			if (GetRand(1) == 1)
			{
				CreateObject<Hakoteki>(Vector2D(640.0f, 390.0f), 0.0);
			}
			else
			{
				CreateObject<Hakoteki>(Vector2D(0.0f, 391.0f), 0.0);
			}
			//�����^�C�~���O�������_���ɂ���
			enemy_count[1] = GetRand(600) + 100;
		}

		//�_�C�A�o���p�x
		if (enemy_count[2] >= POP_TIME_DAIYA)
		{
			if (GetRand(1) == 1)
			{

				CreateObject<Daiya>(Vector2D(640.0f, 400.0f), 0.0);
			}
			else
			{
				CreateObject<Daiya>(Vector2D(0.0f, 400.0f), 0.0);
			}
			//�����^�C�~���O�������_���ɂ���
			enemy_count[2] = (GetRand(1000) + 700);
		}


		//�n�[�s�B�o���p�x
		if (enemy_count[3] >= POP_TIME_HAPYI)
		{
			if (GetRand(1) == 1)
			{

				CreateObject<Hapyi>(Vector2D(640.0f, 0.0f), 0.0);
			}
			else
			{
				CreateObject<Hapyi>(Vector2D(0.0f, 0.0f), 0.0);
			}
			//�����^�C�~���O�������_���ɂ���
			enemy_count[3] = GetRand(200);
		}

		//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				//�����蔻��`�F�b�N���� now(preyer,���̑�)
				HitCheckObject(objects[i], objects[j]);
			}
		}

		//z�L�[����������A�{���𐶐�����
		if (InputControl::GetKeyDown(KEY_INPUT_Z) && bom_set == TRUE)
		{
			CreateObject<Bom>(objects[0]->GetLocation(), 0.0);
			bom_set = FALSE;
		}

		//�{���̃N�[���^�C���ݒ菈��
		if (bom_set == FALSE)
		{
			cool_count++;
			if (cool_count >= BOM_COOLTIME) //�{���̃N�[���^�C��
			{
				bom_set = TRUE;  //�đ��U����
				cool_count = 0;  //�J�E���g���Z�b�g
			}
		}

		//�I�u�W�F�N�g�̃������J�����菈��
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->DeleteFlag() == true)
			{
				objects.erase(objects.begin() + i);
			}
		}
		//�X�R�Acpp�̃A�b�v�f�[�g����
		score_class->Update();
	}
	else  //�^�C����0�ɂȂ�������s
	{
		if (result_count == 0)
		{
			result_flag = true;
			//�T�E���h�X�g�b�v
			DeleteSoundMem(sounds[0]);
			PlaySoundMem(sounds[1], DX_PLAYTYPE_BACK, TRUE);

			//�X�R�A�ɂ���ĕ]�����ς��
			if (score >= SCORE_PERFECT)    //100000�ȏ�p�[�t�F�N�g
			{
				image = result_score[1];
				sound = sounds[2];
			}
			else if (score >= SCORE_GOOD)  //70000�ȏ�O�b�h
			{
				image = result_score[2];
				sound = sounds[3];
			}
			else if (score >= SCORE_OK)    //10000�ȏ� OK
			{
				image = result_score[3];
				sound = sounds[4];
			}
			else                           //�����O�o�b�h
			{
				image = result_score[4];
				sound = sounds[5];
			}

			//�e�I�u�W�F�N�g���폜����
			for (GameObject* obj : objects)
			{
				obj->Finalize();
				delete obj;
			}

			//���I�z��̉��
			objects.clear();
		}

		//���U���g�̐i�s�J�E���g
		result_count++;
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�̕`��
	DrawExtendGraph(0, 0, 640, 480, background_image, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	//�]����ʂ̕����`��
	if (result_flag == true && result_count < 500)
	{
		DrawRotaGraph(320, 240, 1.5, 0, result_score[0], TRUE);
	}
	else if (result_flag == true && result_count >= 500)
	{
		DrawRotaGraph(320, 240, 1, 0, image, TRUE);
	}

	//�]���ɍ��킹�����𗬂�
	if (result_count == 500)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);
	}

	//�X�R�A�V�[���̕`�揈��
	score_class->Draw();
	
}

//�I��������
void Scene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);

	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		DeleteSoundMem(sounds[0]);
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

	//�X�R�A�N���X�̍폜
	delete score_class;
}

//���݃X�R�A�擾����
int Scene::GetScore()
{
	return score;
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻����Ƃ�)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	int fr, gt;
	fr = a->GetMode(); //0;�v���C���[  1;�{��  2;�e�L  3;�G�̒e
	gt = b->GetMode(); //0;�v���C���[  1;�{��  2;�e�L  3;�G�̒e

	//�G�ƃ{�����Ԃ�������̏���
	if ((fr != gt) && (fr != 0 && gt != 0) && (fr != 3 && gt != 3))
	{
		//2�̃I�u�W�F�N�g�̋������擾
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

		//�������傫�����傫���ꍇ�AHit����Ƃ���
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);

			//�X�R�A���Z����
			if (fr == 2)
			{
				score += a->GetScore();
			}
			else if (gt == 2)
			{
				score += b->GetScore();
			}
			if (score < 0)   //�X�R�A��0�ȉ��Ȃ�0�ɂ���
			{
				score = 0;
			}
		}
	}
	//�G�̒e�ƃv���C���[
	else if (fr == 0 && gt == 3)
	{
		//2�̃I�u�W�F�N�g�̋������擾
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize());

		//�������傫�����傫���ꍇ�AHit����Ƃ���
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);
			score_class->DamegeFlag();   //�b�������炷
		}
	}
}

#else

//�����蔻��`�F�b�N����(���㒸�_�̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�㒸�_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIVOT_CNETER