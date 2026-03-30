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

In the general version of the problem, we can no longer look only at the primary domain of a submission and the primary expertise of a reviewer. We also need to consider the secondary domain of the submission and the secondary expertise of the reviewer. This makes the problem more realistic, but also more difficult, because not all valid matches have the same quality.

The main idea would still be to start from the same flow-network structure used in the basic formulation. We would keep:

- a source connected to each submission
- one node for each submission
- one node for each reviewer
- each reviewer connected to the sink

The source-submission and reviewer-sink capacities would stay the same, because submissions still need a minimum number of reviews and reviewers still have a maximum workload. The main difference would be in the edges between submissions and reviewers. In the basic model, those edges only tell us whether a match is possible or not. In the general model, they should also reflect how good that match is.

Because of that, a simple Max-Flow formulation is no longer enough if we want more than just any feasible solution. A better approach is to use **Min-Cost Max-Flow**. The capacity of each submission-reviewer edge would still be `1`, but each edge would now have a cost. Better matches, such as primary-primary, should have lower cost, while weaker matches involving secondary fields should have higher cost. This way, the algorithm still finds a feasible assignment, but among all feasible assignments it prefers the ones with better overall quality.

The parameters already present in the input, such as `PrimaryReviewerExpertise`, `SecondaryReviewerExpertise`, `PrimarySubmissionDomain`, and `SecondarySubmissionDomain`, can be used to define that quality. One possible approach is to give each type of match a score based on these values and then convert that score into a cost for the Min-Cost Max-Flow algorithm.

### Complexity

This formulation is more expensive than the basic feasibility-only model. First, all submission-reviewer pairs still need to be checked, which takes `O(NM)`, where `N` is the number of submissions and `M` is the number of reviewers. After that, instead of a standard Max-Flow algorithm, we need a **Min-Cost Max-Flow** algorithm, which is heavier because each augmentation also has to consider edge costs.

So the general formulation is harder not only because there are more possible matches, but also because the goal changes. We are no longer trying to find just a feasible assignment. We are trying to find a good feasible assignment, taking into account the different quality levels of the matches.
