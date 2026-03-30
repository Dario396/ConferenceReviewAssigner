# Project Analysis

## Risk Analysis for K > 1

For the case of **Risk Analysis = K**, with `K > 1`, the idea is to extend the same reasoning used for the case where `RiskAnalysis = 1`. First, the original conference instance is solved as a **Max-Flow** problem to check whether a feasible assignment exists. If the baseline instance is not feasible, then performing risk analysis does not make much sense, since the problem already fails to satisfy the required review constraints even without reviewer failures. Otherwise, all subsets of `K` reviewers are considered. For each subset, those reviewers are temporarily removed, the flow network is rebuilt, and the maximum flow is computed again. If the resulting flow is smaller than the total number of reviews required, then that subset is classified as **critical**, because its simultaneous failure makes a feasible review assignment impossible.

### Complexity

This method is exact, but it becomes expensive quite quickly. If there are `M` reviewers, then the number of subsets of size `K` that need to be tested is given by `C(M, K)`. For each subset, the network must be rebuilt and the **Max-Flow** algorithm must be executed again. If building the network costs `O(NM)`, where `N` is the number of submissions and `M` is the number of reviewers, and Edmonds-Karp costs `O(VE^2)`, then the total complexity is:

`O(C(M, K) * (NM + VE^2))`

In practice, this means the approach is manageable for small values of `K`, but it becomes much more expensive as `K` or the number of reviewers increases, because the number of combinations grows very quickly.

### Non-trivial example

Consider a conference with four submissions and six reviewers. Submissions `1` and `2` belong to domain `1`, while submissions `3` and `4` belong to domain `2`. Each submission requires `2` reviews, and each reviewer can perform at most `2` reviews. Reviewers `1`, `2`, and `3` have expertise in domain `1`, while reviewers `4`, `5`, and `6` have expertise in domain `2`.

In the baseline case, a feasible assignment exists, because the total capacity available in each domain is enough to cover the corresponding submissions. If only one reviewer fails, the instance may still remain feasible, because the remaining reviewers of that domain can still cover the required number of reviews. However, if `K = 2` and two reviewers from the same domain fail simultaneously, the remaining capacity in that domain is no longer enough.

So, the critical pairs are:

- `(1,2)`, `(1,3)`, and `(2,3)` for domain `1`
- `(4,5)`, `(4,6)`, and `(5,6)` for domain `2`

This example shows how the method identifies exactly the subsets whose removal makes the assignment impossible, while also highlighting the combinatorial growth in the number of tested combinations.

### Example output

```text
#Risk Analysis: 2
(1,2), (1,3), (2,3), (4,5), (4,6), (5,6)
```

## General Formulation without Risk Analysis

For the general case, the problem is no longer restricted to the primary domain of each submission and the primary expertise of each reviewer. Instead, both the **primary and secondary domains** of submissions and the **primary and secondary expertise** of reviewers must be considered. This makes the assignment problem more expressive, because some reviewer-submission pairs are stronger matches than others.

A natural extension is to keep the same **Max-Flow** structure as the basis of the solution, but associate a quality value with each possible assignment edge between a submission and a reviewer. The source would still connect to each submission with capacity equal to the required number of reviews, and each reviewer would still connect to the sink with capacity equal to the maximum number of reviews they may perform. The difference lies in the edges between submissions and reviewers: instead of representing only whether a match is allowed, these edges would also encode how desirable that match is.

To model this, the most suitable approach is to use a **Min-Cost Max-Flow** formulation. Each compatible reviewer-submission pair would receive capacity `1` and a cost derived from the matching quality. For example, a match between a submission's primary domain and a reviewer's primary expertise should receive a better score than a match involving a secondary field. Since Min-Cost Max-Flow minimizes cost, stronger matches can be represented by lower costs, while weaker matches receive higher costs. In this way, the algorithm not only finds a feasible assignment, but also prefers higher-quality allocations among all feasible solutions.

The weights already present in the input, namely `PrimaryReviewerExpertise`, `SecondaryReviewerExpertise`, `PrimarySubmissionDomain`, and `SecondarySubmissionDomain`, can be used to define these costs. A possible interpretation is to combine the contribution of the reviewer side and the submission side into a single score for each edge, then convert that score into a cost for the optimization process.

### Complexity

This formulation is more expensive than the basic feasibility-only model. First, all submission-reviewer pairs must still be tested, which takes `O(NM)`, where `N` is the number of submissions and `M` is the number of reviewers. Then, instead of a standard Max-Flow algorithm, the problem is solved with **Min-Cost Max-Flow**, whose complexity is higher because each augmentation must take edge costs into account. Using a shortest-path based implementation, the total complexity is polynomial, but significantly larger than the basic formulation.

Therefore, the general version is computationally harder, since the goal is no longer just to determine whether a feasible assignment exists, but also to optimize the quality of the final allocation according to the primary and secondary domain/expertise preferences.
