#include <iostream>

using namespace std;

/*
  Задача: Вывести на экран все простые числа не превышающие число N.
  Ввод: Целое положительное число N.
  Завершение: Автоматически после ввода числа N.
  Вывод: Список простых чисел не превышающие число N.
*/

int main()
{
    int N;
    cout << "Enter number N: ";
    cin >> N;

    int dozens = 10;

    if (N >= 2) cout << "2 ";

    for (int i = 3; i <= N; i += 2)
    {
        bool prime = true;
        for (int j = 3; prime && (j * j <= i); j += 2 )
        {
            prime = (i % j) == 0;
        }

        if (prime)
        {
            if (i > dozens)
            {
                cout << endl;
            }

            cout << i << " ";
            dozens = ((i / 10 + 1) * 10);
        }
    }
}