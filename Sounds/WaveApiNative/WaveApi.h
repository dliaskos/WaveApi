#pragma once

#include <Windows.h>

#define WAVE_API __declspec(dllexport)

extern "C" WAVE_API UINT __stdcall waveapi_waveOutOpen(LPHWAVEOUT lphwo,
    WORD channels, WORD bitsPerSample, DWORD samplesPerSec, WORD formatTag);

extern "C" WAVE_API UINT __stdcall waveapi_waveOutPrepareHeader(HWAVEOUT hwo,
    LPWAVEHDR &lpwhdr, LPSTR buffer, DWORD bufferLength);

extern "C" WAVE_API UINT __stdcall waveapi_waveOutWrite(HWAVEOUT hwo,
    LPWAVEHDR lpwhdr);
