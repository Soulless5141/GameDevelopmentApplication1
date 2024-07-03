#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include "Score.h"

#define ENEMY_KINDS   (4)//�G�̐�
#define MAX_RESULT    (5)//���U���g�摜��

class Scene
{
private:
	int background_image;  //�w�i�摜
	int sounds[6];         //����
	int sound;             //�Đ��p����
	int enemy_count[ENEMY_KINDS];    //�G�̏o���p�x
	int bom_set;           //�{���̔��˃t���O
	int cool_count;        //�{���̃N�[���^�C��
	int mode;              //�I�u�W�F�N�g���ʔԍ�
	int score;             //�X�R�A
	int time;              //����
	int result_count;      //���U���g�̐i�s����
	int result_score[MAX_RESULT];   //���U���g�̉摜
	int image;             //����p�摜�ϐ�
	bool result_flag;      //���U���g�@�ۃt���O

	std::vector<GameObject*>objects;
	Score* score_class;

public:
	Scene();
	~Scene();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

	//�|�����G�̃X�R�A���擾����
	int GetScore();

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

private:
	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location, const Vector2D& velocity)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);
		//�i�s�����擾����
		new_object->GetVelocity(velocity);
		//����������
		new_object->Initialize();

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;

	}
};

