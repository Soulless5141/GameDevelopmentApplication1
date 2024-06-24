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

	void Initialize();  //‰Šú‰»ˆ—
	void Update();      //XVˆ—
	void Draw() const;  //•`‰æˆ—
	void Finalize();    //I—¹ˆ—

private:
	void ChangeFont();
};

