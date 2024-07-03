#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	box_size(0),
	radian(0.0),
	image(0),
	sound(0),
	scale(0),
	mode(0),
	delete_flag(false),
	enemy_score(NULL),
	attack_flag(false)
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{
	
}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{
	//�����蔻��̉���
//#ifdef D_PIVOT_CENTER
//
//	Vector2D tl = location - (box_size / 2.0f);
//	Vector2D br = location + (box_size / 2.0f);
//
//	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#else
//	Vector2D tl = location;
//	Vector2D br = location + box_size;
//
//	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
//#endif  // D_PIVOT_CENTER
}

//�I������
void GameObject::Finalize()
{
	
}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	Finalize();
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�G�̑傫���擾����
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//�I�u�W�F�N�g�̎�ގ擾����
int GameObject::GetMode()
{
	return mode;
}

//�폜�t���O����
bool GameObject::DeleteFlag()
{
	return delete_flag;
}

//�|�����G�̃X�R�A�擾����
int GameObject::GetScore()
{
	return enemy_score;
}

//�G�̍U�����菈��
bool GameObject::GetAttackFlag()
{
	return attack_flag;
}

//����������擾����
void GameObject::GetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}