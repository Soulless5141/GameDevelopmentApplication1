#include "Scene.h"
#include"DxLib.h"
#include"stdlib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Player/Bom.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(), background_image(NULL), sound(NULL),enemy_count(),bom_set(TRUE),bom_count(0),mode(NULL)
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
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//CreateObject<Bom>(Vector2D(320.0f, 60.0f));
	CreateObject<Enemy>(Vector2D(640.0f, 380.0f));    //�n�R�e�L�E����
	CreateObject<Enemy>(Vector2D(0.0f, 380.0f));      //�n�R�e�L������

	background_image = LoadGraph("Resource/Imagezu/�w�i2.png");

	sound = LoadSoundMem("Resource/Imagezu/BGM_arrows.wav");

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

	enemy_count = 0;
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//���Ԍo�߂œG�̐���
	enemy_count++;
	if (enemy_count >= 600)
	{
		CreateObject<Enemy>(Vector2D(640.0f, 380.0f));
		CreateObject<Enemy>(Vector2D(0.0f, 381.0f));
		enemy_count = ((rand() % 300) + 200);
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
		//CreateObject<Bom>(Vector2D())->Func();
		CreateObject<Bom>(objects[0]->GetLocation());
		//CreateObject<Bom>(Vector2D(50,50));
		bom_set = FALSE;
	}

	if (InputControl::GetKey(KEY_INPUT_X) && bom_set == TRUE)
	{
		CreateObject<Bom>(objects[0]->GetLocation());
	}

	if (bom_set == FALSE)
	{
		bom_count++;
		if (bom_count >= 0)
		{
			bom_set = TRUE;
			bom_count = 0;
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteFlag() == true)
		{
			objects.erase(objects.begin() + i);
		}
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

}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻����Ƃ�)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	int fr, gt;
	fr = a->GetMode();
	gt = b->GetMode();

	if ((fr != gt) && (fr != 0 && gt != 0) )
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