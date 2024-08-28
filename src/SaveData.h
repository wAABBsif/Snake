#pragma once
#define PLAYER_DATA_FILENAME "Snake.sav"

typedef struct SaveData
{
    unsigned short highScore : 11;
    unsigned short fullScreen : 1;
    unsigned short scale : 3;
    unsigned short filter : 1;
} SaveData;

#define DEFAULT_SAVE_DATA (SaveData){3, 0, 2, 0}

void SavePlayerData(const SaveData* const saveData);
void LoadPlayerData(SaveData* const saveData);