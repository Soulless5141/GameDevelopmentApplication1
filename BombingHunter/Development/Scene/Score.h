#pragma once

class Score 
{
private:
	class Scene* owner_scene;
	class Time* owner_time;
	int image[13];
	int s_omote[10];
	int t_omote[3];
	int score;
	int value;

public:
	Score(class Scene* owner);
	Score(class Time* time);
	~Score();

	void Initialize();  //‰Šú‰»ˆ—
	void Update();      //XVˆ—
	void Draw() const;  //•`‰æˆ—
	void Finalize();    //I—¹ˆ—

private:
	void ChangeFont();
};

