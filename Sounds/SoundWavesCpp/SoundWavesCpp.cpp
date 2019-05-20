#include "Windows.h"

#include <string>
#include <fstream>
#include <iostream>

int main()
{
	HWAVEOUT		hwo;
	WAVEFORMATEX	format;
	LPVOID			memblock;
	LPWAVEHDR		lpWaveHdr;
	HANDLE			hHeap = GetProcessHeap();
	DWORD_PTR		callback;
	MMRESULT result;


	std::ifstream	file(
		"C:\\devel\\resources\\carlin_boring.wav",
		std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		std::cout << "Could not open file";

		return -1;
	}

	auto sw_size = file.tellg();
	memblock = HeapAlloc(hHeap, HEAP_GENERATE_EXCEPTIONS, sw_size);

	file.seekg(0, std::ios::beg);
	file.read((char*)memblock, sw_size);
	file.close();

	format.nChannels = 1;
	format.wBitsPerSample = 8;
	format.nSamplesPerSec = 11000;
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
	format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

	MMRESULT odres = waveOutOpen(
		&hwo, WAVE_MAPPER, &format, NULL, NULL, CALLBACK_FUNCTION);

	if (odres != MMSYSERR_NOERROR) {
		std::cout << "Error while opening device: " << ": " << odres;

		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, memblock);

		return odres;
	}

	lpWaveHdr = (LPWAVEHDR)HeapAlloc(
		hHeap, HEAP_ZERO_MEMORY, sizeof(WAVEHDR));

	if (lpWaveHdr == NULL) {
		return -1;
	}

	lpWaveHdr->dwBufferLength = sw_size;
	lpWaveHdr->lpData = (LPSTR)memblock;
	lpWaveHdr->dwFlags = 0;
	lpWaveHdr->dwLoops = 0;
	
	result = waveOutPrepareHeader(hwo, lpWaveHdr, sizeof(WAVEHDR));
	if (result != MMSYSERR_NOERROR) {
		std::cout << "Error while preparing header: " << ": " << result;

		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, memblock);
		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, lpWaveHdr);

		return result;
	}

	if (!(lpWaveHdr->dwFlags & WHDR_PREPARED)) {
		std::cout << "Error while preparing header: flag not set";

		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, memblock);
		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, lpWaveHdr);

		return -1;
	}

	result = waveOutWrite(hwo, lpWaveHdr, sizeof(WAVEHDR));
	if (result != MMSYSERR_NOERROR) {
		std::cout << "ERR";

		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, memblock);
		HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, lpWaveHdr);

		return -1;
	}
	
	while ((result = waveOutUnprepareHeader(
	  hwo, lpWaveHdr, sizeof(WAVEHDR))) == WAVERR_STILLPLAYING) {
		Sleep(100);
	}

	waveOutClose(hwo);

	HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, memblock);
	HeapFree(hHeap, HEAP_GENERATE_EXCEPTIONS, lpWaveHdr);

	return 0;
}
