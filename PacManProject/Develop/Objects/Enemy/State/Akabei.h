#pragma once
#include "../EnemyBase.h"
#include "../../Utility/Vector2D.h"

class Akabei : public EnemyBase
{
private:
	Vector2D old_location;					// 前回座標情報
	ePanelID old_panel;						// 前回パネル情報

public:
	Akabei(class EnemyBase* enemy);
	~Akabei();

public:
	//初期化処理関数
	virtual void Initialize() override;

	void AttackMovement(float delta_second);
};