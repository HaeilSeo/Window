#pragma once
#include<Windows.h>
#include <stdio.h>
#include"graphic.h"

#define DDPF_ALPHAPIXELS 0x00000001
#define DDPF_RGB		 0x0000040

struct DDS_PIXELFORMAT {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwABitMask;
};

struct DDS_HEADER {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwHeight;
	DWORD dwWidth;
	DWORD dwPitchOrLinearSize;
	DWORD dwDepth;
	DWORD dwMipMapCount;
	DWORD dwReserved1[11];
	DDS_PIXELFORMAT ddspf;
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCaps3;
	DWORD dwCaps4;
	DWORD dwReserved2;
};

struct DDS_FILE {
	DWORD magic;
	DDS_HEADER header;
	BYTE data[1];
};


DDS_FILE* readDDS(const char* filename);
DDS_FILE* readDDSRect(const char* filename, int x, int y, int width, int height);