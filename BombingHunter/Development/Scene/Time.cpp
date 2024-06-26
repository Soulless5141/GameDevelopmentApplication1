#include "Time.h"
#include "Score.h"
#include "DxLib.h"

Time::Time():time(0),score_class(nullptr)
{

}

Time::~Time()
{

}

void Time::Initialize()
{
	time = 12000;
}

void Time::Update()
{
	time = time - 1;
}

void Time::Draw() const
{

}

void Time::Finalize()
{

}

void Time::DamegeFlag()
{
	time = time - 500;
}

int Time::GetTime()
{
	return time;
}
