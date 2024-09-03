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
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// 可動性の設定
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
	// 親クラスの描画処理を呼び出す
	if (enemy_state != eEnemyState::GOHOME)
	{
		__super::Draw(screen_offset);
	}
	
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;

	// 目の描画
	if (enemy_state != IZIKE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_animation[now_direction], TRUE);
	}
}

//プレイヤーの状態取得
void EnemyBase::GetPlayer(Player* player)
{
	// プレイヤーの状態取得
	this->player = player;
}

void EnemyBase::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 32.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}

		// いじけの画像の設定
		if (enemy_state == eEnemyState::IZIKE)
		{
			if (player->GetPowerUpTime() > 5) // 5秒以下で点滅準備
			{
				image = move_animation[16 + animation_count];
			}
			else
			{
				izike_right_time++;

				// 点滅の判定
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

				if (right_flag == TRUE) // 光る画像
				{
					image = move_animation[18 + animation_count];
				}
				else // 通常izike画像
				{
					image = move_animation[16 + animation_count];
				}
			}
		}
		else // ノーマル画像
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
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}

	// 当たったオブジェクトが敵だったら
	
	// いじけ状態の時、GOHOME状態になる
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		player->GetEnemy(this);

		if (enemy_state == IZIKE)
		{
			enemy_state = eEnemyState::GOHOME;
			old_enemy_state = enemy_state;

		}
	}

	//	ハウスの中にいるとき、上下に移動する
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

// 最初で敵の種類を分ける
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

// 基本的な移動処理
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
		HomeMovement(delta_second);     // 待機中、上下に動く（予定）
		break;
	case eEnemyState::ATACCK:
		AttackMovement(delta_second);	// 各エネミーcppに飛ぶ（予定）
		break;
	case eEnemyState::PATROL:
		PatrolMovement(delta_second);   // 目標パネルを各エネミーのなわばりにする（予定）
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

	// 移動量から移動方向を更新

		// 移動方向に移動していなければ direction_state を変更する
	switch (now_direction)
	{
	case eEnemyDirection::EUP:
	case eEnemyDirection::EDOWN:
	{
		float diff = location.y - velocity.y;
		if (((now_direction == eEnemyDirection::EUP) && (diff < 0.0f)) ||
			((now_direction == eEnemyDirection::EDOWN) && (0.0f < diff)))
		{
			// 移動方向に移動してるので break
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
			// 移動方向に移動してるので break
			break;
		}
	}
	break;

	default:// 何もしない
		break;
	}

	// 入力状態の取得
	InputManager* input = InputManager::GetInstance();

	// 現在パネルの状態を確認
	ePanelID panel = StageData::GetPanelData(location);

	// 入力から移動方向を設定
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

	// 進行方向の移動量を追加
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

	//// 前回座標の更新
	//old_location = location;

	//// 前回パネルの更新
	//old_panel = panel;

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;

	// 画面外に行ったら、反対側にワープさせる
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
	// ハウスの中の敵が、壁にぶつかると方向転換する
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

//巡回
void EnemyBase::PatrolMovement(float delta_second)
{
	// 現在パネルの状態を確認
	ePanelID panel = StageData::GetPanelData(location);

	// 方向変換フラグ
	if (get_flag == false && panel == ePanelID::NONE)
	{
		get_flag = true;
	}

	// 方向変換処理
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

		get_flag = false; //一度通路に行かないと変換しないようにする
	}
}

void EnemyBase::IzikeMovement(float delta_second)
{
	// ハウスの中でも移動できるようにする
	if (old_enemy_state == HOME)
	{
		HomeMovement(delta_second);
	}

	// いじけ状態解除
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
	// 現在パネルの状態を確認
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
