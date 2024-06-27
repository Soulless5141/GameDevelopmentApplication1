#include "Haneteki.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Haneteki::Haneteki() : animation_count(0), direction(0.0f),ptn(GetRand(2)),attack_time(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Haneteki::~Haneteki()
{

}

//����������
void Haneteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");//�n�l�e�L1
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");//�n�l�e�L2

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//Y���W�����_������
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
	
	//�X�R�A�ݒ�
	enemy_score = 800;

	//�������̈ړ�����
	if (location.x <= 300.0f)
	{
		velocity.x = (rand() % 8) / 10.0f + 0.2f;
	}
	else
	{
		velocity.x = -((rand() % 8) / 10.0f + 0.2);
	}

	//�G�̎�ސݒ�
	mode = 2;
}

//�X�V����
void Haneteki::Update()
{
	//�U���t���O����
	if (attack_flag == true)
	{
		attack_flag = false;
	}
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
	//�U�����萧��
	AttackControl();

}

//�`�揈��
void Haneteki::Draw() const
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

	//�n�l�e�L�̉摜��`��
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//�I��������
void Haneteki::Finalize()
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
void Haneteki::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	Finalize();
}

//�ړ�����
void Haneteki::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;

	//�͂��܂ōs���ƍ폜
	if (location.x < -20 || location.x > 660)
	{
		Finalize();
	}
}

//�A�j���[�V��������
void Haneteki::AnimeControl()
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

//�U�����䏈��
void Haneteki::AttackControl()
{
	//��莞�ԊԊu�ōU��
	attack_time++;

	//��莞�Ԍo�Ƒł�
	if (attack_time >= 200)
	{
		//�J�E���g���Z�b�g
		attack_time = 0;
		attack_flag = true;
	}
}