#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"
#include "State/Enum/EnemyState.h"

// 進行方向状態
enum eEnemyDirection : unsigned char
{
	EUP,
	ERIGHT,
	EDOWN,
	ELEFT
};

enum eEnemyType : unsigned int
{
	AKABEI = 0,
	PINKY  = 1,
	AOSUKE = 2,
	GUZUTA = 3,
};

/// <summary>
/// エネミークラス
/// </summary>
class EnemyBase : public GameObject
{
public:
	

protected:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> eye_animation;
	class Player* player;
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;
	eEnemyState old_enemy_state;
	eEnemyDirection now_direction;			// 現在進行方向状態
	eEnemyDirection old_direction;			// 現在進行方向状態
	float animation_time;					// アニメーション時間
	eEnemyType enemy_type;
	int animation_count;					// アニメーション添字

	char now_type;

	class Akabei* akabei;
	class Aosuke* aosuke;
	class Guzuta* guzuta;
	class Pinky* pinky;

	int panel_x;
	int panel_y;

private:
	float world_time;
	float izike_time;

	float frame_time;
	float izike_right_time;
	bool right_flag;

	bool home_flag;
	float home_time;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	void AnimationControl(float delta_second);
	eEnemyState GetEnemyState();
	eEnemyDirection GetEnemyDirection();
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	void Movement(float delta_second);
	virtual void HomeMovement(float delta_second);
	virtual void PatrolMovement(float delta_second);
	virtual void IzikeMovement(float delta_second);
	virtual void GoHomeMovement(float delta_second);

	char ChangeEnemyType();

	void GetPlayer(Player* player);

	//eEnemyState GetIzike();

protected:
	virtual void AttackMovement(float delta_second);

	//eEnemyState GetEnemyMode() const;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	//virtual void OnHitCollision(GameObjectBase* hit_object) override;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	//void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	//void AnimationControl(float delta_second);
};