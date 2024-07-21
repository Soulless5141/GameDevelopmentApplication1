#pragma once

#include "EnemyBase.h"
#include "../GameObject.h"

class EnemyRed : public EnemyBase
{
private:
	std::vector<int> move_animation;
	std::vector<int> eye_animation;
	eEnemyState enemy_state;

public:
	EnemyRed();
	virtual ~EnemyRed();

	void Initialize();
	void Update(float) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	eEnemyState GetenemyMode() const;

	void Movement(float) const;

};

