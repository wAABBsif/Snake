#pragma once
#include "Core.h"

typedef struct SoundEntry
{
	const char name[32];
	Sound sound;
} SoundEntry;

void Sound_Initialize();
void _Sound_Load(const char* name);
void Sound_Play(const char* name);
void Sound_Free(void);