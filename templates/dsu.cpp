#include <bits/stdc++.h>
using namespace std;





/*
 * DSU
 * Code mostly copied from USACO Guide, with a few extra features added in
 */
class DSU {
private:
	vector<int> parents;
	vector<int> sizes;

public:
	int number_cc;
  int largest_cc;

  explicit DSU(int n) : parents(n), sizes(n, 1), number_cc(n), largest_cc(1) {
		for (int i = 0; i < n; i++)  parents[i] = i;
	}

	int find(int x) {
    return parents[x] == x ? x : (parents[x] = find(parents[x]));
  }

	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root)  return false;
		if (sizes[x_root] < sizes[y_root]) {
      swap(x_root, y_root);
    }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
    largest_cc = max(largest_cc, sizes[x_root]);
    number_cc--;
		return true;
	}

	bool connected(int x, int y) { return find(x) == find(y); }
};





int main() {
  int n = 10;
  DSU dsu(n);
  printf("Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(0, 1);
  printf("0<->1   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(0, 2);
  printf("0<->2   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(0, 3);
  printf("0<->3   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(1, 2);
  printf("1<->2   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(4, 5);
  printf("4<->5   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(6, 7);
  printf("6<->7   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(8, 9);
  printf("8<->9   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(7, 8);
  printf("7<->8   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
  dsu.unite(5, 6);
  printf("5<->6   Number of CCs: %d   Largest CC: %d\n", dsu.number_cc, dsu.largest_cc);
}
