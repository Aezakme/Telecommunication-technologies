#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#define N 15
#define Np 7

// Парсер строки в биты
unsigned long str_to_bits(char* str)
{
    int len = strlen(str);
    unsigned long res = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '1')
            res++;
        res <<= 1;
    }
    res >>= 1;

    return res;
}
//******************************************
//Паресер битов в строки для вывода
char* bits_to_str(unsigned long num, int k)
{
    char* str = new char[k + 1];
    unsigned long mask = (1 << (k - 1));

    for (int i = 0; i < k; i++)
    {
        if (num & mask)
            str[i]='1';
        else
            str[i]='0';
        mask >>= 1;
    }
    str[k]='\0';

    return str;
}
//******************************************
//Деление полиномов
unsigned long DividePolynoms(unsigned long U, int k, unsigned long P, int p)
{
    int mask = (1 << (k + p - 2));

    P <<= (k - 1);

    for (int i = 0; i < k; i++)
    {
        if (U & mask)
            U ^= P;
        mask >>= 1;
        P >>= 1;
    }

    return U;
}
//******************************************
//Сдвиг
unsigned long Shift(unsigned long U, int k, char direction)
{
    unsigned long mask, shift_bit;

    if (direction == 'l')
    {
        mask = (1 << (k - 1));
        shift_bit = (U & mask) ? 1 : 0;
        mask = ((U & mask) << 1);
        U <<= 1;
        U ^= mask;
    }
    else
    {
        mask = 1;
        shift_bit = ((U & mask) << (k - 1));
        U >>= 1;
    }

    return U + shift_bit;
}
//******************************************
//Поиск пораждающей матрицы
unsigned long* FindGenMatrix(unsigned long P, int k, int p)
{
    unsigned long* G = new unsigned long[k];

    for(int i = 0; i < k; i++)
    {
        G[i] = (1 << (k + p - 2 - i));
        G[i] += DividePolynoms(G[i], k, P, p);
    }

    return G;
}
//******************************************
//Вывод матрицы
void PrintMatrix(unsigned long * matrix, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        printf("%s\n", bits_to_str(matrix[i], n));
    }
}
//******************************************
//Поиск максимальной длинны кода
int FindCodeDistance(unsigned long * G, int k, int p)
{
    unsigned long  mask;
    int d = k + p - 1, min;

    for(int i = 0; i < k; i++)
    {
        min = 0;
        mask = 1;
        for (int j = 0; j < k + p - 1; j++)
        {
            if (G[i] & mask)
                min++;
            mask <<= 1;
        }
        if (d > min)
            d = min;
    }

    return d;
}
unsigned long* FindCheckMatrix(unsigned long* G, int k, int p)
{
    unsigned long* H = new unsigned long[p - 1], mask;

    for (int j = 0; j < p - 1; j++)
    {
        H[j] = (1 << (p - 2 - j));
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < p - 1; j++)
        {
            mask = G[i] & (1 << (p - 2 - j));
            mask <<= (k - i + j);
            H[j] ^= mask;
        }
    }

    return H;
}
//******************************************
//Поиск веса кода
int FindWeight(unsigned long num, int k)
{
    int w = 0;
    unsigned long mask = 1;

    for (int i = 0; i < k; i++)
    {
        if (num & mask)
            w++;
        mask <<= 1;
    }

    return w;
}
//******************************************
//Главная функция
int main(int argc, char* argv[])
{
	setlocale(LC_ALL,"russian");
    int lenght_of_U = 0;
    int polynom_lenght = 0;
    int d = 0;
    char err[N+1];
    char Ustr[N-Np+1];
    char Pstr[Np+1];
    unsigned long U;
    unsigned long P;
    unsigned long R;
    unsigned long E;
    unsigned long *G;
    unsigned long *H;

	char choise = '0';

			printf("Введите исходное сообщение:\n");
			scanf("%s", Ustr);
			lenght_of_U = strlen(Ustr);
			U = str_to_bits(Ustr);

			printf("Введите пораждающий полином:\n");
			scanf("%s", Pstr);
			polynom_lenght = strlen(Pstr);
			P = str_to_bits(Pstr);

			U <<= (polynom_lenght - 1);
			R = DividePolynoms(U, lenght_of_U, P, polynom_lenght);
			U += R;
			printf("CRC: %s\n", bits_to_str(U, lenght_of_U + polynom_lenght - 1));

			G = FindGenMatrix(P, lenght_of_U, polynom_lenght);
			printf("Пораждающая матрица: \n");
			PrintMatrix(G, lenght_of_U, lenght_of_U + polynom_lenght - 1);

			H = FindCheckMatrix(G, lenght_of_U, polynom_lenght);
			printf("Проверочная матрица: \n");
			PrintMatrix(H, polynom_lenght - 1, lenght_of_U + polynom_lenght - 1);

			d = FindCodeDistance(G, lenght_of_U, polynom_lenght);
			printf("Наименьшее расстояние: %d\n", d);
			printf("Кодирование может обнаружить ошибки уровня %d, правильный уровень ошибок %d\n", d-1, (d-1)/2);

    getch();
    return 0;
}
