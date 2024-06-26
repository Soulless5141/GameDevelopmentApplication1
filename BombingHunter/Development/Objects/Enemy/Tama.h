#pragma once
#include"../GameObject.h"

class Tama : public GameObject
{
private:
	int p_location;
	int animation[4];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	int next_flag;
	Vector2D direction;    //�i�s����

public:
	Tama();
	~Tama();

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
};

