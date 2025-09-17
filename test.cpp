#include <iostream>
#include <string> // Служит для работы со строками
#include <fstream> // Служит для работы с файлами
#include <clocale>//Обработка кириллицы

using namespace std; // Указываем пространство имен std

void test ();

int main()
{

	// Установка поддержки кириллицы
	setlocale(LC_CTYPE, "rus");


	//Работа с консолью

	int a=0;

	cout << "a:"<< endl;
	cout << a << endl;
	cin >> a;
	cout << a<< endl;

	//Работа со статическими массивами

	int b[4]={1, 2, 3, 4};

	b[4]=10;

	cout << b[4] << endl;

	//Динамические массивы

	int *nums= new int[3];

	nums[0]=1;
	cout << "dinamic array first element:" << nums[0] << endl;

	delete[] nums;


	//Работа со строками:

	string test_string="test string instance";

	cout << test_string << endl;

	cin >> test_string;

	cout << test_string << endl;


	//Использование ссылок

	int c=10;

	int &d=c;//Записываем адрес переменной

	cout << &c << "-" << c  << endl;//до изменения
	cout << &d << "-" << d  << endl;//до изменения

	d=5;

	cout << &c << "-" << c  << endl;//после изменения
	cout << &d << "-" << d  << endl;//после изменения

	//Использование указателей

	int t = 237; // Простая переменная
	int *p; // Создание указателя, который принимает лишь адрес другой переменной

	p = &t; // Устанавливаем адрес нашей первой переменной


	//std::cin.get();//Программа ожидает ввода символа для завершения
	return 0;
}

void test () {
	cout << "Вывод чего-либо в консоль" << endl;
}


