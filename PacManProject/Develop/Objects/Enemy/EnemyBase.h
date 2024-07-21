#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

enum eEnemyState
{
	HOME,
	ATACCK,		// 追尾状態
	PATROL,		// 巡回状態
	IZIKE,		// いじけ状態
	GOHOME		// 死亡状態
};

/// <summary>
/// エネミークラス
/// </summary>
class EnemyBase : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	float animation_time;					// アニメーション時間
	const int animation_num[4];
	const int animation_eye[4];
	int animation_count;					// アニメーション添字
	

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	eEnemyState GetEnemyMode() const;

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