#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include "Score.h"

class Scene
{
private:
	int background_image;
	int sound;
	int enemy_count[4];
	int bom_set;
	int cool_count;
	int mode;
	int score;
	int attack_flag;

	std::vector<GameObject*>objects;
	Score* score_class;

public:
	Scene();
	~Scene();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

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
		new_object->GetVelocity(velocity);
		//����������
		new_object->Initialize();

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;

	}
};

