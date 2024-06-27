#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"Player.h"

//�R���X�g���N�^
Bom::Bom() : animation_count(0),next_flag(false)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Bom::~Bom()
{

}

//����������
void Bom::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3/png");

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

	//�I�u�W�F�N�g�ݒ�
	mode = 1;

	//�������[�V�����Ɉڂ��Ă������̊m�F
	next_flag = false;

	//�ړ��ݒ�
	direction = Vector2D(0.0, 1.5);
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
	delete_flag = true;
	//�g�p�����摜���J������
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Bom::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	next_flag = true;
	box_size = 0;
	direction = 0.0f;
	Vector2D velocity = 0.0f;
	direction = Vector2D(0.0, 0.0);
}

//�ړ�����
void Bom::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z����
	location += direction;

	//�����W���B��A�N�����[�V����
	if (location.y >= 410)
	{
		next_flag = true;  //�N���A�j���[�V�����ɂ���
		direction = 0.0f;  //���W���~�߂�
	}
}

//�A�j���[�V��������
void Bom::AnimeControl()
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
	

