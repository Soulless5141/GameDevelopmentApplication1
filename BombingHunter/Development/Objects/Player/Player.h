#pragma once

#include"../GameObject.h"
#include"../Enemy/Tama.h"

class Player : public GameObject
{
private:
	int animation[2];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V�����ύX����
	int filp_flag;         //���]�t���O

	Tama* tama_class;

public:
	Player();
	~Player();

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

