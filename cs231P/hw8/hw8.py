import time
import sys
from typing import List
from random import randint
from heapq import heapify, heappush, heappop, heappushpop
from math import floor

schedule = []
loads = []

def set_processor_load(no_processors: int, low: int = 10, high: int = 100) -> List[int]:
    """get uniformly distributed unbalances load.

    Keyword arguments:
    no_processors -- number of processors
    low -- lowest allowed load units value
    high -- highest allowed load unites value
    """
    global loads
    loads = [randint(low, high) for _ in range(no_processors)]

def set_scheduling_time(no_processors: int, low: int = 100, high: int = 1000) -> None:
    """set the random time between low and high for each processors as  it's balacing time

    Keyword argument:
    no_processors -- number of processors
    low -- lowest allowed time value
    high -- highest allowed time value
    """
    global schedule
    for processors_id in range(no_processors):
        heappush(schedule, (randint(low, high), processors_id))

def get_load_balancing_processor(low: int = 100, high: int = 1000) -> int:
    """get the next processor which has to perform the balaching of load

    Keyword argument:
    low -- lowest allowed time value
    hight -- highest allowed time value 
    """

    # NOTE: discuss the offset to reset value for the popped value
    return heappushpop(schedule, (schedule[0][0] + randint(low, high), schedule[0][1]))

def is_balanced(no_processors: int, local_diff_max: int, global_min_units: int) -> bool:
    """returns if the current load state is balance or not

    Keyword argument:
    no_processors -- number of processors
    local_diff_max -- the maximum allowed absolute difference of loads between the adjacent processors
    global_min_units -- minimum amount of load units each processor need to have in balanced state
    """
    for processor_id in range(no_processors):
        next_id = (processor_id+1)%no_processors
        prev_id = (processor_id-1)%no_processors
        if loads[processor_id] < global_min_units or abs(loads[processor_id] - loads[next_id]) > local_diff_max or abs(loads[processor_id] - loads[prev_id]) > local_diff_max:
            return False
    return True

def balance_load_unequal(no_processors: int, processors_id: int, give_max: int) -> None:
    """perform balancing of loads betweend processors at index processor_id and it's neighbours described below
    
    balancing processors looks at its two neighbors, compute an average number of load units each should have to equalize each
    other’s load and will “give” load units to the neighboring processor(s) such that the difference in load units between 
    neighboring processors is balanced. If by “giving” load units balancing is not possible, the processor does nothing

    Keyword argument:
    no_processors -- number of processors
    processors_id -- index of processor to perform the balancing activity
    give_max -- maximum unit of load current processor can give to it's unbalanced neighbours
    """

    next_id = (processors_id+1)%no_processors
    prev_id = (processors_id-1)%no_processors
    avg = (loads[processors_id] + loads[next_id] +  loads[prev_id])//3
    excess = loads[processors_id] - avg
    if excess <= 0:
        return
    
    # if loads = [60, 60, 61, 60, 59] and current balancing processor in index 2(value 61) then we need to transfer excess 1 unit to the last unit with load 59
    if avg >= loads[prev_id]:
        prev_req = avg-loads[prev_id]+1
        loads[prev_id] += min(give_max, excess, prev_req)
        excess -= min(give_max, excess, prev_req)

    if avg > loads[next_id]:
        next_req = avg-loads[next_id]
        loads[next_id] += min(give_max, excess, next_req)
        excess -= min(give_max, excess, next_req)
        
    loads[processors_id] = avg + excess

def simulate_load_balancing(no_processors: int, give_max: int, local_diff_max: int, min_units_as_avg_fraction: int, timeout_in_sec: int) -> None:
    """simulate validity of balance_load_unequal load balanching strategy and estimate the time to converge to balanced state

    Keyword argument:
    no_processors -- number of processors
    give_max -- maximum unit of load current processor can give to it's unbalanced neighbours
    local_diff_max -- the maximum allowed absolute difference of loads between the adjacent processors
    min_units_as_avg_fraction -- the fraction of average load each processors must have in balance state eg: 0.9*(sum(load)/len(loads))
    timeout_in_sec -- maximum time to converge to balanced state.
    """
    set_processor_load(no_processors)
    set_scheduling_time(no_processors)
    global_min_units = floor(min_units_as_avg_fraction*(sum(loads)//len(loads)))
    print('initial load state:\n', loads, '\nsum: ', sum(loads), ', global_min_units:', global_min_units)
    
    timeout = time.time() + timeout_in_sec
    next_min_schedule_time = schedule[0][0]
    while time.time() < timeout and not is_balanced(no_processors, local_diff_max, global_min_units):
        next_min_schedule_time, processors_id  = get_load_balancing_processor()
        balance_load_unequal(no_processors, processors_id, give_max)
    if not is_balanced(no_processors, local_diff_max, global_min_units):
        print("failed to converge in ", timeout_in_sec, " seconds")
    
    print('last scheduled time slice value:', next_min_schedule_time)
    print('final load state:\n', loads, '\nsum: ', sum(loads), ', max load unit: ', max(loads), ', min load unit:', min(loads))
    print('-'*100)


if __name__ == "__main__":
    no_processors = int(sys.argv[1])
    give_max = int(sys.argv[2])
    local_diff_max = int(sys.argv[3])
    min_units_as_avg_fraction = float(sys.argv[4])
    timeout_in_sec = int(sys.argv[5])
    assert give_max >= 1, 'maximum number of units to transfer during balancing must be non negative'
    assert local_diff_max >= 2, 'local diff must be greater than 1'
    simulate_load_balancing(no_processors, give_max, local_diff_max, min_units_as_avg_fraction, timeout_in_sec)