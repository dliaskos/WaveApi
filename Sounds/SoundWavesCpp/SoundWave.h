#pragma once

#include "Windows.h"

class SoundWave
{
	HANDLE hHeap_;

public:
	SoundWave();
	~SoundWave();

	void Play(WORD channels, WORD bitsPerSample, DWORD samplesPerSec);

};

