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

  int findKthZeroInRangeImpl(int v, int tl, int tr, int l, int r, int k) {
      if (k <= 0 || tl > r || tr < l) return -1; // отрезки не пересекаются
      if (tl == tr) {
        if (tree[v] > 0 && k == 1 && l <= tl && tl <= r) {
          return tl;
        }
        return -1;
      }

      int tm = (tl + tr) / 2;

      // Считаем, сколько нулей в левом ребёнке НА ПЕРЕСЕЧЕНИИ с [l, r]
      int left_count = 0;
      if (!(l > tm || r < tl)) { // если есть пересечение с левой половиной
        left_count = (l <= tl && tm <= r) ? tree[v*2] : query(v*2, tl, tm, max(l, tl), min(r, tm));
      }

      if (left_count >= k) {
        return findKthZeroInRangeImpl(v*2, tl, tm, l, r, k);
      } else {
        return findKthZeroInRangeImpl(v*2+1, tm+1, tr, l, r, k - left_count);
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

    int findKthZeroInRange(int l, int r, int k) {
      return findKthZeroInRangeImpl(1, 0, n - 1, l, r, k);
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

    //Оптимизация работы с консолью
    ios::sync_with_stdio(false);
    cin.tie(0);


    //int N;
    //cin >> N;

    // vector<int> inputArray(N);
    // for (int i = 0; i < N; ++i) {
    //   cin >> inputArray[i];
    // }


    int N=5;

    vector<int> inputArray={0, 0, 3, 0, 2};


    SegmentTree segmentTree(inputArray);

    // int M;
    // cin >> M;
    //
    // char type;
    //
    // for (int i = 0; i < M; ++i) {
    //   cin >> type;
    //   if (type == 's') {
    //     int l, r, k;
    //     cin >> l >> r >> k;
    //     // Если индексы вводятся 1-based — раскомментируй:
    //     // l--; r--;
    //     int idx = segmentTree.findKthZeroInRange(l, r, k);
    //     cout << idx << "\n";
    //   } else if (type == 'u') {
    //     int pos, val;
    //     cin >> pos >> val;
    //     // Если позиция 1-based — раскомментируй:
    //     // pos--;
    //     segmentTree.update(pos, val);
    //   }
    // }

    //vector<int> a = {0, 1, 0, 2, 0, 3, 0, 4}; - пример входного массива
    //0 1 0 2 0 3 0 4 - запись в консоли (8 элементов)

    cout << "Исходное количество нулей на [0, 4]: " << segmentTree.query(0, 4) << endl;

    cout << "Количество нулей на [2, 4]: " << segmentTree.query(2, 4) << endl; // было [2,5] → исправлено

    segmentTree.update(2, 5); // меняем a[2] с 3 на 5 → не влияет на нули
    cout << "После update(2, 5): нулей на [0,4]: " << segmentTree.query(0, 4) << endl;

    segmentTree.update(3, 0); // меняем a[3] с 0 на 0 → ничего не изменилось (но обновление прошло)
    cout << "После update(3, 0): нулей на [0,4]: " << segmentTree.query(0, 4) << endl;

    cout << "Текущее состояние массива: ";
    segmentTree.printArray();  // <-- наш новый метод

    cout << "\n=== Поиск k-го нуля НА ОТРЕЗКЕ ===" << endl;

    // Тестируем различные запросы
    // vector<tuple<int, int, int>> testQueries = {
    //   {0, 4, 1}, // 1-й ноль на [0,4]
    //   {0, 4, 2}, // 2-й ноль на [0,4]
    //   {0, 4, 3}, // 3-й ноль на [0,4]
    //   {0, 4, 4}, // 4-й — не существует
    //   {2, 4, 1}, // 1-й ноль на [2,4] → индекс 3
    //   {2, 4, 2}, // 2-го нет
    //   {0, 1, 1}, // 1-й ноль на [0,1] → 0
    //   {0, 1, 2}, // 2-й → 1
    //   {0, 1, 3}, // 3-го нет
    // };

    // for (auto [l, r, k] : testQueries) {
    //   int idx = segmentTree.findKthZeroInRange(l, r, k);
    //   cout << "findKthZeroInRange(" << l << ", " << r << ", " << k << ") = " << idx;
    //   if (idx != -1) {
    //     //cout << " (значение: " << segmentTree.arr[idx] << ")";
    //   }
    //   cout << endl;
    // }

    int idx = segmentTree.findKthZeroInRange(2, 4, 1);
    cout << "findKthZeroInRange(" << 2 << ", " << 4 << ", " << 1 << ") = " << idx;



     // Попробуем найти несуществующий
     int k = 10;
     idx = segmentTree.findKthZero(k);
     if (idx == -1) {
       cout << "\n" << k << "-й ноль не существует." << endl;
     }

     cout << "\n=== Состояние дерева отрезков (tree[1..]) ===" << endl;
     segmentTree.printTree();





    return 0;
}







