// MT.cpp: определяет точку входа для консольного приложения.
// Var 1 №13

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#pragma comment(lib, "Winmm.lib")

clock_t start;

const unsigned int t1 = 6900;
const unsigned int t2 = 3700;
const unsigned int t3 = 2900;

const unsigned int r1 = 10;
const unsigned int r2 = 35;
const unsigned int r3 = 5000;

int count = 0;

void CALLBACK n_one(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - start) << " ";
	int i, j;

	i = 1 + rand() % 30;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	std::cout << "p1 " << result << '\n';
	++count;
}

void CALLBACK n_three(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - start) << " ";
	int i, j;

	i = 1 + rand() % 50;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	std::cout << "p2 " << result << '\n';
	++count;
}


void CALLBACK n_five(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - start) << " ";
	int i, j;

	i = 1 + rand() % 70;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	std::cout << "p3 " << result << '\n';
	++count;
}



int main()
{
	//Создаем Мультимедийные таймеры(время через которое должен запуститься таймер, точность t+-r, функция, передоваемое значение, один раз запускается || переодически)
	MMRESULT one = timeSetEvent(t1, r1, n_one, 0, TIME_ONESHOT);
	MMRESULT two = timeSetEvent(t2, r2, n_three, 0, TIME_ONESHOT);
	MMRESULT three = timeSetEvent(t3, r3, n_five, 0, TIME_ONESHOT);
	
	
	//Замеряем начальное время
	start = clock();
	
	//Пока count!=3
	while (count != 3);
	//Убиваем таймеры
	timeKillEvent(one);
	timeKillEvent(two);
	timeKillEvent(three);
	return 0;
}

