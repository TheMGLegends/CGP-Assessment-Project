#pragma once
#include <string>

class cTextureStrings
{
public:
	/* INFO: Ensures strings aren't entered incorrectly by defining specific strings using variables
	* EXAMPLE:
	* static const std::string PLAYER_IDLE = "Player_Idle";
	*/

	static const std::string Tilemap;
	static const std::string Background;

	static const std::string Mario_Idle;
	static const std::string Mario_Run;
	static const std::string Mario_Jump;
	static const std::string Mario_Fall;

	static const std::string BulletBill_Fly;

	static const std::string Goomba_Walk;
	static const std::string Goomba_Death;
};

