- why is this distinction important?
    - because the latency occured between messag passing introduces the various anamolies we need to deal with while working with distributed systems.


- flaws of distributed algorith for mutual exclusion problem:
    - mutual exclusion problem:
        - it's trying to solve the mutual exclusion problem defined as:
            - system with fixed number of processes with one shared resources which can only be accessed by one processor at a time. Sharing algo that:
                - process must release resource before giving to another.
                - request and resource in first come first serve.
                - every process possessing resourse eventuall releases.
    - distributed algo solution:
            - assumptions: 
                - messages are received in the same order they were sent.
                - every message is eventually received.
                - process can message directly to one another.
            - from the image describe the algo.
    - anomalous behaviour:
        - from image present concise explanation.

        - rule 1 satisfied as for both A and B it is the first ordered request for resource.
        - if rule 2 is already satisfied then we have concurrent shared resource request causing conflict

- Two Solutions: (explain in brief using highlights)

- phycical clock brief 2 points.

- logical clock as solution rest of the points from highlights.

- criticism: we loose global state information on weather some processes were parallel or not.