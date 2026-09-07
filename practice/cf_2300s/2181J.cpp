#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
//#define long int64_t
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define DOUBLE(x) ((double) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;








vector<double> bayes_update(const vector<double>& prior, int wins, int rounds) {
  double r_choose_w = 1.0;
  for (int i = 1; i <= wins; i++) {
    r_choose_w *= DOUBLE(rounds - i + 1);
    r_choose_w /= DOUBLE(i);
  }

  double norm = 0.0;
  vector<double> posterior(101);
  for (int p = 0; p <= 100; p++) {
    // Chance to get wins out of rounds with probability p/100, just a binomial coefficient
    double likelihood = r_choose_w;
    for (int i = 0; i < wins; i++) {
      likelihood *= DOUBLE(p) / 100.0;
    }
    for (int i = wins; i < rounds; i++) {
      likelihood *= DOUBLE(100 - p) / 100.0;
    }
    posterior[p] = prior[p] * likelihood;
    norm += posterior[p];
  }

  if (norm > 0.0) {
    for (int p = 0; p <= 100; p++) {
      posterior[p] /= norm;
    }
  }  //otherwise, the likelihood this happens is literally zero, so we'll just return whatever and it doesn't matter.
  return posterior;
}
/* Expected win probability */
double calc_win_prob(const vector<double>& pmf) {
  double prob = 0.0;
  for (int p = 0; p <= 100; p++) {
    prob += DOUBLE(p)/100.0 * pmf[p];
  }
  return prob;
}
/* Expected value, per unit bet */
double calc_expectation(const vector<double>& pmf) {
  double exp = 0.0;
  for (int p = 0; p <= 100; p++) {
    exp += DOUBLE(p)/100.0 * pmf[p];
    exp -= DOUBLE(100-p)/100.0 * pmf[p];
  }
  return exp;
}




void solve() {
  int n, k;
  cin >> n >> k;
  vector<double> root_pmf(101, 0.0);
  FORI(n) {
    int x;
    cin >> x;
    root_pmf[x] += 1.0 / n;
  }

  vector<vector<double>> dp(k+1, vector<double>(k+1, -1000.0));
  for (int rounds = k; rounds >= 0; rounds--) {
    for (int wins = 0; wins <= rounds; wins++) {
      if (rounds == k) {
        // Can't play anymore, so pay 1x
        dp[rounds][wins] = 1.0;
        continue;
      }

      vector<double> pmf = bayes_update(root_pmf, wins, rounds);
      double expectation_here = calc_expectation(pmf);
      fprintf(stderr, "for rounds%d wins%d, expectation is %.6f\n", rounds, wins, expectation_here);

      // How much do we want to bet now?
      // Beat fraction f of 1 if p m2 - (1-p) m1 >= 0
      double p = calc_win_prob(pmf);
      double win_multi = dp[rounds+1][wins+1];
      double lose_multi = dp[rounds+1][wins];
      double f = ((p*win_multi - (1.0-p)*lose_multi) >= 0) ? 1.0 : 0.0;

      // Expectation from where we go next
      dp[rounds][wins] = p * win_multi * (1.0+f) + (1.0 - p) * lose_multi * (1.0-f);
      fprintf(stderr, "  chance to win here is %.6f\n", p);
      fprintf(stderr, "  dp[%d][%d] = %.6f\n", rounds, wins, dp[rounds][wins]);
    }
  }

  cout << fixed << setprecision(12) << (dp[0][0]*1000.0 - 1000.0) << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */
