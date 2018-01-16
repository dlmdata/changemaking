# change making problem
Greedy and dynamic programming solutions to the change making problem.

Given a set of coin denominations and an unlimited supply of each coin, find the smallest set of coins (fewest coins) that sums to a given amount. The denominations include a unit coin, so a solution exists for every amount.

These functions return a vector where the ith element is the number of times the ith coin is used in the solution, except for the last element, which is the total number of coins used.

## greedy solution

In this solution we iterate through the coins ordered by descending value, repeatedly selecting the largest coin that does not exceed the remaining amount.

```c++
namespace changemaking {

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

} // namespace changemaking
```

## dynamic programming solution

In this solution we use the fact that the optimal solution for amount _A_ that uses coin _C_ is _C_ plus the optimal solution for amount _A_ - _C_. Therefore we can solve the problem recursively. And we use memoization to avoid repeatedly solving subproblems.

```c++
namespace changemaking {

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

} // namespace changemaking
```
