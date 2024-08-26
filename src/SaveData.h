#pragma once
#define PLAYER_DATA_FILENAME "Snake.sav"

typedef struct SaveData
{
    unsigned short fullScreen : 1;
    unsigned short scale : 3;
    unsigned short highScore : 12;
} SaveData;

#define DEFAULT_SAVE_DATA ((SaveData){ 0, 2, 5})

void SavePlayerData(const SaveData* const saveData);
void LoadPlayerData(SaveData* const saveData);