#include <stdio.h>
#include <iostream>
using namespace std;

#define ROWS 11
#define COLS 11

//Начальное общение с пользователем
void start_print() {
	cout << "Кузнецов Андрей ИКБО-09-21\n";
	cout << "Практическая работа №2 «Двумерный массив»\n";
	cout << "Какой тип массива будем использовать?\n";
	cout << "1 - Static, 2 - Dynamic, 3 - Vector\n";
	cout << "Ввод: ";
}

void print_array(int mas[][COLS]) {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

void zero_array(int mas[][COLS], int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mas[i][j] = 0;
}

int enter_points_coords(int mas[][COLS], int n) {
	int x = 0, y = 0;
	int bot_x = -(ROWS - 1) / 2;
	int bot_y = -(COLS - 1) / 2;
	int high_x = (ROWS - 1) / 2;
	int high_y = (COLS - 1) / 2;

	for (int i = 1; i <= n; i++)
	{
		cout << "Введите координаты " << i << "й точки (x,y): ";
		do {
			if (x < bot_x or x > high_x or y < bot_y or y > high_y) {
				cout << "Выход за пределы координатной плоскости." << endl;
				cout << "Введите ещё раз (" << bot_x << " <= x <= " << high_x;
				cout << ", " << bot_y << " <= y <= " << high_y << ") : ";
			}
			cin >> x >> y;
		} while (x < bot_x or x > high_x or y < bot_y or y > high_y);
		if (mas[(ROWS - 1) / 2 - y][(COLS - 1) / 2 + x] == 1) {
			cout << "Точка с такими координатами уже существует." << endl;
			i--;
		}
		else {
			mas[(ROWS - 1) / 2 - y][(COLS - 1) / 2 + x] = 1;
		}
	}
	return 0;
}

double max_dist(int mas[][COLS]) {
	int last_slot = ROWS * COLS;
	double max_d = -1;
	int x, y;
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (mas[i][j] == 1)
			{
				for (int m = i; m < COLS; m++)
				{
					for (int k = 0; k < ROWS; k++)
					{
						if (mas[m][k] == 1) {
							double dist = sqrt(pow(double(m - i), 2.0) + pow(double(k - j), 2.0));
							if (max_d < dist)
								max_d = dist;
						}
					}
				}
			}
		}
	}
	return (round(max_d * 1000) / 1000);
}

void static_mas() {
	int static_mas[ROWS][COLS];
	int n_points;
	zero_array(static_mas, ROWS, COLS);
	cout << "Сколько точек будет находиться на координатной плоскости?\n";
	cout << "(Не больше 100)\n";
	cout << "Ввод: ";
	cin >> n_points;
	enter_points_coords(static_mas, n_points);
	//print_array(static_mas);
	cout << "Максимальное расстояние между заданными точками равно: ";
	cout << max_dist(static_mas);
}

void create_dynamic_array(int**& mas) {
	mas = new int* [COLS];
	for (int i = 0; i < COLS; i++)
	{
		mas[i] = new int[ROWS];
	}
}

void zero_dynamic_array(int**& mas) {
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			mas[i][j] = 0;
}

void print_dynamic_array(int** mas) {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

void dynamic_mas() {
	int** dynamic_mas;
	create_dynamic_array(dynamic_mas);
	zero_dynamic_array(dynamic_mas);
	print_dynamic_array(dynamic_mas);
}

int main()
{
	setlocale(0, "russian");
	int menu;
	start_print();
	do {
		cin >> menu;
		switch (menu)
		{
		case 1:
			static_mas();
			break;
		case 2:
			dynamic_mas();
		default:
			break;
		}

	} while (menu != 0);
}