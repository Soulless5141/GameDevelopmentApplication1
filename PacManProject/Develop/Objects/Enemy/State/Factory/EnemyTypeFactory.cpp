#include "EnemyTypeFactory.h"
#include "../Akabei.h"
#include "../Aosuke.h"
#include "../Guzuta.h"
#include "../Pinky.h"

#include "../../EnemyBase.h"

EnemyTypeFactory* EnemyTypeFactory::instance = nullptr;

void EnemyTypeFactory::Initialize(class EnemyBase& enemy)
{
	akabei = new Akabei(&enemy);
	aosuke = new Aosuke(&enemy);
	guzuta = new Guzuta(&enemy);
	pinky = new Pinky(&enemy);
}

void EnemyTypeFactory::Finalize()
{
	delete instance->akabei;
	delete instance->aosuke;
	delete instance->guzuta;
	delete instance->pinky;
}

EnemyBase* EnemyTypeFactory::Get(EnemyBase& enemy, eEnemyState state , eEnemyType type)
{
	if (instance == nullptr)
	{
		instance = new EnemyTypeFactory();
		instance->Initialize(enemy);
	}

	EnemyBase* ret = nullptr;

	switch (type)
	{
	case eEnemyType::AKABEI:
		instance->akabei->Initialize();
		ret = instance->akabei;
		break;
	case eEnemyType::AOSUKE:
		instance->aosuke->Initialize();
		ret = instance->aosuke;
		break;
	case eEnemyType::GUZUTA:
		instance->guzuta->Initialize();
		ret = instance->guzuta;
		break;
	case eEnemyType::PINKY:
		instance->pinky->Initialize();
		ret = instance->pinky;
		break;
	default:
		break;
	}
	
	return ret;
}
