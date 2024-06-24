#pragma once

class Score 
{
private:
	class Scene* owner_scene;
	int image[11];
	int omote[10];
	int score;
	int value;

public:
	Score(class Scene* owner);
	~Score();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I������

private:
	void ChangeFont();
};

