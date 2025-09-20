#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;  // дерево отрезков: хранит количество нулей
    vector<int> arr;   // исходный массив
    int n;             // размер массива

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = (arr[tl] == 0) ? 1 : 0;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            arr[pos] = val;
            tree[v] = (val == 0) ? 1 : 0;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))
             + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    int findKthZero(int v, int tl, int tr, int k) {
        if (k > tree[v]) // если k-го нуля не существует
          return -1;
        if (tl == tr)
          return tl; // нашли лист — это и есть позиция k-го нуля
        int tm = (tl + tr) / 2;
        if (tree[v*2] >= k) {
          // k-й ноль находится в левой половине
          return findKthZero(v*2, tl, tm, k);
        } else {
          // иначе — в правой, вычитаем количество нулей слева
          return findKthZero(v*2+1, tm+1, tr, k - tree[v*2]);
        }
      }

public:
    SegmentTree(vector<int>& input) : arr(input), n(input.size()) {
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    int findKthZero(int k) {
        return findKthZero(1, 0, n - 1, k);
    }

    void printTree() {
        cout << "Tree: ";
        for (int i = 1; i < 4 * n && i < (int)tree.size(); ++i) {
            cout << tree[i] << " ";
        }
        cout << endl;
    }

    void printArray() {
        cout << "Массив: ";
        for (int i = 0; i < n; ++i) {
          cout << arr[i];
          if (i < n - 1) cout << " ";
        }
        cout << endl;
      }

};

int main() {
    SetConsoleOutputCP(CP_UTF8); // Для корректного вывода кириллицы в Windows

    int N;
    cin >> N;

    vector<int> inputArray(N);
    for (int i = 0; i < N; ++i) {
      cin >> inputArray[i];
    }

    //vector<int> a = {0, 1, 0, 2, 0, 3, 0, 4}; - пример входного массива
    // 0 1 0 2 0 3 0 4 - запись в консоли (8 элементов)
    SegmentTree segmentTree(inputArray);

    cout << "Исходное количество нулей на [0, 7]: " << segmentTree.query(0, 7) << endl;
    cout << "Количество нулей на [2, 5]: " << segmentTree.query(2, 5) << endl;

    segmentTree.update(2, 5);
    cout << "После update(2, 5): нулей на [0,7]: " << segmentTree.query(0, 7) << endl;

    segmentTree.update(3, 0);
    cout << "После update(3, 0): нулей на [0,7]: " << segmentTree.query(0, 7) << endl;

    cout << "Текущее состояние массива: ";
    segmentTree.printArray();  // <-- наш новый метод

    // 👇 НОВОЕ: поиск k-го нуля
    cout << "\n=== Поиск k-го нуля ===" << endl;
    for (int k = 1; k <= segmentTree.query(0, 7); ++k) {
      int idx = segmentTree.findKthZero(k);
      cout << k << "-й ноль находится по индексу: " << idx
           << " (значение: " << inputArray[idx] << ")" << endl;
    }

    // Попробуем найти несуществующий
    int k = 10;
    int idx = segmentTree.findKthZero(k);
    if (idx == -1) {
      cout << "\n" << k << "-й ноль не существует." << endl;
    }

    cout << "\n=== Состояние дерева отрезков (tree[1..]) ===" << endl;
    segmentTree.printTree();

    return 0;
}







