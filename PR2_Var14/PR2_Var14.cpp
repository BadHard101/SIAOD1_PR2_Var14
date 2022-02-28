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

int enter_n_points() {
	int n;
	cout << "Сколько точек будет находиться на координатной плоскости?\n";
	cout << "(Не больше 100)\n";
	cout << "Ввод: ";
	cin >> n;
	return n;
}

void static_mas() {
	int static_mas[ROWS][COLS];
	int n_points;
	n_points = enter_n_points();
	zero_array(static_mas, ROWS, COLS);
	enter_points_coords(static_mas, n_points);
	//print_array(static_mas);
	cout << "Максимальное расстояние между заданными точками равно: ";
	cout << max_dist(static_mas);
}

void create_dynamic_array(int**& mas, int n, int m) {
	mas = new int* [m];
	for (int i = 0; i < m; i++)
	{
		mas[i] = new int[n];
	}
}

void zero_dynamic_array(int**& mas, int n, int m) {
	for (int i = 0; i < (n*2+1); i++)
		for (int j = 0; j < (m*2+1); j++)
			if (mas[i][j]!=1)
				mas[i][j] = 0;
}

void print_dynamic_array(int** mas, int n, int m) {
	for (int i = 0; i < (n*2+1); i++) {
		for (int j = 0; j < (m*2+1); j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

int enter_points_coords_dynamic(int**& mas, int n_points, int& n, int& m, int**& newMas) {
	int x = 0;
	int y = 0;

	for (int i = 1; i <= n_points; i++)
	{
		cout << "Введите координаты " << i << "й точки (x,y): ";
		cin >> x >> y;
		if (abs(x)>n or abs(y)>m) {
			if (abs(x) > n) {
				/*newMas = (int**)realloc(newMas, (x * 2 + 1) * sizeof(int*));
				for (int i = 0; i < (x * 2 + 1); i++)
					newMas[i] = (int*)malloc((x * 2 + 1) * sizeof(int));*/
				create_dynamic_array(newMas, abs(x) * 2 + 1, abs(x) * 2 + 1);
				zero_dynamic_array(newMas, abs(x), abs(x));
				for (int k = 0; k < (n*2+1); k++)
				{
					for (int r = 0; r < (m*2+1); r++)
					{
						newMas[k + abs(x) - n][r + abs(x) - n] = mas[k][r];
					}
				}
				n = abs(x);
				m = abs(x);
				mas = newMas;
			}
			if (abs(y) > m) {
				/*newMas = (int**)realloc(newMas, (y * 2 + 1) * sizeof(int*));
				for (int i = 0; i < (y * 2 + 1); i++)
					newMas[i] = (int*)malloc((y * 2 + 1) * sizeof(int));*/
				create_dynamic_array(newMas, abs(y) * 2 + 1, abs(y) * 2 + 1);
				zero_dynamic_array(newMas, abs(y), abs(y));
				for (int k = 0; k < (n*2+1); k++)
				{
					for (int r = 0; r < (m*2+1); r++)
					{
						newMas[k + abs(y) - n][r + abs(y) - n] = mas[k][r];
					}
				}
				n = abs(y);
				m = abs(y);
				mas = newMas;
			}
			
			
		}

		if (mas[m - y][n + x] == 1) {
			cout << "Точка с такими координатами уже существует." << endl;
			i--;
		}
		else
			mas[m - y][n + x] = 1;
	}
	return 0;
}

double max_dist_dynamic(int** mas, int n, int m) {
	double max_d = -1;
	int x, y;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mas[i][j] == 1)
			{
				for (int p = i; p < m; p++)
				{
					for (int k = 0; k < n; k++)
					{
						if (mas[p][k] == 1) {
							double dist = sqrt(pow(double(p - i), 2.0) + pow(double(k - j), 2.0));
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


void dynamic_mas() {
	int** dynamic_mas;
	int** newMas;
	int n_points;
	int n = (ROWS-1)/2;
	int m = (COLS-1)/2;
	create_dynamic_array(dynamic_mas, ROWS, COLS);
	zero_dynamic_array(dynamic_mas,n,m);
	n_points = enter_n_points();
	//print_dynamic_array(dynamic_mas, n, m);
	enter_points_coords_dynamic(dynamic_mas, n_points, n, m, newMas);
	//print_dynamic_array(dynamic_mas, n, m);
	cout << "Максимальное расстояние между заданными точками равно: ";
	cout << max_dist_dynamic(dynamic_mas, n*2+1, m*2+1);
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