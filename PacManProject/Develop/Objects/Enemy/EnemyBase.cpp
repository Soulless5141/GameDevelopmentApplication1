#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

#define D_ENEMY_SPEED	(50.0f)


EnemyBase::EnemyBase() :
	enemy_state(eEnemyState::HOME),
	right_flag(FALSE),
	home_flag(TRUE),
	home_time(0),
	get_flag(true)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	z_layer = 10;
}

void EnemyBase::Update(float delta_second)
{
	Movement(delta_second);

	AnimationControl(delta_second);
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	if (enemy_state != eEnemyState::GOHOME)
	{
		__super::Draw(screen_offset);
	}
	
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	// �ڂ̕`��
	if (enemy_state != IZIKE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_animation[now_direction], TRUE);
	}
}

//�v���C���[�̏�Ԏ擾
void EnemyBase::GetPlayer(Player* player)
{
	// �v���C���[�̏�Ԏ擾
	this->player = player;
}

void EnemyBase::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 32.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}

		// �������̉摜�̐ݒ�
		if (enemy_state == eEnemyState::IZIKE)
		{
			if (player->GetPowerUpTime() > 5) // 5�b�ȉ��œ_�ŏ���
			{
				image = move_animation[16 + animation_count];
			}
			else
			{
				izike_right_time++;

				// �_�ł̔���
				if (izike_right_time > 5 && right_flag == FALSE)
				{
					right_flag = TRUE;
					izike_right_time = 0;
				}
				else if (izike_right_time > 5 && right_flag == TRUE)
				{
					right_flag = FALSE;
					izike_right_time = 0;
				}

				if (right_flag == TRUE) // ����摜
				{
					image = move_animation[18 + animation_count];
				}
				else // �ʏ�izike�摜
				{
					image = move_animation[16 + animation_count];
				}
			}
		}
		else // �m�[�}���摜
		{
			image = move_animation[now_type * 2 + animation_count];
		}
		
		/*switch (now_direction)
		{
		case EUP:
			now_direction = ERIGHT;
			break;
		case ERIGHT:
			now_direction = EDOWN;
			break;
		case EDOWN:
			now_direction = ELEFT;
			break;
		case ELEFT:
			now_direction = EUP;
			break;
		default:
			break;
		}*/
	}
}

eEnemyState EnemyBase::GetEnemyState()
{
	return enemy_state;
}

eEnemyDirection EnemyBase::GetEnemyDirection()
{
	return now_direction;
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������I�u�W�F�N�g���G��������
	
	// ��������Ԃ̎��AGOHOME��ԂɂȂ�
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		player->GetEnemy(this);

		if (enemy_state == IZIKE)
		{
			enemy_state = eEnemyState::GOHOME;
			old_enemy_state = enemy_state;

		}
	}

	//	�n�E�X�̒��ɂ���Ƃ��A�㉺�Ɉړ�����
	if (hit_object->GetCollision().object_type == eObjectType::wall && (enemy_state == HOME || enemy_state == IZIKE))
	{
		if (home_flag == TRUE)
		{
			home_flag = FALSE;
		}
		else if (home_flag == FALSE)
		{
			home_flag = TRUE;
		}
	}
}

// �ŏ��œG�̎�ނ𕪂���
char EnemyBase::ChangeEnemyType()
{
	StageData::ConvertToIndex(location, panel_x, panel_y);

	switch (panel_y)
	{
	case 12:
		this->now_type = eEnemyType::AOSUKE;
		break;
	case 13:
		this->now_type = eEnemyType::AKABEI;
		enemy_state = PATROL;
		now_direction = ELEFT;
		//enemy_state = GOHOME; //                      aaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		break;
	case 14:
		this->now_type = eEnemyType::PINKY;
		break;
	case 16:
		this->now_type = eEnemyType::GUZUTA;
		break;
	default:
		break;
	}

	return now_type;
}

