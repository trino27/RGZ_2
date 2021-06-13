//___________________Made_by_Artem___________________________

#include <iostream>
#include <windows.h>

#include "main.h"

using namespace std;

// Масив для заміни кольорових пікселів
const unsigned char Chars[3][6][3] = { { { 'r', 'T', 'R' }, { 'z', 'u', 'y' }, { 'f', '[', 'g' }, { 'c', 's', 'q' }, { 'x', 'h', 'b' }, { 'a', 'l', 'p' } },
									   { { '-', '~', '{' }, { 'v', 'U', 'Y' }, { 'e', 'O', 'G' }, { 'd', 'C', 'Q' }, { 'w', 'H', 'B' }, { 'j', 'L', 'P' } },
									   { { '2', 't', '6' }, { '`', 'F', 'i' }, { '0', 'o', '>' }, { '^', '*', '&' }, { ',', '|', '/' }, { '.', '+', ';' } } };


// Масив для заміни чорно-білих пікселів
const unsigned char Chars2[25] = { '#', '%', '|'};


// Функція пошуку максимому та мінімуму з структури RGBTRIPLE
void Max_Min(RGBTRIPLE Pixel, int& Max, int& Min) {
	if (Pixel.rgbtRed > Pixel.rgbtGreen && Pixel.rgbtRed > Pixel.rgbtBlue) {
		Max = Pixel.rgbtRed;
	}
	else if (Pixel.rgbtGreen > Pixel.rgbtRed && Pixel.rgbtGreen > Pixel.rgbtBlue) {
		Max = Pixel.rgbtGreen;
	}
	else if (Pixel.rgbtBlue > Pixel.rgbtRed && Pixel.rgbtBlue > Pixel.rgbtGreen) {
		Max = Pixel.rgbtBlue;
	}
	else {
		Max = Pixel.rgbtBlue;
		Min = Pixel.rgbtBlue;
		return;
	}

	if (Pixel.rgbtRed < Pixel.rgbtGreen && Pixel.rgbtRed < Pixel.rgbtBlue) {
		Min = Pixel.rgbtRed;
	}
	else if (Pixel.rgbtGreen < Pixel.rgbtRed && Pixel.rgbtGreen < Pixel.rgbtBlue) {
		Min = Pixel.rgbtGreen;
	}
	else if (Pixel.rgbtBlue < Pixel.rgbtRed && Pixel.rgbtBlue < Pixel.rgbtGreen) {
		Min = Pixel.rgbtBlue;
	}
}


//функція перетворення масиву пікселів в масив ASCII символів
void Convert(RGBTRIPLE**& Map, char**& ASCII, int Width, int Height) {
	int Hue = 0;    // Змінна для збереження відтінку
	int Max, Min;   // Змінні для збереження максимальної та мінімальної інтинсивності кольору в стрктурі RGBTRIPLE
	int Saturation; // Змінна для збереження насиченості кольору

	// Виділення пам'яті під масив символів ASCII
	ASCII = new char* [Height];
	for (int i = 0; i < Height; i++) {
		ASCII[i] = new char[Width];
	}

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			Max_Min(Map[i][j], Max, Min); //Функція пошуку максимому та мінімуму з структури RGBTRIPLE

			// Змінну Max приймємо за яскравість
			//Якщо яскравість пікселя нульова або максимальна
			//змінюємо значення відповідної комірки масиву та переходимо до наступного пікселя
			if (Max / 50 == 0) { ASCII[i][j] = '@'; continue; }
			if (Max / 50 == 5) { ASCII[i][j] = ' '; continue; }

			//Якщо значення максимальної та мінімальної інтинсивності кольору в стрктурі RGBTRIPLE однакові
			//це означає що піксель чорно білий
			if (Max == Min) {
				ASCII[i][j] = Chars2[(Max / 50) - 2];
				continue;
			}


			//обчислюємо відтінок пікселя
			//залежно від переважной інтенсивності червоного синього або зеленого кольорів у пікселі
			if (Max == Map[i][j].rgbtRed && Map[i][j].rgbtGreen >= Map[i][j].rgbtBlue) {
				Hue = (int)(60 * (Map[i][j].rgbtGreen - Map[i][j].rgbtBlue) / (Max - Min));
			}
			else if (Max == Map[i][j].rgbtRed && Map[i][j].rgbtGreen < Map[i][j].rgbtBlue) {
				Hue = (int)(60 * (Map[i][j].rgbtGreen - Map[i][j].rgbtBlue) / (Max - Min) + 360);
			}
			else if (Max == Map[i][j].rgbtGreen) {
				Hue = (int)(60 * (Map[i][j].rgbtBlue - Map[i][j].rgbtRed) / (Max - Min) + 120);
			}
			else if (Max == Map[i][j].rgbtBlue) {
				Hue = (int)(60 * (Map[i][j].rgbtRed - Map[i][j].rgbtBlue) / (Max - Min));
			}

			Saturation = 100 - (int)(((float)Min / (float)Max) * 100); // обчислюємо насиченість кольору пікселя

			ASCII[i][j] = Chars[(Max / 50) - 2][Hue / 60][Saturation / 33]; // змінюємо значення відповідної комірки масиву
		}
	}
}
