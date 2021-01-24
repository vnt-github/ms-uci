- key problem:
    - paper proposes an efficient method to maintain vector clocks which reduces the size of timestamp related information in a message, which is directionaly proportional to the number of processes in the system at the expense of very little extra storage.
    - the proposed method is resilient to changes in topology like addition and deletion communication edges.
- assumptions:
    - assumes FIFO message delivery and **resilient to changes in topology**.

- proposed techniques:
    - maintain two vectors
        - LUi[1...N]: value of Ti[i] when process i **Last Updated** entry Ti[j].
        - LSi[1...N]: value of Ti[i] when the process i **Last Sent** a message to process j.
    - since last communication from process i to process j only those elemets Ti[k] have changed for which LSi[j] < LUi[k], so only when process i sends a message to j, it only sends those entries Ti[k] for which LSi[j] < LUi[k].
    - it requires O(n) space at each process in basic form.

- modifications for maintaining causal relationships
    - some application like prototyping langauges design, required that causal relationships be determined between two messages Mj and Mk arriving at a process from process j and k respectively.
    - Since only differential vectors are sent, neither message may contains timestamp tuple from other, even though the two events may be causally related.
    - for this problem as modified approach is as follows
        - A process i matintains array LRi[i...N, i...N] called **Last Received** where entry LRi[j, k] is the latest value of Tj[k] received by process i from process j.
        - when process i receives a message from j the corresponding entries is LRi[j] are updated.
        - this can be used to reconstruct timestamps at process j and k when Mj and Mk were respectively sent by them, and determine causal relationship at the expense of O(n^2) extra space.

- advantages
    - distributed systems requiring latest global state information can use it as the incrementaion changes are sufficient to construct the latest global state.
    - distributed systems requiring consistent global state and algorithms for recovery and termination detection can also benefit from reduce message size in transition.
    - locality of communications: in distributed structures like tree structure or cluster structure with localized communication, only incremental changes to timestam vector need to be transferred, hence making proposed techniqued even more effective.
    - optimizations on storage:
        - if process i is not reachable from process j, then Ti[j] and LUi[j] will be 0 and undefined respectively, thus process i need not keep and entry for all such processes j in Ti and LU.
        - if there is no logical channel from process i to j then LSi[j] will be undefined so process i need not to keep an entry for process j in its LSi.

- efficiency: average percentage reduction in size of timestamp related information to be tranferred in a message as compared to when sending the entire vector timestamp = (1-((log2N + b).n)/(b.N)).100% where
    - n: average nubmer of entries in Ti for trnamission.
    - b: number of bits in a sequence number.
    - log2N: number of bits needed to code N process ids.

- limitations:
    - proposed technique is only beneficial only if n < N.b/(lob2N+b).

