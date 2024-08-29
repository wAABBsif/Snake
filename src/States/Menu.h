#pragma once
#include "../Core.h"

#define MENU_TITLE_SIZE 50
#define MENU_TITLE_POSITION 32
#define MENU_TITLE_COLOR (Color){0x63, 0x9B, 0xFF, 0xFF}

#define MENU_TEXT_SIZE 20
#define MENU_TEXT_START_POSITION 96
#define MENU_TEXT_SPACING 24

void _Menu_Start(GameData* game, const unsigned char prevState);
void _Menu_Update(GameData* game);
void _Menu_Draw(const GameData* game);