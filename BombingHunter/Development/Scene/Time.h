#pragma once
class Time
{
private:
	Score* score_class;
	class Scene* owner_scene;
	int time;

public:
	Time();
	/*Time();*/
	~Time();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

	int GetTime();

	void DamegeFlag();

private:
	
};

