import sys
from typing import List
from random import randint
from heapq import heapify, heappush, heappop, heappushpop

schedule = []
loads = []

def set_processor_load(no_processors: int, low: int = 10, high: int = 100) -> List[int]:
    """get uniformly distributed unbalances load.

    Keyword arguments:
    no_processors -- number of processors
    low -- lowest allowed load units value
    hight -- highest allowed load unites value
    """
    global loads
    loads = [randint(low, high) for _ in range(no_processors)]

def set_scheduling_time(no_processors: int, low: int = 100, high: int = 1000) -> None:
    global schedule
    for processors_id in range(no_processors):
        heappush(schedule, (randint(low, high), processors_id))

def get_load_balancing_processor(low: int = 100, high: int = 1000) -> int:
    # NOTE: discuss the offset to reset value for the popped value
    return heappushpop(schedule, (schedule[0][0] + randint(low, high), schedule[0][1]))

def is_balanced(no_processors: int, local_diff_max: int, global_min_units: int) -> bool:
    for processor_id in range(no_processors):
        next_id = (processor_id+1)%no_processors
        prev_id = (processor_id-1)%no_processors
        if loads[processor_id] < global_min_units or abs(loads[processor_id] - loads[next_id]) > local_diff_max or abs(loads[processor_id] - loads[prev_id]) > local_diff_max:
            return False
    return True

def balance_load(no_processors: int, processors_id: int, give_max: int, local_diff_max: int) -> None:
    next_id = (processors_id+1)%no_processors
    prev_id = (processors_id-1)%no_processors
    avg = (loads[processors_id] + loads[next_id] +  loads[prev_id])//3
    excess = loads[processors_id] - avg
    if excess > 0 and avg > loads[prev_id]:
        loads[prev_id] += max(1, excess // 2)
        excess -= max(1, excess // 2)

    if excess > 0 and avg > loads[next_id]:
        loads[next_id] += max(1, excess // 2)
        excess -= max(1, excess // 2)
        
    loads[processors_id] = avg + excess

def simulate_load_balancing(no_processors: int, give_max: int, local_diff_max: int, global_min_units: int) -> None:
    set_processor_load(no_processors)
    set_scheduling_time(no_processors)
    print(loads, sum(loads))
    while not is_balanced(no_processors, local_diff_max, global_min_units):
        next_min_schedule_time, processors_id  = get_load_balancing_processor()
        balance_load(no_processors, processors_id, give_max, local_diff_max)
        print(loads)
        print(processors_id, next_min_schedule_time)
    print(loads, sum(loads))

if __name__ == "__main__":
    no_processors = int(sys.argv[1])
    give_max = int(sys.argv[2])
    local_diff_max = int(sys.argv[3]) # should be >= 2
    global_min_units = int(sys.argv[4])
    # NOTE: need to figure better way to distribute to accomodate local_diff_min < 2
    assert local_diff_max >= 2, 'local diff must be greater than 1'
    simulate_load_balancing(no_processors, give_max, local_diff_max, global_min_units)