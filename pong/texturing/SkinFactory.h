#pragma once
#include <memory>
#include "BallSkin.h"
class SkinFactory {

public:
	enum ballSkinType {
		DonutEye,
		Watermelon,
		BlueEye,
		CyclopeEye,
		CrackedEye,

	};
	
	static	std::unique_ptr<BallSkin> CreateSkin(ballSkinType TextureSkin);

};
