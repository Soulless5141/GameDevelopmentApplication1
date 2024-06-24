#pragma once
#include"../GameObject.h"

class Haneteki : public GameObject
{
private:
	int ptn;
	int animation[2];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	int attack_time;
	Vector2D direction;    //�i�s����
	//�ړ��̑���
	Vector2D velocity = 0.0f;

public:
	Haneteki();
	~Haneteki();

	virtual void Initialize() override;  //����������
	virtual void Update() override;      //�X�V����
	virtual void Draw() const override;  //�`�揈��
	virtual void Finalize() override;    //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();

	void AttackControl();
};

