#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#define ROWS 11
#define COLS 11

//Задание: Дано множество точек на плоскости, точки заданы своими координатами.
//Найти наибольшее расстояние между этими точками.

//Начальное общение с пользователем
void start_print() {
	cout << "Кузнецов Андрей ИКБО-09-21\n";
	cout << "Практическая работа №2 «Двумерный массив»\n";
	cout << "Программа считает наибольшее расстояние между точками на плоскости.";
	cout << "Какой тип массива будем использовать?\n";
	cout << "1 - Static, 2 - Dynamic, 3 - Vector\n";
	cout << "Ввод: ";
}

//Вывод статического двумерного массива
void print_static_array(int mas[][COLS]) {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

//Зануление статического двумерного массива
void zero_static_array(int mas[][COLS], int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mas[i][j] = 0;
}

//Размещение точек на координатную плоскость по их координатам
int enter_points_coords_static(int mas[][COLS], int n) {
	int x = 0, y = 0;

	//задаем границы статической координатной плоскости
	int bot_x = -(ROWS - 1) / 2;
	int bot_y = -(COLS - 1) / 2;
	int high_x = (ROWS - 1) / 2;
	int high_y = (COLS - 1) / 2;

	for (int i = 1; i <= n; i++)
	{
		cout << "Введите координаты " << i << "й точки (x,y): ";
		do {
			//проверка на выход за границы коррдинатной плоскости
			if (x < bot_x or x > high_x or y < bot_y or y > high_y) {
				cout << "Выход за пределы координатной плоскости." << endl;
				cout << "Введите ещё раз (" << bot_x << " <= x <= " << high_x;
				cout << ", " << bot_y << " <= y <= " << high_y << ") :";
			}
			cin >> x >> y;
		} while (x < bot_x or x > high_x or y < bot_y or y > high_y);
		//проверка на уже существующую точку
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

//нахождение наибольшего расстояния между точками в статическом одномерном массиве
double max_dist_static(int mas[][COLS]) {
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
							double dist = 
								sqrt(pow(double(m - i), 2.0) + pow(double(k - j), 2.0));
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

//ввод количества точек
int enter_n_points() {
	int n;
	cout << "Сколько точек будет находиться на координатной плоскости?\n";
	cout << "(Не больше 100)\n";
	cout << "Ввод: ";
	cin >> n;
	return n;
}

//основной код для работы со статическим массивом
void static_mas() {
	int static_mas[ROWS][COLS];
	int n_points;
	n_points = enter_n_points();
	zero_static_array(static_mas, ROWS, COLS);
	enter_points_coords_static(static_mas, n_points);
	cout << "Получившаяся координатная плоскость:\n";
	print_static_array(static_mas);
	cout << "Максимальное расстояние между заданными точками равно: ";
	cout << max_dist_static(static_mas);
}

//создание динамического двумерного массива (координатной плоскости)
void create_dynamic_array(int**& mas, int n, int m) {
	mas = new int* [m];
	for (int i = 0; i < m; i++)
	{
		mas[i] = new int[n];
	}
}

//зануление динамического двумерного массива
void zero_dynamic_array(int**& mas, int n, int m) {
	for (int i = 0; i < (n*2+1); i++)
		for (int j = 0; j < (m*2+1); j++)
			if (mas[i][j]!=1)
				mas[i][j] = 0;
}

//вывод динамического двумерного массива
void print_dynamic_array(int** mas, int n, int m) {
	for (int i = 0; i < (n*2+1); i++) {
		for (int j = 0; j < (m*2+1); j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

//Размещение точек на координатную плоскость по их координатам
//в двумерном динамическом массиве
int enter_points_coords_dynamic(int**& mas, int n_points, int& n, int& m, int**& newMas) {
	int x = 0;
	int y = 0;

	for (int i = 1; i <= n_points; i++)
	{
		cout << "Введите координаты " << i << "й точки (x,y): ";
		cin >> x >> y;
		//в случае выхода точки за границы координатной плоскости
		//создание нового расширенного двумерного динамического массива и его зануление
		//копирует точки из старого двумерного массива в новый
		if (abs(x)>n or abs(y)>m) {
			
			//в случае выхода по оси абцисс
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

			//в случае выхода по оси ординат
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

		//проверка на существующую точку
		if (mas[m - y][n + x] == 1) {
			cout << "Точка с такими координатами уже существует." << endl;
			i--;
		}
		else
			mas[m - y][n + x] = 1;
	}
	return 0;
}

//нахождение наибольшего расстояния между точками в динамическом двумерном массиве
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

//основной код для работы с динамическим двумерным массивом
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
	cout << "Получившаяся координатная плоскость:\n";
	print_dynamic_array(dynamic_mas, n, m);
	cout << "Максимальное расстояние между заданными точками равно: ";
	cout << max_dist_dynamic(dynamic_mas, n*2+1, m*2+1);
}

int zero_vector_mas(vector < vector <int> >& mas, int n, int m) {
	for (int i = 0; i < n; i++)     // Цикл, который идёт по строкам
		for (int j = 0; j < m; j++) // Цикл, который идёт по элементам
		{
			mas[i][j] = 0;
		}
	return 0;
}

void print_vector_mas(vector < vector <int> >& mas, int n, int m) {
	for (int i = 0; i < n; i++) // Цикл, который идёт по строкам
	{
		for (int j = 0; j < m; j++) // Цикл, который идёт по элементам
			cout << mas[i][j] << ' '; // Вывод элементов i строки вектора
		cout << endl;
	}
}

int enter_points_coords_vector(vector < vector <int> >& mas, int n_points, int& n, int& m) {
	int x = 0;
	int y = 0;


	for (int i = 1; i <= n_points; i++)
	{
		cout << "Введите координаты " << i << "й точки (x,y): ";
		cin >> x >> y;

		//в случае выхода точки за границы координатной плоскости
		//создание нового расширенного двумерного динамического массива и его зануление
		//копирует точки из старого двумерного массива в новый
		if (abs(x) > ((n-1)/2.0) or abs(y) > ((m - 1) / 2.0)) {
			
			
			//в случае выхода по оси абцисс
			if (abs(x) > (n-1)/2.0) {
				vector < vector <int> > vector_new_mas((abs(x) * 2 + 1), vector <int>(abs(x) * 2 + 1));
				zero_vector_mas(vector_new_mas, abs(x) * 2 + 1, abs(x) * 2 + 1);
				//print_vector_mas(vector_new_mas, (abs(x) * 2 + 1), (abs(x) * 2 + 1));
				for (int k = 0; k < n; k++)
				{
					for (int r = 0; r < m; r++)
					{
						vector_new_mas[k + abs(x) - (n-1)/2.0][r + abs(x) - (n - 1) / 2.0] = mas[k][r];
					}
				}
				n = abs(x) * 2 + 1;
				m = abs(x) * 2 + 1;
				mas = vector_new_mas;
			}

			if (abs(y) > (m - 1) / 2.0) {
				vector < vector <int> > vector_new_mas((abs(y) * 2 + 1), vector <int>(abs(y) * 2 + 1));
				zero_vector_mas(vector_new_mas, abs(y) * 2 + 1, abs(y) * 2 + 1);
				//print_vector_mas(vector_new_mas, (abs(y) * 2 + 1), (abs(y) * 2 + 1));
				for (int k = 0; k < n; k++)
				{
					for (int r = 0; r < m; r++)
					{
						vector_new_mas[k + abs(y) - (n - 1) / 2.0][r + abs(y) - (n - 1) / 2.0] = mas[k][r];
					}
				}
				n = abs(y) * 2 + 1;
				m = abs(y) * 2 + 1;
				mas = vector_new_mas;
			}
		}

		//проверка на существующую точку
		if (mas[(m - 1) / 2.0 - y][(n - 1) / 2.0 + x] == 1) {
			cout << "Точка с такими координатами уже существует." << endl;
			i--;
		}
		else
			mas[(m-1)/2.0 - y][(n-1)/2.0 + x] = 1;
	}
	return 0;
}

void kvadrat(vector < vector <int> >& vector_mas,int n,int m) {
	int sum = 0;
	int max_sum = 0;
	int max_coord_1x = 0;
	int max_coord_1y = 0;
	int max_coord_2x = 0;
	int max_coord_2y = 0;
	int max_coord_3x = 0;
	int max_coord_3y = 0;
	int max_coord_4x = 0;
	int max_coord_4y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (vector_mas[i][j] == 1) {
				for (int p = j + 1; p < m; p++)
				{
					if ((i + p - j) <= n)
					{
						if (vector_mas[i][p] == 1 and vector_mas[i + p - j][j] == 1 and vector_mas[i + p - j][p] == 1) {
							for (int r = i + 1; r < i + p - j; r++)
							{
								for (int v = j + 1; v < p; v++)
								{
									if (vector_mas[r][v] == 1)
									{
										sum += 1;
									}
								}
							}
							if (max_sum < sum)
							{
								max_sum = sum;
								max_coord_1x = j - ((m - 1) / 2.0);
								max_coord_1y = ((n - 1) / 2.0) - i;
								max_coord_2x = p - ((m - 1) / 2.0);
								max_coord_2y = ((n - 1) / 2.0) - i;
								max_coord_3x = j - ((m - 1) / 2.0);
								max_coord_3y = ((n - 1) / 2.0) - (i + p - j);
								max_coord_4x = p - ((m - 1) / 2.0);
								max_coord_4y = ((n - 1) / 2.0) - (i + p - j);
							}
							sum = 0;
						}
					}
				}
			}

		}
	}
	if (max_coord_1x == 0 and
		max_coord_1y == 0 and
		max_coord_2x == 0 and
		max_coord_2y == 0 and
		max_coord_3x == 0 and
		max_coord_3y == 0 and
		max_coord_4x == 0 and
		max_coord_4y == 0)
	{
		cout << "Не существует такого квадрата, внутри которого была хотябы 1 точка";
	}
	else {
		cout << "Квадрат с наибольшим количеством точек (" << max_sum << ") имеет координаты : \n" <<
			"(" << max_coord_1x << "," << max_coord_1y << ");" <<
			"(" << max_coord_2x << "," << max_coord_2y << ");" <<
			"(" << max_coord_3x << "," << max_coord_3y << ");" <<
			"(" << max_coord_4x << "," << max_coord_4y << ")\n";
	}
}


//Задано множество точек на плоскости. Найти все четверки точек, являющихся вершинами квадратов. 
//Найти квадрат, внутри которого лежит наибольшее количество точек множества.
void vector_mas() {
	int n = ROWS;
	int m = COLS;
	int n_points;
	vector < vector <int> > vector_mas(n, vector <int>(m)); // Объявление вектора на n строк по m элементов 
	zero_vector_mas(vector_mas, n, m);
	n_points = enter_n_points();
	enter_points_coords_vector(vector_mas, n_points, n, m);
	cout << "Получившаяся координатная плоскость:\n";
	print_vector_mas(vector_mas, n, m);
	kvadrat(vector_mas, n, m);
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
			break;
		case 3:
			vector_mas();
		default:
			break;
		}

	} while (menu != 0);
}