#pragma once

#include "../../EnemyBase.h"

class EnemyTypeFactory
{
	//�V���O���g���p ��������
private:
	static EnemyTypeFactory* instance;

private:
	EnemyTypeFactory() = default;
	EnemyTypeFactory(const EnemyTypeFactory&) = default;
	EnemyTypeFactory& operator=(const EnemyTypeFactory&) = default;
	//�V���O���g���p�����܂�

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
