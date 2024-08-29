#pragma once

typedef struct SaveData
{
    unsigned char highScore;
    unsigned char scale : 3;
    unsigned char windowMode : 2;
    unsigned char filter : 2;
} SaveData;

#define PLAYER_DATA_FILENAME "Snake.sav"
#define DEFAULT_SAVE_DATA (SaveData){3, 2, 0, 0}

void SavePlayerData(const SaveData* const saveData);
void LoadPlayerData(SaveData* const saveData);