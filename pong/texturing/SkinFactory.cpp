
#include "SkinFactory.h"
#include "TextureSkin.h"
#include <map>

std::unique_ptr<BallSkin> SkinFactory::CreateSkin(ballSkinType type) {
    static const std::map<ballSkinType, std::string> skinPaths = {
        {DonutEye,   "IDB_PNG4"},
        {Watermelon, "IDB_PNG5"},
        {BlueEye,    "IDB_PNG1"},
        {CyclopeEye, "IDB_PNG3"},
        {CrackedEye, "IDB_PNG2"}
    };
    auto it = skinPaths.find(type);
    if (it != skinPaths.end()) {
        return std::make_unique<TextureSkin>(it->second);
    }
    return nullptr;

}
