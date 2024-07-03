#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"
#include"Player.h"

//�R���X�g���N�^
Bom::Bom() : animation_count(0),next_flag(false)
{
	for (int i = 0; i < ANIMATION_IMAGES; i++)
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
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�摜�̓ǂݍ���
	tmp = rm->GetImages("Resource/Images/Bomb/Bomb.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/1.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/2.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/3.png");
	animation_data.push_back(tmp[0]);

	//�����̓ǂݍ���
	tmp = rm->GetSounds("Resource/Sounds/explosion.wav");
	sounds_data.push_back(tmp[0]);

	sound = sounds_data[0];

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}

	//���ړ����Ȃ��猂�����ݒ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		//�����̐ݒ�
		radian = 180 * 3.14 / 180;
		//�����ړ��ݒ�
		direction = Vector2D(-1.4, 1.7); 
	}
	//�E�ړ����Ȃ��猂�����ݒ�
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		//�����̐ݒ�
		radian = 0 * 3.14 / 180;
		//�����ړ��ݒ�
		direction = Vector2D(1.4, 1.7);
	}
	//�~�܂��Č�������
	else
	{
		//�����̐ݒ�
		radian = 90 * 3.14 / 180;
		//�����ړ��ݒ�
		direction = Vector2D(0, 1.5);
	}

	//�傫���̐ݒ�
	box_size = 32.0;

	//�����摜�̐ݒ�
	image = animation_data[0];

	//�I�u�W�F�N�g�ݒ�
	//0;�v���C���[  1;�{��  2;�e�L  3;�G�̒e
	mode = 1;

	//�������[�V�����Ɉڂ��Ă������̊m�F
	next_flag = false;

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
	//�������J���t���O
	delete_flag = true;
	//�g�p�����摜�≹�����J������
	DeleteGraph(image);
	DeleteSoundMem(sounds_data[0]);
}

//�����蔻��ʒm����
void Bom::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	next_flag = true;
	box_size = 0;
	direction = 0.0f;
	/*Vector2D velocity = 0.0f;*/
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

	//�J�[�u�X���[�������̓���
	if (direction.x < 0 && image == animation_data[0])
	{
		direction.x = direction.x + (1.2/ 90);
	}
	if (direction.x > 0 && image == animation_data[0])
	{
		direction.x = direction.x - (1.2 / 90);
	}
}

//�A�j���[�V��������
void Bom::AnimeControl()
{
	//�J�[�u�X���[�������̌�����
	if (radian < 90 * 3.14 / 180 && image == animation_data[0])
	{
		radian = radian + (1 * 3.14 / 180);
	}
	if (radian > 90 * 3.14 / 180 && image == animation_data[0])
	{
		radian = radian - (1 * 3.14 / 180);
	}

	//���j�������̉摜�̐؂�ւ�
	if (next_flag == true)
	{
		animation_count++;

		if (image == animation_data[0])
		{
			box_size = 0;
			radian = 0;
			image = animation_data[1];
			animation_count = 0;
			PlaySoundMem(sounds_data[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (animation_count >= 10 && image == animation_data[1])
		{
			image = animation_data[2];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation_data[2])
		{
			image = animation_data[3];
			animation_count = 0;
		}
		else if (animation_count >= 10 && image == animation_data[3])
		{
			DeleteGraph(image);
		}
		if (animation_count > 100)  //�������Đ�����������I������
		{
			Finalize();
		}
	}
}
	

