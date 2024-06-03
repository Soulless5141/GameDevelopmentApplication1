#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"Player.h"

//�R���X�g���N�^
Bom::Bom() : animation_count(0), count(0),next_flag(false)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//�f�X�g���N�^
Bom::~Bom()
{

}

//����������
void Bom::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Imagezu/���e.png");
	animation[1] = LoadGraph("Resource/Imagezu/baku1.png");
	animation[2] = LoadGraph("Resource/Imagezu/baku2.png");
	animation[3] = LoadGraph("Resource/Imagezu/baku3.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}
	if (animation[1] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 90 * 3.14 / 180;

	//�傫���̐ݒ�
	box_size = 32.0;

	//�����摜�̐ݒ�
	image = animation[0];

	mode = 1;

	//�������[�V�����Ɉڂ��Ă������̊m�F
	next_flag = false;

	direction = Vector2D(0.0, 1.0);

}

//�X�V����
void Bom::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Bom::Draw() const
{
	//�v���C���[�̉摜��`��
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	__super::Draw();
}

//�I��������
void Bom::Finalize()
{
	box_size = 0;
	location = 0;
	delete_flag = true;
	//�g�p�����摜���J������
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Bom::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	next_flag = true;
	direction = 0.0f;
	Vector2D velocity = 0.0f;
}

//�ړ�����
void Bom::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z����
	location += direction;

	if (location.y >= 410)
	{
		next_flag = true;
		direction = 0.0f;
	}
}

//�A�j���[�V��������
void Bom::AnimeControl()
{
	//�摜�̐؂�ւ�
	if (next_flag == true)
	{
		count++;
		if (image == animation[0])
		{
			box_size = 0;
			radian = 0;
			image = animation[1];
			count = 0;
		}
		else if (count >= 10 && image == animation[1])
		{
			image = animation[2];
			count = 0;
		}
		else if (count >= 10 && image == animation[2])
		{
			image = animation[3];
			count = 0;
		}
		else if (count >= 10 && image == animation[3])
		{
			Finalize();
		}
	}
}
	

//void Bom::Func(Vector2D player)
//{
//	player = 0;
//}
