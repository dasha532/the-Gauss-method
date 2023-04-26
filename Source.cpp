#include <iostream>
using namespace std;
void print_s(double** a, double* y, int n);
double* gauss(double** a, double* y, int n);

int main()
{
    double** a, * y, * x;
    double* c;
    int n, b;
    cout << "Enter 0 - if you want to solve your system and 1 - if random system" << endl;
    cin >> b;
    if (b == 1)
    {
        cout << "Enter the number of equations: ";
        cin >> n;
        a = new double* [n];
        y = new double[n];
        c = new double[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new double[n];
            for (int j = 0; j < n; j++)
            {

                a[i][j] = rand() % 21 - 10;
            }
        }
        for (int i = 0; i < n; i++)
            c[i] = i + 1+ 0.1;
        double k = 0.0, b = 0.0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                k = a[i][j] * c[j];
                b = b + k;
            }
            y[i] = b;
            b = 0.0;
        }
        x = gauss(a, y, n);
        for (int i = 0; i < n; i++)
            cout << x[i] << "   ";
        double m = 0.0, l = 0.0;
        double r = 0.0;
        for(int i = 0; i < n; i++)
        {
            l = l + i + 1;
        }
        l = l / n;
        cout <<"l = "<< l << endl;
        for (int i = 0; i < n; i++)
        {
            m = abs(x[i] - (i+1));
           // cout << m << endl;
            r = r + m;
            m = 0;
        }
        r = r / n;
        cout <<"r= "<< r << endl;
        r = r/l * 100;
        cout << "Pogresnnost: " << r;
    }
    else
    {
        cout << "Enter the number of equations: ";
        cin >> n;
        a = new double* [n];
        y = new double[n];
        cout << "Enter the index matrix";
        for (int i = 0; i < n; i++)
        {
            a[i] = new double[n];
            for (int j = 0; j < n; j++)
            {
                cout << "X" << "[" << i << "]" << "[" << j << "] = ";
                cin >> a[i][j];
            }
        }
        cout << "Enter right coloumn";
        for (int i = 0; i < n; i++)
        {
            cout << "X" << "[" << i << "] = ";
            cin >> y[i];
        }
        print_s(a, y, n);
        x = gauss(a, y, n);
        for (int i = 0; i < n; i++)
            cout << "x[" << i << "]=" << x[i] << endl;
    }
    return 0;
}
void print_s(double** a, double* y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
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
    const double eps = 0.0001;
    x = new double[n];
    k = 0;
    while (k < n)
    {
        max = abs(a[k][k]); // Поиск макс
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        for (int j = 0; j < n; j++)// Перестановка строк
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--) // обратный метод
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}