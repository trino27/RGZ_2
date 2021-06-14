#pragma warning(disable : 4996)

#include <iostream>
#include <Windows.h>
#include "main.h"


using namespace std;

int main() {
	setlocale(LC_ALL, "Ukrainian");
	BITMAPFILEHEADER FHeader;
	BITMAPINFOHEADER IHeader;
	RGBTRIPLE** Map;
	
	short key = -1;
	while (key)
	{
		char file_name[255];
		cout << "Введите путь к картинке: ";
		cin.getline(file_name, 255, '\n');

		FILE* f = fopen(file_name, "rb");
		if (!file_name)
		{
			cout << "Не удается открыть файл. (Или файл не существует.)\n" << endl;
			exit(1);
		}
		else cout << "Успех!\n";

		read(Map, FHeader, IHeader, f);

		char** ASCII;

		Convert(Map, ASCII, IHeader.biWidth, IHeader.biHeight);

		cout << "1 - вывод в фаил" << endl;
		cout << "2 - вывод в консоль" << endl;
		cout << "3 - сброс" << endl;
		cout << "0 - завершение программы" << endl;
		cout << "->";
		cin >> key;
		if (key == 1) Print(ASCII, IHeader.biWidth, IHeader.biHeight);
		if (key == 2) Print_cmd(ASCII, IHeader.biWidth, IHeader.biHeight);
	}

	return 0;
}