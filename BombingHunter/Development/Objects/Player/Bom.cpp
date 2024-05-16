#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
Bom::Bom() : animation_count(0)
{
	animation[0] = NULL;
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

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.5;

	//�傫���̐ݒ�
	scale = 32.0;

	//�����摜�̐ݒ�
	image = animation[0];
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


	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) * (float)scale / 2.0f);
	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) * (float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Bom::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
}

//�����蔻��ʒm����
void Bom::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

//�ړ�����
void Bom::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.5f;

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Bom::AnimeControl()
{
	//�摜�̐؂�ւ�
	/*if (image == animation[0])
	{
		image = animation[1];
	}
	else
	{
		image = animation[0];
	}*/
}
