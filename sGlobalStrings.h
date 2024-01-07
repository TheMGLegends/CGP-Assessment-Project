#pragma once

#include <string>

// INFO: Ensures strings aren't entered incorrectly by defining specific strings using variables
struct sGlobalStrings
{
	static const std::string Tilemap;
	static const std::string Background;

	static const std::string Mario_Idle;
	static const std::string Mario_Run;
	static const std::string Mario_Jump;
	static const std::string Mario_Fall;
	static const std::string Mario_Death;

	static const std::string BulletBill_Fly;

	static const std::string Goomba_Walk;
	static const std::string Goomba_Death;

	static const std::string Coin_Rotating;


	static const std::string GroundTheme_Music;
	static const std::string Coin_SFX;
	static const std::string Mario_Death_SFX;
	static const std::string Mario_GoombaStomp_SFX;
	static const std::string Mario_Jump_SFX;

};

