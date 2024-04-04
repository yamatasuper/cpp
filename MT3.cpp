// MT3.cpp: определяет точку входа для консольного приложения.
// Вариант 9

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <time.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;

const unsigned int t1 = 6600;
const unsigned int t2 = 4200;
const unsigned int t3 = 1800;

const unsigned int r1 = 50;
const unsigned int r2 = 25;
const unsigned int r3 = 200;

const unsigned int z1 = 1;
const unsigned int z2 = 3;
const unsigned int z3 = 4;

const unsigned int n = 9;

const unsigned int iter = 0;

//Масив таймеров
vector<MMRESULT> v1;
//Масив времени
vector<clock_t> ts;

HANDLE hSemaphore;

int count = 0;

//p3
void CALLBACK n_six(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - ts[(int)dwUser]) << " ";
	int i, j;

	i = 1 + rand() % 80;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	cout << "p3 " <<'\n';
}

//p2
void CALLBACK n_tree(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	//От текущего времени отнимаем заемернное и выводим
	std::cout << (clock() - ts[(int)dwUser]) << " ";
	int i, j;

	i = 1 + rand() % 50;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	cout << "p2 " << "  \n";


}

//p1
void CALLBACK n_two(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	srand(time(NULL));

	 //От текущего времени отнимаем заемернное и выводим
	cout << (clock() - ts[(int)dwUser]) << " ";
	int i, j;

	i = 1 + rand() % 40;
	j = GetTickCount();

	while (GetTickCount() - j < i)
	{
	}

	int result = rand() % 5;
	cout << "p1 " << result << '\n';


	switch (result)
	{
	case z1://1
		ts.push_back(clock());
		v1.push_back(timeSetEvent(t2, r2, n_tree, (int)dwUser + 1, TIME_ONESHOT));
		break;
	case z2://3
		ts.push_back(clock());
		v1.push_back(timeSetEvent(t3, r3, n_six, (int)dwUser + 1, TIME_ONESHOT));
		break;
	case z3://4
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return;
	default:
		ts.push_back(clock());
		v1.push_back(timeSetEvent(t1, r1, n_two, (int)dwUser + 1, TIME_ONESHOT));
		return;
	}
	ts.push_back(clock());
	v1.push_back(timeSetEvent(t1, r1, n_two, (int)dwUser + 2, TIME_ONESHOT));
}





int main()
{
	//Создаем семафор
	hSemaphore = CreateSemaphore(NULL, 0, 1,
		NULL); if (hSemaphore == NULL)
		return GetLastError();
	srand(time(NULL));

	//Сохраняем время
	ts.push_back(clock());

	//Создаем Мультимедийные таймеры(время через которое должен запуститься таймер, точность t+-r, функция, передоваемое значение, один раз запускается || переодически)
    //Сохраняем идентификатор таймера
	v1.push_back(timeSetEvent(t1, r1, n_two, iter, TIME_ONESHOT));

	//Ждем
	WaitForSingleObject(hSemaphore,INFINITE);
	for (int i = 0;i < v1.size(); ++i)
	{
		//Убиваем таймеры
		timeKillEvent(v1[i]);
	}
	return 0;
}
