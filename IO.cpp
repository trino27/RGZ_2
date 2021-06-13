//______________Made_by_Artem_______________
#include <iostream>
#include <Windows.h>
#include <fstream>

#include "main.h"

using namespace std;

//Функція зчитування зображення до масиву
void read(RGBTRIPLE**& Map, BITMAPFILEHEADER& BFH, BITMAPINFOHEADER& BIH, FILE *f) {
	
	fread(&BFH, sizeof(BITMAPFILEHEADER), 1, f);//зчитування заголовку файла
	fread(&BIH, sizeof(BITMAPINFOHEADER), 1, f);//зчитування інформаційного заголовку
	
	int sep = 4 - (BIH.biWidth * 3) % 4; //обчислення кількості байт між строками пікселів
	
	// Виділення пам'яті під масив пікселів
	Map = new RGBTRIPLE * [BIH.biHeight]; 
	for (int i = 0; i < BIH.biHeight; i++) {
		Map[i] = new RGBTRIPLE[BIH.biWidth];
	}
	
	// Зчитування зображення в масив
	for (int i = BIH.biHeight - 1; i >= 0; i--) {
		for (int j = 0; j < BIH.biWidth; j++) {
			Map[i][j].rgbtBlue = fgetc(f);
			Map[i][j].rgbtGreen = fgetc(f);
			Map[i][j].rgbtRed = fgetc(f);
		}
		for (int j = 0; j < sep; j ++) fgetc(f); 
	}
}

//Функція виведення в файл
void Print(char**& ASCII, int Width, int Height)
{	
	string out_file;
	cout << "Enter way to output: ";
	cin >> out_file;
	ofstream out(out_file + ".txt");

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			out << ASCII[i][j]; out << ASCII[i][j];
		}
		out << endl;
	}
	
}