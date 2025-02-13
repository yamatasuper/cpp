// MT2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Вариант 7

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#pragma comment(lib, "Winmm.lib")

const unsigned int t1 = 7100;
const unsigned int t2 = 3300;

const unsigned int r1 = 35;
const unsigned int r2 = 5;

const unsigned int n = 9;

//Массив таймеров
MMRESULT mr[n];
//Время p1
clock_t tf[n];
//Время p2
clock_t ts[n];


HANDLE hSemaphore;

void CALLBACK n_six(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << "\t"<< (clock() - ts[(int)dwUser]) << " ";
	int i, j;

	i = 1 + rand() % 80;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	std::cout << "p2 " << result << '\n';
	//Если запускается 9 раз сигнализируем
	if(8 == (int)dwUser)
		ReleaseSemaphore(hSemaphore, 1, NULL);
}



void CALLBACK n_one(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - tf[(int)dwUser]) << " ";
	int i, j;

	i = 1 + rand() % 30;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	std::cout << "p1 " << result;
	//Создаем Мультимедийные таймеры(время через которое должен запуститься таймер, точность t+-r, функция, передоваемое значение, один раз запускается || переодически)
	MMRESULT one = timeSetEvent(t2, r2, n_six, (int)dwUser, TIME_ONESHOT);
	//Сохраняем время p2
	ts[(int)dwUser] = clock();
}





int main()
{
	//Создаем семафор
	hSemaphore = CreateSemaphore(NULL, 0, 1,
		NULL); if (hSemaphore == NULL)
		return GetLastError();

	bool flag = 1;
	for (int i = 0; i < n; ++i)
	{
		//Создаем Мультимедийные таймеры(время через которое должен запуститься таймер, точность t+-r, функция, передоваемое значение, один раз запускается || переодически)
		//Сохраняем идентификатор таймера
		mr[i] = timeSetEvent(t1, r1, n_one, i, TIME_ONESHOT);
		//Сохраняем время p1
		tf[i] = clock();
		//Ждем
		Sleep(t1);
	}
	//Ждем когда таймер запустится 9 раз
	WaitForSingleObject(hSemaphore, INFINITE);

	//Уничтожаем таймер
	for (int i = 0; i < n; ++i)
	{
		timeKillEvent(mr[i]);
	}
	return 0;
}