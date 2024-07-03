#include "Daiya.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Daiya::Daiya() : animation_count(0), direction(0.0f)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Daiya::~Daiya()
{

}

//����������
void Daiya::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");//�_�C�A1
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");//�_�C�A2
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");//�_�C�A3
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");//�_�C�A4
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");//�_�C�A5


	//�G���[�`�F�b�N
	for (int i = 0; i < 5; i++)
	{
		if (animation[i] == -1)
		{
			throw("�_�C���̉摜������܂���\n");
		}
	}
	
	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 40.0;

	//�����摜�̐ݒ�
	image = animation[0];
	
	//�X�R�A�ݒ�
	enemy_score = 77777;

	//�������̈ړ�����&���x�����_��
	if (location.x <= 300.0f)
	{
		velocity.x = GetRand(7) / 10.0f + 0.3f;
	}
	else
	{
		velocity.x = -(GetRand(7) / 10.0f + 0.3);
	}

	//�I�u�W�F�N�g�ݒ�
	//0;�v���C���[  1;�{��  2;�e�L  3;�G�̒e
	mode = 2;
}

//�X�V����
void Daiya::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

}

//�`�揈��
void Daiya::Draw() const
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

	//�_�C�A�̉摜��`��
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//�I��������
void Daiya::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	delete_flag = true;
	//�g�p�����摜���J������
	for (int i = 0; i <= 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	//�������J��
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Daiya::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	Finalize();
}

//�ړ�����
void Daiya::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;

	//��ʊO�ɍs���Ə�����
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//�A�j���[�V��������
void Daiya::AnimeControl()
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
		else if (image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else if (image == animation[4])
		{
			image = animation[0];
		}
	}
}