//______________Made_by_Artem_______________
#include <iostream>
#include <Windows.h>
#include <fstream>

#include "main.h"

using namespace std;

//������� ���������� ���������� �� ������
void read(RGBTRIPLE**& Map, BITMAPFILEHEADER& BFH, BITMAPINFOHEADER& BIH, FILE *f) {
	
	fread(&BFH, sizeof(BITMAPFILEHEADER), 1, f);//���������� ��������� �����
	fread(&BIH, sizeof(BITMAPINFOHEADER), 1, f);//���������� �������������� ���������
	
	int sep = 4 - (BIH.biWidth * 3) % 4; //���������� ������� ���� �� �������� ������
	
	// �������� ���'�� �� ����� ������
	Map = new RGBTRIPLE * [BIH.biHeight]; 
	for (int i = 0; i < BIH.biHeight; i++) {
		Map[i] = new RGBTRIPLE[BIH.biWidth];
	}
	
	// ���������� ���������� � �����
	for (int i = BIH.biHeight - 1; i >= 0; i--) {
		for (int j = 0; j < BIH.biWidth; j++) {
			Map[i][j].rgbtBlue = fgetc(f);
			Map[i][j].rgbtGreen = fgetc(f);
			Map[i][j].rgbtRed = fgetc(f);
		}
		for (int j = 0; j < sep; j ++) fgetc(f); 
	}
}

//������� ��������� � ����
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


//______Made_togeather____
void Print_cmd(char**& ASCII, int Width, int Height){
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			cout << ASCII[i][j] << ASCII[i][j];
		}
		cout << endl;
	}
}
//______Made_togeather____