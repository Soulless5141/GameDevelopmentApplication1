#pragma once

#include"../GameObject.h"


class Bom :public GameObject
{
private:
	int animation[4];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V�����ύX����
	int bom_count;
	int next_flag;
	Vector2D direction;    //�i�s����


public:
	Bom();
	~Bom();

	virtual void Initialize() override;  //����������
	virtual void Update() override;      //�X�V����
	virtual void Draw() const override;  //�`�揈��
	virtual void Finalize() override;    //�I��������
	

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	void Func(Vector2D player);
private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();
};

