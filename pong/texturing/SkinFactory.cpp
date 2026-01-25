
#include "SkinFactory.h"
#include "TextureSkin.h"
#include <map>

std::unique_ptr<BallSkin> SkinFactory::CreateSkin(ballSkinType type) {
	static const std::map<ballSkinType, std::string> skinPaths = {
		{DonutEye,   "assets/images/DonutEye.png"},
		{Watermelon, "assets/images/Watermelon.png"},
		{BlueEye,    "assets/images/BlueEye.png"},
		{CyclopeEye, "assets/images/CyclopeEye.png"},
		{CrackedEye, "assets/images/CrackedEye.png"}
	};
	auto it = skinPaths.find(type);
	if (it != skinPaths.end()) {
		return std::make_unique<TextureSkin>(it->second);
	}
	return nullptr;

}
