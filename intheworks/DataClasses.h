#pragma once
#include <string>

struct Size {
	Size(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

struct CharacterData {
	CharacterData(
		const float moveSpeed
	) : moveSpeed(moveSpeed)
	{
	}

	const float moveSpeed;
};

struct AnimatedSpriteData {
    AnimatedSpriteData(
        const std::string& textureName,
        int width,
        int height,
        Size size,
        int padding,
        int stepPixels,
		float frameTime
    )
        : textureName(textureName),
        width(width),
        height(height),
        size(size),
        padding(padding),
        stepPixels(stepPixels),
		frameTime(frameTime)
    {
    }

    const std::string textureName;
    const int width;
    const int height;
	const Size size;
    const int padding;
    const int stepPixels;
	const float frameTime;
};