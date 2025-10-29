#pragma once
#include <string>

struct CharacterData {
	CharacterData(
		const std::string textureName,
		const int width,
		const int height,
		const int size,
		const int padding,
		const int stepPixels,
		const float moveSpeed
	) : textureName(textureName),
		width(width),
		height(height),
		size(size),
		padding(padding),
		stepPixels(stepPixels),
		moveSpeed(moveSpeed)
	{
	}

	const std::string textureName;
	const int width, height;
	const int size;
	const int padding;
	const int stepPixels;
	const float moveSpeed;
};