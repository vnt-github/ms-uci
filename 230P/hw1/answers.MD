- DOUBT
    - is E part of the cut, cos where is the cut line.
    - are the lamport with or without the process ids for total ordering.
    - paper summary:
        - papers background of the class material, examples or basic stuff like reflexive relation etc?.. i've skipped them.
        - can the critiue be on other that content like structure or sequence of the sections in the paper.
    - how do you submit assignment is there a specific format?
        - single pdf with all all parts of zip with different doc for summary.
        - take printout and scan cos in chandy-lamport you've mentioned annotate the figure.
        - i was going to modify the pdf online.


- Question 1:
    - 1. 1,1,4,5,6,8,10
    - 2. A: 12, B: 10, C: 6 
    - ~~3. the causal path be simple or have to be long.~~
        - can be simple, the point is reflected by lamports timestamps.
        - m and n, After receiving message M3, C cends message M5 to A is correctly ideifnitedi by lamport scalar clocks as timestamp(m) = 5 and timestamp(n) = 6 and 5 < 6.
    - ~~4 - the question is  like given the time by lamport to these event can you determine if they are equal WITHOUT LOOKING AT THE EVENT DIAGRAM.~~
        - ~~Yes: if i increment and make event i 6, as you've said the same time stamp are concurrent.~~
        - No because Lamport timestamps not guaranteed to be ordered or unequal for concurrent
            - timestamp(M4) < timestamp(M5) => (E1 (happens before) E2) or (E1 and E2 are concurrent) events

- Question 2:
    - 1. done in the pdf.
    - 2. done in the pdf.

- Question 3:
    - 1. PHYSICAL vs LOGICAL
        - phycical clock: physical process coupled with a method of measuring iterations of that process to record the passage of time. for eg: rotation of earth in solar days, counting transition of a crystal (cesium 133, quarts) etc
        - logical clock:  Used to determine causality in distributed systems in which we use a abstract mechanism which assigns to any **atomic event** e∈E the value C(e)(typicall made from **non-negative integers**) of some time domain T where T is **partially ordered set**, such that if event e occurs before e' then it implies that C(e) is less that C(e').
    - 2. done in the pdf.
    - 3. done in the pdf.

- Question 4
    - 1. done in the Q1 1 of the pdf.
    - 2. done in the pdf.
        - doubt about where the cut is ans is E is part of it.

