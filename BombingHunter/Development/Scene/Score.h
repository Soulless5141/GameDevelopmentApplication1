#pragma once

#define MAX_SCORE_DIGIT (10)   //�X�R�A�̍ő包��
#define MAX_TIME_DIGIT (3)     //���Ԃ̍ő包��
#define MAX_IMAGES (13)        //�摜�̐�

class Score 
{
private:
	class Scene* owner_scene;  //scene�ւ̃A�N�Z�X
	int image[MAX_IMAGES];             //�ő�摜����
	int s_omote[MAX_SCORE_DIGIT];      //�X�R�A�̍ő包��
	int t_omote[MAX_TIME_DIGIT];       //���Ԃ̍ő包��
	int score;                 //�X�R�A
	int time;                  //����
	int count_time;            //1�b�̌v�Z
	int lost_time;             //�ϓ������Ă�������
	int value;                 //�����̉摜�����邽�߂̕ς��

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

	void DamegeFlag();  //�v���C���[��e����

	int GetTime();      //���Ԏ擾����

private:
	void ChangeFont();  //UI�ύX����
};

