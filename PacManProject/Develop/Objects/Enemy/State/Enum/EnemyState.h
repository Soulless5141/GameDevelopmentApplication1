#pragma once

enum eEnemyState : unsigned char
{
	HOME,
	ATACCK,		// 追尾状態
	PATROL,		// 巡回状態
	IZIKE,		// いじけ状態
	GOHOME		// 死亡状態
};