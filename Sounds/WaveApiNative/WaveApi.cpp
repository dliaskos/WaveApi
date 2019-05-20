#include <Windows.h>

#include "WaveApi.h"

UINT waveapi_waveOutOpen(LPHWAVEOUT lphwo, WORD channels, WORD bitsPerSample,
    DWORD samplesPerSec, WORD formatTag)
{
    WAVEFORMATEX    format;

    if (formatTag != WAVE_FORMAT_PCM) {
        return MMSYSERR_ERROR;
    }

    format.nChannels = channels;
    format.wBitsPerSample = bitsPerSample;
    format.nSamplesPerSec = samplesPerSec;
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

    return waveOutOpen(lphwo, WAVE_MAPPER,
        &format, NULL, NULL, CALLBACK_FUNCTION);
}

UINT waveapi_waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR &lpwhdr, LPSTR buffer,
    DWORD bufferLength)
{
    LPWAVEHDR local = (LPWAVEHDR)HeapAlloc(
        GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WAVEHDR));

    if (local == NULL) {
        return MMSYSERR_ERROR;
    }

    local->dwFlags = 0;
    local->dwLoops = 0;
    local->lpData = buffer;
    local->dwBufferLength = bufferLength;

    auto result = waveOutPrepareHeader(hwo, local, sizeof(WAVEHDR));

    lpwhdr = local;

    return result;
}

UINT waveapi_waveOutWrite(HWAVEOUT hwo, LPWAVEHDR lpwhdr)
{
    return waveOutWrite(hwo, lpwhdr, sizeof(WAVEHDR));
}
