#include <iostream>
using namespace std;

//вывод системы уравнений
void sysout(double** a, double* y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "*x" << j + 1;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	return;
}



double* gauss(double** a, double* y, int n)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001;  //точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		//поиск главного элемента
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		//перестановка строк
		if (max < eps)
		{
			//нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		//нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; //для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; //уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	//обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}
double* gauss2(double** a, double* y, int n) //без выбора главного элемента
{
	double* x;
	int k;
	const double eps = 0.00001;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	double** a, * y, * x;
	int n = 3;// номер по списку + 3. Я 12-й
	a = new double* [n];
	y = new double[n];
	for (int i = 0; i < n; i++)//инициализация матрицы гильберта
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 1.0 / ((i + 1) + (j + 1) - 1.0);
		}
	}
	for (int i = 0; i < n; i++)// Свободный член системы уравнений задайте в виде fi = n/i^2
	{
		y[i] = ((double)n / ((i + 1) * (i + 1)));
	}
	sysout(a, y, n);
	 cout << "\nС выбором" << endl;
	 x = gauss(a, y, n);
	 cout << endl;
	 for (int i = 0; i < n; i++)
		 cout << "x[" << i + 1 << "]=" << x[i] << endl;
	/*cout << "\nБез выбора" << endl;
	x = gauss2(a, y, n);
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "x[" << i + 1 << "]=" << x[i] << endl;*/

	return 0;
}