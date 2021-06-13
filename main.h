#pragma once
#include <string>
#include <Windows.h>

void read(RGBTRIPLE**& Map, BITMAPFILEHEADER &FHeader, BITMAPINFOHEADER &IHeader, FILE *f);

void Convert(RGBTRIPLE**& Map, char**& ASCII, int Width, int Height);

void Print(char**& ASCII, int Width, int Height);