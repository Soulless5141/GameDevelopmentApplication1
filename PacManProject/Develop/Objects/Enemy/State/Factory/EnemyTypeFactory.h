#pragma once

#include "../../EnemyBase.h"

class EnemyTypeFactory
{
	//シングルトン用 ここから
private:
	static EnemyTypeFactory* instance;

private:
	EnemyTypeFactory() = default;
	EnemyTypeFactory(const EnemyTypeFactory&) = default;
	EnemyTypeFactory& operator=(const EnemyTypeFactory&) = default;
	//シングルトン用ここまで

private:
	class Akabei* akabei;
	class Aosuke* aosuke;
	class Guzuta* guzuta;
	class Pinky* pinky;

private:
	void Initialize(class EnemyBase& enemy);

public:
	static EnemyBase* Get(class EnemyBase& enemy, eEnemyState state, eEnemyType type);
	static void Finalize();
};
