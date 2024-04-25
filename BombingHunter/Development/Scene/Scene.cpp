#include "Scene.h"
#include"DxLib.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"

//�R���X�g���N�^
Scene::Scene() : objects(), background_image(NULL), sound(NULL)
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
	CreateObject<Enemy>(Vector2D(640.0f, 380.0f));

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
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
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