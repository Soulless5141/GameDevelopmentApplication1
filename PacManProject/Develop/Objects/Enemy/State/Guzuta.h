#pragma once
#include "../EnemyBase.h"
#include "../../Utility/Vector2D.h"

class Guzuta : public EnemyBase
{
private:
	Vector2D old_location;					// �O����W���
	ePanelID old_panel;						// �O��p�l�����

public:
	Guzuta(class EnemyBase* enemy);
	~Guzuta();

public:
	//�����������֐�
	virtual void Initialize() override;

	void AttackMovement(float delta_second);
};

