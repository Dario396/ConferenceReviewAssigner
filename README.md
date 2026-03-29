## Risk Analysis for K > 1

For the case of **Risk Analysis = K**, with `K > 1`, the idea is to directly generalize the same approach used for `RiskAnalysis = 1`. First, the original conference instance is solved as a **Max-Flow** problem in order to verify whether the baseline assignment is feasible. If the baseline instance is not feasible, then the risk analysis is no longer meaningful, since the problem already fails to satisfy the required review constraints even without reviewer failures. Otherwise, all possible combinations of `K` reviewers are generated. For each combination, those reviewers are temporarily removed from the instance, the flow network is rebuilt, and the maximum flow is computed again. If the resulting flow is smaller than the total number of reviews required, then that subset of reviewers is considered critical, because its simultaneous failure makes a feasible review assignment impossible.

### Complexity

This approach is exact, but it quickly becomes expensive. If there are `M` reviewers, then the number of subsets of size `K` that must be tested is given by `C(M, K)`. For each subset, the network must be rebuilt and the **Max-Flow** algorithm must be executed again. If building the network costs `O(NM)`, where `N` is the number of submissions and `M` is the number of reviewers, and Edmonds-Karp costs `O(VE²)`, then the total complexity is:

`O(C(M, K) · (NM + VE²))`

This means that the method is practical for small values of `K`, but the number of tested scenarios grows combinatorially, making the approach significantly more expensive when either the number of reviewers or the value of `K` increases.

### Non-trivial example

Consider a conference with four submissions and six reviewers. Submissions `1` and `2` belong to domain `1`, while submissions `3` and `4` belong to domain `2`. Each submission requires `2` reviews, and each reviewer can perform at most `2` reviews. Reviewers `1`, `2`, and `3` have expertise in domain `1`, while reviewers `4`, `5`, and `6` have expertise in domain `2`.

In the baseline case, a feasible assignment exists, because the total capacity available in each domain is enough to cover the corresponding submissions. If only one reviewer fails, the instance may still remain feasible, because the remaining reviewers of that domain can still cover the required number of reviews. However, if `K = 2` and two reviewers from the same domain fail simultaneously, then the remaining capacity in that domain is no longer sufficient.

Therefore, the critical pairs are:
- `(1,2)`, `(1,3)`, and `(2,3)` for domain `1`
- `(4,5)`, `(4,6)`, and `(5,6)` for domain `2`

This example shows that the approach correctly identifies the subsets whose removal makes the assignment impossible, while also illustrating the combinatorial growth in the number of tested combinations.
### Example output

```text
#Risk Analysis: 2
(1,2), (1,3), (2,3), (4,5), (4,6), (5,6)
```
