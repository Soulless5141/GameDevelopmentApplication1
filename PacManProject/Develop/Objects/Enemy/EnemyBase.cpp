#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	// ìñÇΩÇËîªíËÇÃê›íË
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
}

void EnemyBase::Update(float delta_second)
{

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{

}

void EnemyBase::Finalize()
{

}

eEnemyState EnemyBase::GetEnemyMode() const
{
	return enemy_state;
}