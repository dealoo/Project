#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#ifndef HEADER_H
#define HEADER_H

#endif HEADER_H


using namespace std;

void CLSconsol() {// Konsolu emeliyat sistemine gore temizleme 
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void PrintColor(string text, int colorCode, bool n = 0) { //rengli yazi yazma
	if (n) {
		cout << "\033[1;" << colorCode << "m" << text << "\033[0m" << endl;
	}
	else {
		cout << "\033[1;" << colorCode << "m" << text << "\033[0m";
	}
}

void PrintMSG(string text, int color = 1) {
	int size = text.size();
	cout << "\n";
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t k = 0; k < 5; k++)
		{
			cout << "      ";
		}
		PrintColor("|", 41, 0);
		if (i != 1) {
			for (size_t i = 0; i < 5; i++)
			{
				cout << "-------";
			}
			PrintColor("|", 41, 1);
		}
		else {
			int center = (35 - size) / 2;
			for (size_t i = 0; i < 35; i++)
			{
				if (i <= center || i >= (35 - center)) {
					cout << "-";
				}
				else {
					PrintColor(text, color, 0);
					i += (size - 1);
				}
			}
			PrintColor("|", 41, 1);
		}
	}
}

void PrintCanter(string text, bool n = 0, int size = 20) {
	int Size = size / 5;
	for (size_t i = 0; i < Size; i++)
	{
		cout << "     ";
	}
	if (n) {
		cout << text;
	}
	else {
		cout << text << endl;
	}
}

bool HasSharp(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '#') {
			return true;
		}
	}
	return false;
}

void EnterExit() {
	int n;
	cout << "[1] Exit \nEnter Index: ";
	cin >> n;
}
