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

//�R���X�g���N�^
Scene::Scene() : objects(), background_image(NULL), sound(NULL),enemy_count(),
bom_set(TRUE),cool_count(0),mode(NULL),score(0),attack_flag(FALSE), score_class(nullptr)
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

	sound = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");

	if (sound == -1)
	{
		throw("ne-yo");
	}

	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/Imagezu/to�w�i2.png���Ȃ��ł��B\n");
	}

	for (int i = 0; enemy_count[3]; i++)
	{
		enemy_count[i] = 0;
	}

	if (GetRand(2) == 1)
	{

		CreateObject<Haneteki>(Vector2D(640.0f, 0.0f),0.0);
	}
	else
	{
		CreateObject<Haneteki>(Vector2D(0.0f, 0.0f),0.0);
	}

	score_class = new Score(this);
	score_class->Initialize();
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetMode() == 2 && objects[i]->GetAttackFlag() == true)
		{
			Vector2D p = objects[0]->GetLocation();
			Vector2D t = objects[i]->GetLocation();


			Vector2D l = Vector2D(p.x - t.x, p.y - t.y);

			int z = sqrt((l.x * l.x) + (l.y * l.y));

			CreateObject<Tama>(Vector2D(objects[i]->GetLocation()), l / z);
			
		}
	}

	//���Ԍo�߂œG�̐���
	for (int i = 0; i <= 3; i++)
	{
		enemy_count[i] += 1;
	}

	//�n�l�e�L�o���p�x
	if (enemy_count[0] >= 200)
	{
		if (GetRand(1) == 1)
		{

			CreateObject<Haneteki>(Vector2D(640.0f, 0.0f), 0.0);
		}
		else
		{
			CreateObject<Haneteki>(Vector2D(0.0f, 0.0f), 0.0);
		}
		enemy_count[0] = GetRand(150);
	}

	//�n�R�e�L�o���p�x
	if (enemy_count[1] >= 1000)
	{
		if (GetRand(1) == 1)
		{
			CreateObject<Hakoteki>(Vector2D(640.0f, 390.0f), 0.0);
		}
		else
		{
			CreateObject<Hakoteki>(Vector2D(0.0f, 391.0f), 0.0);
		}
		enemy_count[1] = GetRand(600) + 100;
	}

	//�_�C�A�o���p�x
	if (enemy_count[2] >= 2500)
	{
		if (GetRand(1) == 1)
		{

			CreateObject<Daiya>(Vector2D(640.0f, 400.0f), 0.0);
		}
		else
		{
			CreateObject<Daiya>(Vector2D(0.0f, 400.0f), 0.0);
		}
		enemy_count[2] = (GetRand(1000) + 700);
	}


	//�n�[�s�B�o���p�x
	if (enemy_count[3] >= 1200)
	{
		if (GetRand(1) == 1)
		{

			CreateObject<Hapyi>(Vector2D(640.0f, 0.0f), 0.0);
		}
		else
		{
			CreateObject<Hapyi>(Vector2D(0.0f, 0.0f), 0.0);
		}
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
	if (InputControl::GetKey(KEY_INPUT_X))
	{
		CreateObject<Bom>(objects[0]->GetLocation(), 0.0);
	}

	

	if (bom_set == FALSE)
	{
		cool_count++;
		if (cool_count >= 70) //�{���̃N�[���^�C��
		{
			bom_set = TRUE;
			cool_count = 0;
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteFlag() == true)
		{
			objects.erase(objects.begin() + i);
		}
	}

	score_class->Update();
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
		DeleteSoundMem(sound);
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

	delete score_class;
}

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
	gt = b->GetMode();

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
			if (score < 0)
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
			score_class->DamegeFlag();
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