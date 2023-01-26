//
// Created by pinkynyte on 1/26/23.
//

#ifndef HOMICSIM_SIMULATORSPRITE_H
#define HOMICSIM_SIMULATORSPRITE_H

#include "olcPixelGameEngine.h"
#include "constants.h"
#include <vector>
#include <string>

class simulatorSprite {
public:
    simulatorSprite() = default;

    void init(float x, float y, std::initializer_list<std::string> spritePaths) {
        for (const auto& path : spritePaths) {
            sprites.push_back({{x, y}, std::make_shared<olc::Sprite>(path)});
        }
    }

    [[nodiscard]] const olc::Sprite& getSprite(int index) const {
        return *sprites[index].second;
    }

    // Begin
    [[nodiscard]] const std::pair<olc::vf2d, std::shared_ptr<olc::Sprite>>& getSpriteBegin() const {
        return sprites[0];
    }

    // End
    [[nodiscard]] const std::pair<olc::vf2d, std::shared_ptr<olc::Sprite>>& getSpriteEnd() const {
        return sprites[sprites.size() - 1];
    }

private:
    std::vector<std::pair<olc::vf2d, std::shared_ptr<olc::Sprite>>> sprites;
    float scale { 1.0f };
};

#endif //HOMICSIM_SIMULATORSPRITE_H
