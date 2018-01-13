#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace change {

  auto greedy(int amount, vector<int> const& coins) -> vector<int> {
    auto soln = vector<int>(size(coins) + 1);
    for (auto i = 0; amount != 0 && i != size(coins); i++) {
      while (coins[i] <= amount) {
        soln[i]++;
        soln.back()++;
        amount -= coins[i];
      }
    }
    return soln;
  }

  auto dynamic(int amount, vector<int> const& coins, vector<vector<int>>& cache) -> vector<int> {
    // base case, nothing to do
    if (amount == 0) return vector<int>(size(coins) + 1);

    // is the solution cached?
    if (!empty(cache[amount])) return cache[amount];

    // recursively solve subproblems
    auto soln = vector<int>{};
    for (auto i = 0; i != size(coins); i++) {
      if (coins[i] <= amount) {
        auto u = dynamic(amount - coins[i], coins, cache);
        u[i]++;
        u.back()++;
        if (empty(soln) || u.back() < soln.back()) swap(soln, u);
      }
    }

    // update cache and return solution
    swap(cache[amount], soln);
    return cache[amount];
  }

  auto dynamic(int amount, vector<int> const& coins) -> vector<int> {
    auto cache = vector<vector<int>>(amount + 1);
    return dynamic(amount, coins, cache);
  }

} // namespace change

int main(int ac, char** av) {
  auto amount = 0;
  cin >> amount;

  auto numcoins = 0;
  cin >> numcoins;

  auto coins = vector<int>(numcoins);
  copy_n(istream_iterator<int>{cin}, numcoins, begin(coins));
  sort(begin(coins), end(coins), greater<int>{});
  if (empty(coins) || coins.back() != 1) coins.push_back(1);

  auto soln = change::dynamic(amount, coins);
  cout << soln.back() << ' ';
  for (auto i = 0; i != size(coins); i++) {
    cout << coins[i] << ',' << soln[i] << ' ';
  }
  cout << '\n';
}