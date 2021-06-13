#pragma warning(disable : 4996)

#include <iostream>
#include <Windows.h>

#include "main.h"

using namespace std;

int main() {

	BITMAPFILEHEADER FHeader;
	BITMAPINFOHEADER IHeader;
	RGBTRIPLE** Map;
	
	FILE *f = fopen("test.bmp", "rb");

	read(Map, FHeader, IHeader, f);

	char** ASCII;

	Convert(Map, ASCII, IHeader.biWidth, IHeader.biHeight);

	Print(ASCII, IHeader.biWidth, IHeader.biHeight);

	return 0;
}