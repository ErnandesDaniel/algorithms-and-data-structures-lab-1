#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SegmentTree {
private:
  vector<int> tree;
  vector<int> arr;
  int n;

  void build(int v, int tl, int tr) {
    if (tl == tr) {
      tree[v] = (arr[tl] == 0) ? 1 : 0;
    } else {
      int tm = (tl + tr) / 2;
      build(v * 2, tl, tm);
      build(v * 2 + 1, tm + 1, tr);
      tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
  }

  void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
      arr[pos] = val;
      tree[v] = (val == 0) ? 1 : 0;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        update(v * 2, tl, tm, pos, val);
      else
        update(v * 2 + 1, tm + 1, tr, pos, val);
      tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
      return 0;
    if (l == tl && r == tr) {
      return tree[v];
    }
    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, min(r, tm)) + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
  }

  int findKthZeroInRangeImpl(int v, int tl, int tr, int l, int r, int k) {
    if (k <= 0 || tl > r || tr < l)
      return -1;
    if (tl == tr) {
      if (tree[v] > 0 && k == 1 && l <= tl && tl <= r) {
        return tl;
      }
      return -1;
    }

    int tm = (tl + tr) / 2;

    int left_count = 0;
    if (!(l > tm || r < tl)) {
      left_count =
          (l <= tl && tm <= r) ? tree[v * 2] : query(v * 2, tl, tm, max(l, tl), min(r, tm));
    }

    if (left_count >= k) {
      return findKthZeroInRangeImpl(v * 2, tl, tm, l, r, k);
    } else {
      return findKthZeroInRangeImpl(v * 2 + 1, tm + 1, tr, l, r, k - left_count);
    }
  }

public:
  SegmentTree(const vector<int>& input) : arr(input), n(input.size()) {
    tree.resize(4 * n);
    build(1, 0, n - 1);
  }

  void update(int pos, int val) {
    update(1, 0, n - 1, pos, val);
  }

  int findKthZeroInRange(int l, int r, int k) {
    return findKthZeroInRangeImpl(1, 0, n - 1, l, r, k);
  }

  void PrintTree() const {
    cout << "Tree: ";
    for (int i = 1; i < 4 * n && i < static_cast<int>(tree.size()); ++i) {
      cout << tree[i] << " ";
    }
    cout << endl;
  }

  void PrintArray() const {
    cout << "Массив: ";
    for (int i = 0; i < n; ++i) {
      cout << arr[i];
      if (i < n - 1)
        cout << " ";
    }
    cout << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  vector<int> inputArray(N);

  for (int i = 0; i < N; ++i) {
    cin >> inputArray[i];
  }

  SegmentTree segmentTree(inputArray);

  int M;
  cin >> M;

  char type;

  string output_string = "";

  for (int i = 0; i < M; i++) {
    cin >> type;

    if (type == 's') {
      int l, r, k;

      cin >> l >> r >> k;

      l--;
      r--;

      int idx = segmentTree.findKthZeroInRange(l, r, k);

      int output_index = idx;

      if (idx > -1) {
        output_index++;
      }

      output_string = output_string + " " + to_string(output_index);

    } else if (type == 'u') {
      int pos, val;

      cin >> pos >> val;

      pos--;

      segmentTree.update(pos, val);
    }
  }

  cout << output_string << endl;

  return 0;
}