// ��{�I�Ȉړ�����
void EnemyBase::Movement(float delta_second)
{
	player->GetLocation();

	if (player->GetPowerUp() == true && enemy_state != GOHOME)
	{
		if (enemy_state != IZIKE)
		{
			old_enemy_state = enemy_state;
		}
		enemy_state = IZIKE;
	}

	switch (enemy_state)
	{
	case eEnemyState::HOME:
		HomeMovement(delta_second);     // �ҋ@���A�㉺�ɓ����i�\��j
		break;
	case eEnemyState::ATACCK:
		AttackMovement(delta_second);	// �e�G�l�~�[cpp�ɔ�ԁi�\��j
		break;
	case eEnemyState::PATROL:
		PatrolMovement(delta_second);   // �ڕW�p�l�����e�G�l�~�[�̂Ȃ�΂�ɂ���i�\��j
		break;
	case eEnemyState::IZIKE:
		IzikeMovement(delta_second);
		break;
	case eEnemyState::GOHOME:
		GoHomeMovement(delta_second);
		break;
	default:
		break;
	}

	// �ړ��ʂ���ړ��������X�V

		// �ړ������Ɉړ����Ă��Ȃ���� direction_state ��ύX����
	switch (now_direction)
	{
	case eEnemyDirection::EUP:
	case eEnemyDirection::EDOWN:
	{
		float diff = location.y - velocity.y;
		if (((now_direction == eEnemyDirection::EUP) && (diff < 0.0f)) ||
			((now_direction == eEnemyDirection::EDOWN) && (0.0f < diff)))
		{
			// �ړ������Ɉړ����Ă�̂� break
			break;
		}
	}
	break;

	case eEnemyDirection::ELEFT:
	case eEnemyDirection::ERIGHT:
	{
		float diff = location.x - velocity.x;
		if (((now_direction == eEnemyDirection::ELEFT) && (diff < 0.0f)) ||
			((now_direction == eEnemyDirection::ERIGHT) && (0.0f < diff)))
		{
			// �ړ������Ɉړ����Ă�̂� break
			break;
		}
	}
	break;

	default:// �������Ȃ�
		break;
	}

	// ���͏�Ԃ̎擾
	InputManager* input = InputManager::GetInstance();

	// ���݃p�l���̏�Ԃ��m�F
	ePanelID panel = StageData::GetPanelData(location);

	// ���͂���ړ�������ݒ�
	if (input->GetKeyDown(KEY_INPUT_W) || input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		switch (now_direction)
		{
		case eEnemyDirection::ELEFT:
		case eEnemyDirection::EDOWN:
		case eEnemyDirection::ERIGHT:
			now_direction = eEnemyDirection::EUP;
			break;

		default:
			break;
		}
	}
	else if (input->GetKeyDown(KEY_INPUT_S) || input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		switch (now_direction)
		{
		case eEnemyDirection::ELEFT:
		case eEnemyDirection::ERIGHT:
		case eEnemyDirection::EUP:
			now_direction = eEnemyDirection::EDOWN;
			break;

		default:
			break;
		}
	}
	else if (input->GetKeyDown(KEY_INPUT_A) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		switch (now_direction)
		{
		case eEnemyDirection::EUP:
		case eEnemyDirection::EDOWN:
		case eEnemyDirection::ERIGHT:
			now_direction = eEnemyDirection::ELEFT;
			break;

		default:
			break;
		}
	}
	else if (input->GetKeyDown(KEY_INPUT_D) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		switch (now_direction)
		{
		case eEnemyDirection::EUP:
		case eEnemyDirection::EDOWN:
		case eEnemyDirection::ELEFT:
			now_direction = eEnemyDirection::ERIGHT;
			break;

		default:
			break;
		}
	}

	// �i�s�����̈ړ��ʂ�ǉ�
	velocity = 0.0f;
	switch (now_direction)
	{
	case eEnemyDirection::EUP:
		velocity.y = -2.0f;
		break;
	case eEnemyDirection::EDOWN:
		velocity.y = 2.0f;
		break;
	case eEnemyDirection::ELEFT:
		velocity.x = -2.0f;
		break;
	case eEnemyDirection::ERIGHT:
		velocity.x = 2.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}

	if (enemy_state == GOHOME)
	{
		velocity = velocity * 3;
	}

	//// �O����W�̍X�V
	//old_location = location;

	//// �O��p�l���̍X�V
	//old_panel = panel;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_ENEMY_SPEED * delta_second;

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}

}

