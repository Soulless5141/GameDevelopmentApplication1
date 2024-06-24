#include "Tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Tama::Tama() : animation_count(0), direction(0.0f),next_flag(false)
{
	for (int i = 0; i <= 3 ; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Tama::~Tama()
{

}

//����������
void Tama::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");//�e1
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");//�e2
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");//�e3
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");//�e4

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�e�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 20.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//enemy_score = -5;

	//�������̈ړ�����
	velocity.y = -1;

	mode = 3;
}

//�X�V����
void Tama::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

}

//�`�揈��
void Tama::Draw() const
{
	//�n�R�e�L�̉摜��`��
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	__super::Draw();
}

//�I��������
void Tama::Finalize()
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
void Tama::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	next_flag = true;
	box_size = 0;
	direction = 0.0f;
	velocity.y = 0.0f;
	direction = Vector2D(0.0, 0.0);
}

//�ړ�����
void Tama::Movement()
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
void Tama::AnimeControl()
{
	//�摜�̐؂�ւ�
	if (next_flag == true)
	{
		animation_count++;
		if (image == animation[0])
		{
			box_size = 0;
			radian = 0;
			image = animation[1];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[1])
		{
			image = animation[2];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[2])
		{
			image = animation[3];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation[3])
		{
			Finalize();
		}
	}
}