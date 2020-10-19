- [] problem types
    - [ ] static/dynamic, deterministic/stochastic, Observable/partially Observable/Unobservable, Discrete/Continuous
        - [ ] fully observable, deterministic: fixed seq of actions: open-loop.
        - [ ] model is incorrect, non-deterministic: closed-loop monitring percepts.
        - [ ] partially-observable or nondeterministic env: branching strategy recommends diff future actions baseed on what percepts arrive.

- [ ] agent four-phase problem-solving-process
    - [ ] goal formulation, problem formulation, search, execution.

- [ ] states, initial_state, goal_states, actions, transition_model, action_cost_function

- [ ] abstraction: the process of removing irrelevant details, retains all important details
    - [ ] valid: can be elaborated into more detailed world.
    - [ ] userfull: abstracted problem is easier to solve.

- [ ] state space:
    - [ ] set of states of the world
    - [ ] actions and transitions.
- [ ] search space:
    - [ ] set of states from initial to some other state.

- [ ] properties of search stragegy: order of node expansion
    - [ ] completeness: does it always find a solution if one exists?
    – [ ] optimality: does it always find a least-cost path solution?
    – [ ] time complexity: number of nodes generated
    – [ ] space complexity: maximum number of nodes in memory
    - [ ] b: branching factor, d: depth of least-cost goal, m: max depth of the state space.

- [ ] evaluation function: f(n) choose frontier with min f(n) value

- [ ] Uninformed search
    - [ ] one non-goal state is better that any other.
    - [ ] which of two actions is better.

- [ ] goat test always when popped
    - [ ] unless in breadth-first-search where cost is non-decresing function of depth only

- [ ] breadth first search = f(n) = depth, FIFO
    - [ ] early goad check on generation, space is bigger problem
    - [ ] complete: yes, time: O(b^d), space: O(b^d), optimal: No, yes if cost = f(d) s.t. f(d) >= f(d-1)

- [ ] uniform cost search: f(n) = path cost, priority queue
    - [ ] late goal test, no loop check
    - [ ] complete: yes, time: O(b^(1+c*/e))~O(b^(d+1)), space: O(b^(1+c*/e))~O(b^(d+1)), optimal: yes if step_cost >= e > 0.
    - [ ] C* is the cost of the optimal solution, e is the lower bound on the cost of each action.

- [ ] depth first search = f(n) = - depth, LIFO
    - [ ] late goal test, cycle test
    - [ ] complete: no(goes in loop = fixed by check if current nodes occured before on the path to root), faile in infinite-depth spaces
    - [ ] time: O(b^m)
    - [ ] space: O(bm)
    - [ ] optiman: no

- [ ] DFS vs BFS
    - [ ] BFS: more memory, shallow goals, many long paths, many loops, small search space.
    - [ ] DFS: less memory, many goals, few long or infinite paths, not many loops, huge search space.

- [ ] iterative depth limited search
    - [ ] memory adv of dfs, completeness of bfs.
    - [ ] complete: yes, time: O(b^d), space: O(bd), optimal: No, yes if cost = f(d) s.t. f(d) >= f(d-1)

- [ ] 71 page of 02-uninformed-search.pdf