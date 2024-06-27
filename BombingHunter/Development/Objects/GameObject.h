#pragma once

#include"../Utility/Vector2D.h"

#define D_PIVOT_CENTER     //���W�̌��_���摜�̒��S�ɂ���

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;   //�ʒu���
	Vector2D box_size;        //��`�傫��
	double scale;        //�傫��
	double radian;       //����
	int image;           //�`�悷��摜
	int sound;           //�Đ����鉹��
	int mode;            //0;�v���C���[  1;�{��  2;�e�L  3;�G�̒e
	int delete_flag;     //�������J�����菈��
	int enemy_score;     //�e�G�̃X�R�A�ݒ�ϐ�
	int attack_flag;     //�U������
	//�ړ��̑���
	Vector2D velocity = 0.0f;  //�f�t�H���g�̓����ݒ�

public:
	GameObject();
	virtual~GameObject();

	virtual void Initialize();  //����������
	virtual void Update();      //�X�V����
	virtual void Draw() const;  //�`�揈��
	virtual void Finalize();    //�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	int GetMode();         //�I�u�W�F�N�g���[�h�擾����
	bool DeleteFlag();     //�������J���t���O�擾����
	int GetScore();        //�e�G�̃X�R�A�擾����
	bool GetAttackFlag();  //�U������擾����

	void GetVelocity(const Vector2D& velocity);  //�i�s�����擾����
};