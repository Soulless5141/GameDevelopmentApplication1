#pragma once

#include "vector"

#include"../GameObject.h"

#define ANIMATION_IMAGES (4) //�摜����

class Bom :public GameObject
{
private:
	int animation[ANIMATION_IMAGES];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V�����ύX����
	bool next_flag;        //���j���[�V�����Ɉڍs����
	Vector2D direction;    //�i�s����

	std::vector<int> animation_data;  //�A�j���[�V�����f�[�^
	std::vector<int> sounds_data;  //�A�j���[�V�����f�[�^

public:
	Bom();
	~Bom();

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

