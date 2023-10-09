// Copyright 2023 Gas
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
std::random_device rd;
std::mt19937 gen(rd());

// using std::cout;

class System {
 private:
  int num;
  int size;
  int opened;
  vector<int> idx;
  vector<int> szs;
  vector<vector<bool>> grid;

  int root(int p) {
    while (p != idx[p]) {
      idx[p] = idx[idx[p]];
      p = idx[p];
    }
    return p;
  }

 public:
  double percolation_probability;
  System() {}
  explicit System(int n) {
    num = n * n;
    size = n;
    opened = 0;
    idx.push_back(0);
    szs.push_back(n);
    for (int i = 1; i <= n * n; ++i) {
      if (i <= n) {
        idx.push_back(0);
      } else {
        if (i > n * n - n) {
          idx.push_back(n * n + 1);
        } else {
          idx.push_back(i);
        }
      }
      szs.push_back(1);
    }
    idx.push_back(n * n + 1);
    szs.push_back(n);

    for (int i = 0; i < n; ++i) {
      grid.push_back(vector<bool>{});
      for (int j = 0; j < n; ++j) {
        grid[i].push_back(false);
      }
    }
  }
  bool connected(int p, int q) { return root(p) == root(q); }

  void unite(int p, int q) {
    int i = root(p);
    int j = root(q);
    if (i == j)
      return;

    if (szs[i] <= szs[j]) {
      idx[i] = j;
      szs[j] += szs[i];
    } else {
      idx[j] = i;
      szs[i] += szs[j];
    }
  }
  bool is_percolate() { return connected(0, num + 1); }

  void monte_carlo() {
    std::random_device rd;
    std::mt19937 gen(rd());
    while (!is_percolate()) {
      std::uniform_int_distribution<int> dis(0, num - 1);
      int random_index = dis(gen);
      int row = random_index / size;
      int col = random_index % size;

      if (grid[row][col]) {
        continue;
      }
      int curr = random_index + 1;
      if (row > 0 && grid[row - 1][col]) {
        unite(curr, curr - size);
      }
      if (row < size - 1 && grid[row + 1][col]) {
        unite(curr, curr + size);
      }
      if (col > 0 && grid[row][col - 1]) {
        unite(curr, curr - 1);
      }
      if (col < size - 1 && grid[row][col + 1]) {
        unite(curr, curr + 1);
      }
      grid[row][col] = true;
      opened++;
    }
    percolation_probability = static_cast<double>(opened) / (num);
  }

  void print() {
    for (int i = 1; i <= size; ++i) {
      for (int j = 1; j <= size; ++j) {
        cout << idx[(i - 1) * size + j] << "    ";
      }
      cout << endl;
    }
  }

  void show() {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (grid[j][i]) {
          cout << "O ";
        } else {
          cout << "X ";
        }
      }
      cout << endl;
    }
  }
};

int main() {
  const int N = 300;
  const int T = 500;
  double percolation_probability = 0;
  for (int t = 0; t < T; ++t) {
    System s(N);
    s.monte_carlo();
    percolation_probability += s.percolation_probability;
  }
  percolation_probability /= T;

  cout << percolation_probability << endl;

  return 0;
}
