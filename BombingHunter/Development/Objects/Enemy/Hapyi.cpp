#include "Hapyi.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Hapyi::Hapyi() : animation_count(0), direction(0.0f),ptn(GetRand(2)),animation()
{
	
}

//�f�X�g���N�^
Hapyi::~Hapyi()
{

}

//����������
void Hapyi::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");//�n�[�s�B1
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");//�n�[�s�B1

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�[�s�B�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
	
	switch (ptn)
	{
	case 1:
		location.y = 140;
		break;
	case 2:
		location.y = 230;
		break;
	default:
		location.y = 320;
		break;
	}

	enemy_score = -3000;
	

	//�������̈ړ�����
	if (location.x <= 300.0f)
	{
		velocity.x = (rand() % 6) / 10.0f + 0.5f;
	}
	else
	{
		velocity.x = -((rand() % 6) / 10.0f + 0.5);
	}

	mode = 2;
}

//�X�V����
void Hapyi::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

}

//�`�揈��
void Hapyi::Draw() const
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
void Hapyi::Finalize()
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
void Hapyi::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	Finalize();
}

//�ړ�����
void Hapyi::Movement()
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
void Hapyi::AnimeControl()
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
			image = animation[0];
		}
	}
}