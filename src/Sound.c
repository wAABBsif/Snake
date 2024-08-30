#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Sound.h"

typedef struct dirent dirent;

static SoundEntry s_soundEntries[7];
static unsigned char s_textureEntryCount;

void Sound_Initialize()
{
	DIR* d = opendir("res/");;
	if (d)
	{
		while (true)
		{
			const dirent* dir = readdir(d);
			if (dir == NULL)
				break;
			if (strstr(dir->d_name, ".wav"))
				_Sound_Load(dir->d_name);
		}
		closedir(d);
	}
}

void _Sound_Load(const char* name)
{
	char filePath[32] = "res/";
	strcat(filePath, name);
	strcpy(s_soundEntries[s_textureEntryCount].name, name);
	s_soundEntries[s_textureEntryCount].sound = LoadSound(filePath);
	s_textureEntryCount++;
}

void Sound_Play(const char* name)
{
	for (unsigned char i = 0; i < s_textureEntryCount; i++)
	{
		if (strcmp(s_soundEntries[i].name, name) == 0)
			return PlaySound(s_soundEntries[i].sound);
	}

	printf("Sound [%s] could not be found!\n", name);
}

void Sound_Free(void)
{
	for (unsigned char i = 0; i < s_textureEntryCount; i++)
		UnloadSound(s_soundEntries[i].sound);
}