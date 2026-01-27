
#include "SkinFactory.h"
#include "TextureSkin.h"
#include <map>
#include "../assets/images/DonutEye_png.h"
#include "../assets/images/Watermelon_png.h"
#include "../assets/images/BlueEye_png.h"
#include "../assets/images/CyclopeEye_png.h"
#include "../assets/images/CrackedEye_png.h"

struct EmbeddedResource {
	const unsigned char* data;
	unsigned int size;
};
std::unique_ptr<BallSkin> SkinFactory::CreateSkin(ballSkinType type) {
	static const std::map<ballSkinType, EmbeddedResource> embeddedSkins = {
		{DonutEye,   {DonutEye_png,   DonutEye_png_len}},
		{Watermelon, {Watermelon_png, Watermelon_png_len}},
		{BlueEye,    {BlueEye_png,    BlueEye_png_len}},
		{CyclopeEye, {CyclopeEye_png, CyclopeEye_png_len}},
		{CrackedEye, {CrackedEye_png, CrackedEye_png_len}}
	};
	auto it = embeddedSkins.find(type);
	if (it != embeddedSkins.end()) {
		return std::make_unique<TextureSkin>(it->second.data, it->second.size);
	}
	return nullptr;
}
