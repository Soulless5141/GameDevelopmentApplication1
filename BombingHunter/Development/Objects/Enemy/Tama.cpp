#include "Tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"stdlib.h"

//�R���X�g���N�^
Tama::Tama() : animation_count(0), direction(0.0f)
{

}

//�f�X�g���N�^
Tama::~Tama()
{

}

//����������
void Tama::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Imagezu/eff1.png");//�e1
	animation[1] = LoadGraph("Resource/Imagezu/eff2.png");//�e2
	animation[2] = LoadGraph("Resource/Imagezu/eff3.png");//�e3
	animation[3] = LoadGraph("Resource/Imagezu/eff4.png");//�e4

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

	enemy_score = -5;

	//�������̈ړ�����
	velocity = 1;

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
	//GetScore();
	//�����������̏���
	Finalize();
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