void EnemyBase::HomeMovement(float delta_second)
{
	// �n�E�X�̒��̓G���A�ǂɂԂ���ƕ����]������
	switch (now_type)
	{
	case AOSUKE:
	case GUZUTA:
		if (home_flag == TRUE)
		{
			now_direction = EDOWN;
		}
		else if (home_flag == FALSE)
		{
			now_direction = EUP;
		}
		break;
	case PINKY:
		if (home_flag == TRUE)
		{
			now_direction = EUP;
		}
		else if (home_flag == FALSE)
		{
			now_direction = EDOWN;
		}
		break;
	default:
		break;
	}
}

//����
void EnemyBase::PatrolMovement(float delta_second)
{
	// ���݃p�l���̏�Ԃ��m�F
	ePanelID panel = StageData::GetPanelData(location);

	// �����ϊ��t���O
	if (get_flag == false && panel == ePanelID::NONE)
	{
		get_flag = true;
	}

	// �����ϊ�����
	if (panel == ePanelID::BRANCH && get_flag == true)
	{
		std::map<eAdjacentDirection, ePanelID> ret = StageData::GetAdjacentPanelData(location);

		if (ret[eAdjacentDirection::UP] != WALL && now_direction != EDOWN)
		{
			old_direction = now_direction;
			now_direction = EUP;
		}
		else if (ret[eAdjacentDirection::RIGHT] != WALL && now_direction != ELEFT)
		{
			old_direction = now_direction;
			now_direction = ERIGHT;
		}
		else if (ret[eAdjacentDirection::DOWN] != WALL && now_direction != EUP)
		{
			old_direction = now_direction;
			now_direction = EDOWN;
		}
		else if (ret[eAdjacentDirection::LEFT] != WALL && now_direction != ERIGHT)
		{
			old_direction = now_direction;
			now_direction = ELEFT;
		}

		

		/*switch (now_direction)
		{
		case EUP:
			now_direction = ERIGHT;
			break;
		case ERIGHT:
			now_direction = EDOWN;
			break;
		case EDOWN:
			now_direction = ELEFT;
			break;
		case ELEFT:
			now_direction = EUP;
			break;
		default:
			break;
		}*/

		get_flag = false; //��x�ʘH�ɍs���Ȃ��ƕϊ����Ȃ��悤�ɂ���
	}
}

void EnemyBase::IzikeMovement(float delta_second)
{
	// �n�E�X�̒��ł��ړ��ł���悤�ɂ���
	if (old_enemy_state == HOME)
	{
		HomeMovement(delta_second);
	}

	// ��������ԉ���
	if (player->GetPowerUp() == false)
	{
		if (old_enemy_state != GOHOME)
		{
			enemy_state = old_enemy_state;
		}
		else
		{
			enemy_state = GOHOME;
		}
		
	}
}

void EnemyBase::GoHomeMovement(float delta_second)
{
	// ���݃p�l���̏�Ԃ��m�F
	ePanelID panel = StageData::GetPanelData(location);

	if (panel == ePanelID::BRANCH)
	{
		if (panel <= 100)
		{
			now_direction = ERIGHT;
		}
	}
}

void EnemyBase::AttackMovement(float delta_second)
{
	switch (now_type)
	{
	case eEnemyType::AKABEI:
		//akabei->AttackMovement(delta_second);
		break;
	case eEnemyType::AOSUKE:
		break;
	case eEnemyType::GUZUTA:
		break;
	case eEnemyType::PINKY:
		break;
	default:
		break;
	}

}
