#include "Hakoteki.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Hakoteki::Hakoteki() : animation_count(0), direction(0.0f),enemy_number(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Hakoteki::~Hakoteki()
{

}

//����������
void Hakoteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Imagezu/1 (1).png");//�n�R�e�L1
	animation[1] = LoadGraph("Resource/Imagezu/2 (1).png");//�n�R�e�L2

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�X�R�A�ݒ�
	enemy_score = 1000;

	//�������̈ړ�����
	if (location.x <= 300.0f)
	{
		velocity.x = (rand() % 8) / 10.0f + 0.2f;
	}
	else 
	{
		velocity.x = -((rand() % 8) / 10.0f + 0.2);
	}

	mode = 2;
}

//�X�V����
void Hakoteki::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

}

//�`�揈��
void Hakoteki::Draw() const
{
	//��ʔ��]�t���O(FALSE=�E�@TURE=��)
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//�n�R�e�L�̉摜��`��
	switch (enemy_number)
	{
	case 0:
		DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
		break;
	default:
		DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
		break;
	}

	__super::Draw();
}

//�I��������
void Hakoteki::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	location = 0;
	delete_flag = true;
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	GetScore();
	//�����������̏���
	Finalize();
}

//�ړ�����
void Hakoteki::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;

	//
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//�A�j���[�V��������
void Hakoteki::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if (image==animation[1])
		{
			image = animation[0];
		}
	}
}
