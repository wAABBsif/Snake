#include "SaveData.h"
#include <stdio.h>

void SavePlayerData(const SaveData* const saveData)
{
    FILE* stream = fopen(PLAYER_DATA_FILENAME, "w");
    if (stream == NULL)
    {
        printf("Could not save player data!\n");
        return;
    }

    fwrite(saveData, sizeof(SaveData), 1, stream);
    fclose(stream);
}

void LoadPlayerData(SaveData* const saveData)
{
    FILE* stream = fopen(PLAYER_DATA_FILENAME, "r");
    if (stream == NULL)
    {
        *saveData = DEFAULT_SAVE_DATA;
        printf("Could not load player data!\n");
        return;
    }

    fread(saveData, sizeof(SaveData), 1, stream);
    fclose(stream);
}