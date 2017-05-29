#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
int sum_gf(int a,int b){
    int sum = a + b;
    sum = sum % 7;
    return sum;
}

int pow_gf(int a, int b){

    int pow_table [7][7]={
        {0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1},
        {1,2,4,1,2,4,1},
        {1,3,2,6,4,5,1},
        {1,4,2,1,4,2,1},
        {1,5,4,6,2,3,1},
        {1,6,1,6,1,6,1}
    };
    return pow_table[a][b];
}

int dev_gf(int a,int b){
    a *=b;
    b *=b;
    int dev =a/(b%7);
    return dev%7;
}



int main() {

	ofstream fout("out.txt");
    int size = 2;
    int input[2] = {3,1};
    int ness_size = 2 *2 + size; // num of errors * 2

    int full_message[ness_size];
    int send_message[ness_size];

    //генерация передаваемого сообщения
    for (int i = 0; i < ness_size; i++) {
        full_message[i]=0;
        send_message[i]=0;
    }
    //закидываем начало сообщения из импута
    for (int i = 0; i < size; i++) {
        full_message[i]=input[i];
    }
    //проверка
    fout << "Take this:";
    for (int i = 0; i < ness_size; i++) {
          fout << full_message[i] << " " ;
    }fout <<" \n";

    //Примитивный элемент
    int Z = 5;

    //Преобразование Фурье
    for (int j = 0; j < ness_size; j++) {
        int temp_sum = full_message[0];
        for (int i = 1; i < ness_size; i++) {
            temp_sum = sum_gf(temp_sum, pow_gf (Z,j)* full_message[i]);// Тут сделать правильное умножение!!!
        }
        send_message[j] = temp_sum;
    }

    //проверка
    fout << "Send this:";
    for (int i = 0; i < ness_size; i++) {
          fout << send_message[i] << " " ;
    }
    fout << "\n" ;

    //Получили сообщение с ошибкой
    // Ошибка= (0,0,0,2,0,6), получим сf(4,1,0,4,5,5).
    int resive_message[6] = {4,1,0,4,5,5} ;



    //Преобразование Фурье
    for (int j = 0; j < ness_size; j++) {
        int temp_sum = resive_message[0];
        fout <<temp_sum<<" ";
        for (int i = 1; i < ness_size; i++) {
            fout << i*j<<"|";
        }
        send_message[j] = dev_gf(temp_sum,6);
        fout <<"\n";
    }
    //проверка
    fout << "Send this:";
    for (int i = 0; i < ness_size; i++) {
          fout << send_message[i] << " " ;
    }

    return 0;
}
