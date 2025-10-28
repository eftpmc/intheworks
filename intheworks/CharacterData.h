#pragma once
#include <string>

struct CharacterData {
	std::string textureName;
	int width, height;
	int size;
	int padding;
	int stepPixels;
	float moveSpeed;
};