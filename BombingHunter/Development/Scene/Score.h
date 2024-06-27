#pragma once

//#include "Time.h"

class Score 
{
private:
	class Scene* owner_scene;
	int image[13];
	int s_omote[10];
	int t_omote[10];
	int score;
	int time;
	int count_time;
	int lost_time;
	int value;

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

	void DamegeFlag();

private:
	void ChangeFont();
};

