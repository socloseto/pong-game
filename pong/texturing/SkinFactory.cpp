
#include "SkinFactory.h"
#include "TextureSkin.h"
#include <map>

std::unique_ptr<BallSkin> SkinFactory::CreateSkin(ballSkinType type) {
	static const std::map<ballSkinType, std::string> skinPaths = {
		{DonutEye,   "images/DonutEye.png"},
		{Watermelon, "images/Watermelon.png"},
		{BlueEye,    "images/BlueEye.png"},
		{CyclopeEye, "images/CyclopeEye.png"},
		{CrackedEye, "images/CrackedEye.png"}
	};
	auto it = skinPaths.find(type);
	if (it != skinPaths.end()) {
		return std::make_unique<TextureSkin>(it->second);
	}
	return nullptr;

}
