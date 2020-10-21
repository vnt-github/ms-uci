- [ ] heuristic
    - [ ] estimate to goal
    - [ ] h(n) is a function of state not node
    - [ ] problem specific knowledge to the search algorithm.

- [ ] g(n) = known path cost so far to node n.
- [ ] greedy best-first uses h(n)
- [ ] A* uses f(n)
- [ ] Branch n Bound Depth First Search uses f(n) for pruning agian upper bound.

- [ ] search efficiency is better if h(n) ~ h*(n). if h(n) = h*(n) then search is linear.

- [ ] GBFS
    - [ ] complete: true(graph in finite), false(tree with loops) false(in infinite space), time: O(b^m), space: O(b^m), optimal: false

- [ ] A*
    - [ ] complete: true(even if not admissible h, if step cost >= e > 0 and b < inf),
    - [ ] optimal: tree search(admissible), graph search(consistent), 
    - [ ] optimally efficient: yes, all other algo which are complete and optimal must expand at least as many as A*
    - [ ] time: O(b^m) : more details heuristic-search page 33.
    - [ ] space: O(b^m)  : more details heuristic-search page 33.

- [ ] C* is the cost of the shortest path to the goal.

- [ ] A* properties
    - [ ] A* expands every path passing through the node wherer f(n) < C*, where 
    - [ ] A* never expands any path for node where f(n) > C* 
    - [ ] A* expands every path for node where f(n) < C*, and subset of nodes where f(n) = C*
    - [ ] the better the heuristic the fewer nodes it expands

- [ ] admissible: h(n) <= h*(n), never overestimates, never pessimistic
- [ ] consistency(monotone): Δh <= c, f(n-1) <= f(n) f(n) is non-decreasing along any path

- [ ] consistent => admissible, admissible !=> consistent, !admissible => !consistent
- [ ] A*
    - [ ] two diff conditions because you might find a long cheap path after short expensive one so need to reprocess it's descendants
    - [ ] in consistent heuristic this never happens.
    - [ ] A* graph with admissible is possible but when we get cheaper path to a node we need to reprocess all it's descendents.

- [ ] non-admissible are complete not optimal but FAST.
    - [ ] can be used as a bound for search and saves a lot of space and time.
    - [ ] A* runs out of memory

- [ ] branch and bound Depth first search
    - [ ] f needs to be admissible and reasonable upper bound to terminate.
    - [ ] most practicle one
    - [ ] complete and optimal even if state space is infinite.
        - [ ] because sooner or later you'll get to a path that'll be pruned if that path is infinite.
    - [ ] time: exponential, depends on heurisitic. if heuristic is exact then it's linear.
    - [ ] space: linear
    - [ ] if same depth use smaller f value for tie breaker.
    - [ ] even after searching the optimal it continues.
    - [ ] anytime property.
    - [ ] may expand f > C*

- [ ] heuristics comparison
    - [ ] h2 >= h1, h2 dominates h1
    - [ ] h2 almost always better for search than h1
    - [ ] h2 is guaranteed to expand no more nodes that h1
    - [ ] h2 almost always expands fewer nodes that h1
    - [ ] not usefull unless  h1 and h2 are admissible/consistent

- [ ] for branching factor use d = depth, n = number of nodes expanded
    - [ ] x^(d) = n

- [ ] 

          n1
  100 /   |1  \   100
    n4_1_ m _1_n3
 100 \    |1  /  100
          n2
