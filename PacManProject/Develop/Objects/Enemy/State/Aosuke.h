#pragma once
#include "../EnemyBase.h"
#include "../../Utility/Vector2D.h"

class Aosuke : public EnemyBase
{
private:
	Vector2D old_location;					// �O����W���
	ePanelID old_panel;						// �O��p�l�����

public:
	Aosuke(class EnemyBase* enemy);
	~Aosuke();

public:
	//�����������֐�
	virtual void Initialize() override;

	void AttackMovement(float delta_second);
};

