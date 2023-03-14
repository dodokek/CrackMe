#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>
#include <stdlib.h>
#include "fileUtils.h"


const int MAX_BIN_FILE_LEN = 5000;

void patch_comfile (char* buffer_res);

void DrawVideo();

sf::Sprite *GenerateImageSprite (char* img_name, int x_coord, int y_coord);

sf::Texture DrawTrollface();

sf::Text *GenerateTextSprite (sf::Font &font, char* content, float x_coord, float y_coord);

sf::RectangleShape GenerateRectangle (float width, float height, float x, float y);

void PlayMusic (char* filename);

void patch_comfile ();