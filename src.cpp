/*	��������� ��� ��������: ���������� � ���������. 
��������� ������� ���� ����� ������������� ��������� ������
� �� ������� ������� Enter ���������� ��������� ��������: 
	� ���������� ������� ������������ � ���, ��� ��������� ������� ����� ������ �������� ������ (�������������); 
	� ��������� ������� �������� ���������� �� ������������ ������ ����������� ��������, 
��������� ���� ������, ���� �������� ����������� ������ / �������� ��������; 
	� ���������� ������� ������� ���������� ������ �� ����� � ���������� ��������� ������� �� �������� ��������� ������; 
	� ��������� ������� ������� ����� ��������� ������ � �.�. � ������ ������ ������������ �������� ������������� ���������. 
����������� ��������� ������ ������������� ����������� ���������. 
���������� ��������� ���������������� �������� ������ �������� �� ����� ��������, 
������ � ������ ������� ������ ���� ��� ��������. 
������ ����������� � ���� ���������: ��� Linux � Windows.*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

using namespace std;

enum ConsoleColor {
Black = 0,
Blue = 1,
Green = 2,
Cyan = 3,
Red = 4,
Magenta = 5,
Brown = 6,
LightGray = 7,
DarkGray = 8,
LightBlue = 9,
LightGreen = 10,
LightCyan = 11,
LightRed = 12,
LightMagenta = 13,
Yellow = 14,
White = 15
};

int main()
{
	STARTUPINFO si;																					
	PROCESS_INFORMATION pi;																		 
																									
	ZeroMemory(&si, sizeof(si));																  
	ZeroMemory(&pi, sizeof(pi));																
																								
	HANDLE channel;
	HANDLE semaphore;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	wchar_t line[] = L"D:\\�����\\cods(C++)\\LAB_3_WIN\\Debug\\dght.exe";

	char str[200];
	char c;
	DWORD cbW;
	
	if(!CreateProcess(NULL, line, 
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
		{
			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << "Error!!!\nProcess was't create!\nExit..." << endl; 
			Sleep(3000);
			
			CloseHandle(pi.hProcess);
			CloseHandle(semaphore);
			CloseHandle(channel);

			return 0; 
		}
	
	semaphore = CreateSemaphore(NULL, 0, 1, L"sem");

	if(!semaphore) 
	{
		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << "Error!\n Semaphore is't created!\nExit..." << endl; 
		Sleep(3000);

		CloseHandle(semaphore);
		CloseHandle(channel);
		CloseHandle(pi.hProcess);

		return 0; 
	}

	channel = CreateNamedPipe(L"\\\\.\\pipe\\new_pipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 512, 512, 5000, NULL);
	
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));cout << "Connect to client..." << endl;

	if(!ConnectNamedPipe(channel, NULL))
	{
		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));cout << "Error!!!\nClient it's not connected!\nExit..." << endl;
		Sleep(3000);

		CloseHandle(channel);
		CloseHandle(semaphore);
		CloseHandle(pi.hProcess);

		return 0;
	}

	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: "; 
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << "Connected done!" << endl;
	
	Sleep(3500);
	
	while(1)
	{
	
		
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << endl << "1 - ";
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << "INPUT SERVER STRING" << endl;
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << endl << "2 - ";
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); 	cout << "CLEAN SCREEN" << endl;
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << endl << "3 - ";
	SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << "EXIT" << endl;
	
	switch( c = getch() )
	{

	case '1':
		
		if(WaitForSingleObject(semaphore, 0) == WAIT_TIMEOUT)
		{

			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << "Input server string: "; 
			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
	
			gets(str);
	
			SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));
	
			if(!WriteFile(channel, str, strlen(str) + 1, &cbW, NULL))
			{
				SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGreen)); cout << endl << "Server: ";
				SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White)); cout << "Error!\n String can't writed to the file!\nExit...";
				Sleep(3000);
				return 0;
			}
			ReleaseSemaphore(semaphore, 1, NULL);
		}

		WaitForSingleObject(semaphore, INFINITE);
		break;
	
	case '2':

		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));
		system("cls");
		break;

	case '3':

		SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));
		
		CloseHandle(pi.hProcess);
		CloseHandle(semaphore);
		CloseHandle(channel);
		CloseHandle(hConsole);
		
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pi.dwProcessId);
		DWORD dwError = ERROR_SUCCESS;

		if(TerminateProcess(hProcess, ((DWORD)-1)) != NULL)
			return 0;
	
	}
	}
	return 0;
}