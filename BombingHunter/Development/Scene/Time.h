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

	void Initialize();  //‰Šú‰»ˆ—
	void Update();      //XVˆ—
	void Draw() const;  //•`‰æˆ—
	void Finalize();    //I—¹ˆ—

	int GetTime();

	void DamegeFlag();

private:
	
};

