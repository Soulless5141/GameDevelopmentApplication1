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

	void Initialize();  //‰Šú‰»ˆ—
	void Update();      //XVˆ—
	void Draw() const;  //•`‰æˆ—
	void Finalize();    //I—¹ˆ—

	void DamegeFlag();

private:
	void ChangeFont();
};

