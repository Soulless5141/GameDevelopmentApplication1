#pragma once
#include "../EnemyBase.h"
#include "../../Utility/Vector2D.h"

class Pinky : public EnemyBase
{
private:
	Vector2D old_location;					// 前回座標情報
	ePanelID old_panel;						// 前回パネル情報

public:
	Pinky(class EnemyBase* enemy);
	~Pinky();

public:
	//初期化処理関数
	virtual void Initialize() override;

	void AttackMovement(float delta_second);
};

