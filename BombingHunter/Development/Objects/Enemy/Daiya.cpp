#include "Daiya.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Daiya::Daiya() : animation_count(0), direction(0.0f), enemy_number(NULL)
{

}

//�f�X�g���N�^
Daiya::~Daiya()
{

}

//����������
void Daiya::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Imagezu/daia1.png");//�_�C�A1
	animation[1] = LoadGraph("Resource/Imagezu/daia2.png");//�_�C�A2
	animation[2] = LoadGraph("Resource/Imagezu/daia3.png");//�_�C�A3
	animation[3] = LoadGraph("Resource/Imagezu/daia4.png");//�_�C�A4
	animation[4] = LoadGraph("Resource/Imagezu/daia5.png");//�_�C�A5


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�_�C���̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 40.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//���邩�H
	enemy_number = 100;
	
	//�X�R�A�ݒ�
	enemy_score = 7777;

	//�������̈ړ�����
	if (location.x <= 300.0f)
	{
		velocity.x = GetRand(8) / 10.0f + 0.2f;
	}
	else
	{
		velocity.x = -(GetRand(8) / 10.0f + 0.2);
	}

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

	//�n�R�e�L�̉摜��`��
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//�I��������
void Daiya::Finalize()
{
	box_size = 0;
	direction = 0.0f;
	location = 0;
	delete_flag = true;
	//�g�p�����摜���J������
	for (int i = 0; i <= 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Daiya::OnHitCollision(GameObject* hit_object)
{
	GetScore();
	//�����������̏���
	Finalize();
}

//�ړ�����
void Daiya::Movement()
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