#include <iostream>
#include <string>  // Служит для работы со строками

using namespace std;  // Указываем пространство имен std

bool isSquareString(string s);

int main() {
  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {
    string s;

    cin >> s;

    if (isSquareString(s)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}

// Функция проверяет, является ли строка квадратной
bool isSquareString(const string s) {
  int len = s.length();

  // Если длина нечётная — не может быть квадратной
  if (len % 2 != 0) {
    return false;
  }

  int half = len / 2;

  // Сравниваем первую половину со второй
  for (int i = 0; i < half; ++i) {
    if (s[i] != s[half + i]) {
      return false;
    }
  }

  return true;
}
