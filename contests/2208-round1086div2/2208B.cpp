#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int n, k, p, m;
  cin >> n >> k >> p >> m;
  vector<int> cards(n);
  for (int i = 0; i < n; i++) {
    cin >> cards[i];
    if (i == p-1) {
      cards[i] = -cards[i];
    }
  }

  fprintf(stderr, "Initial Deck: ");
  for (int c : cards) {
    fprintf(stderr, "%d ", c);
  }
  fprintf(stderr, "\n\n");

  int num_win_cards = 0;
  while (m > 0) {
    // Pick cheapest card out of top k, or the win condition
    int best_i;
    int best = INT_MAX;
    for (int i = 0; i < k && i < n; i++) {
      if (cards[i] < best) {
        best = cards[i];
        best_i = i;
      }
    }
    if (m < abs(best)) {
      // Can't afford any card, end game
      // Otherwise WA on pre 2 :)
      break;
    }
    if (best < 0) {
      // Win condition card
      num_win_cards++;
      m += best;
    } else {
      m -= best;
    }
    // Remove from front, place back
    // O(N) but fine
    cards.erase(cards.begin() + best_i);
    cards.push_back(best);
    fprintf(stderr, "Deck: ");
    for (int c : cards) {
      fprintf(stderr, "%d ", c);
    }
    fprintf(stderr, "   m left = %d, victories = %d\n", m, num_win_cards);
  }
  cout << num_win_cards << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}