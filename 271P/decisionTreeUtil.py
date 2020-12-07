from math import log2
from functools import reduce
from statistics import variance, pvariance

def PlogP(accumulator, probability):
    return accumulator + (0 if not probability else probability*log2(probability))

def h(probabilities):
    return abs(reduce(PlogP, probabilities, 0))

if __name__ == "__main__":
    # print(h([5/6, 1/6]))
    # print(h([0.25, 0.25, 0.25, 0.25]))
    # print(h([0.75, 0.25]))
    # print(h([0.5, 0.5]))
    # print(h([1, 0]))
    # print(h([0.2, 0.8]))

    # print(h([5/6, 1/6]) - (4/6*h([4/4, 0/4]) + 2/6*h([1/2, 1/2])))
    # print(h([5/6, 1/6]) - (3/6*h([3/3, 0/3]) + 3/6*h([2/3, 1/3])))

    # print(h([6/12, 6/12]) - (2/12*h([2/2, 0/2]) + 4/12*h([4/4, 0/4]) + 6/12*h([2/6, 4/6])))
    # print(h([6/12, 6/12]) - (2/12*h([1/2, 1/2]) + 2/12*h([1/2, 1/2]) + 4/12*h([2/4, 2/4]) + 4/12*h([2/4, 2/4]) ))

    # print(h([4/8, 4/8]) - (5/8*h([3/5, 2/5]) + 3/8*h([1/3, 2/3])))

    # original = h([4/8, 4/8]) 
    # print(original - (2/8*h([1/2, 1/2]) + 6/8*h([3/6, 3/6]) ))
    # print(original - (6/8*h([3/6, 3/6]) + 2/8*h([1/2, 1/2]) ))
    # print(original - (2/8*h([2/2, 0/2]) + 3/8*h([1/3, 2/3]) + 3/8*h([1/3, 2/3]) ))

    # print(h([1/2, 1/2]), h([3/4, 1/4]), h([1/100, 99/100]))
    
    # original = h([4/8, 4/8])
    # print(original - (4/8*h([1/4, 3/4]) + 4/8*h([3/4, 1/4]) ))
    # print(original - (2/8*h([1/2, 1/2]) + 6/8*h([3/6, 3/6]) ))
    # print(original - (4/8*h([2/4, 2/4]) + 4/8*h([2/4, 2/4]) ))
    
    # print(h([1/2, 1/2]))
    # print(h([5/10, 5/10]) - (4/10*h([4/4, 0/4]) + 6/10*h([5/6, 1/6]) ))
    # print(4/8*(7.98-7.18) + 4/8*(7.98-3.5))
    # print(4/8*(7.98-12.69) + 4/8*(7.98-2.5))
    # print(6/8*(7.9843-9.3333) + 2/8*(7.98-2.5))
    # original = pvariance([10, 12, 13, 14, 15, 16, 18, 19])
    # print(original)
    print(h([1/4, 3/4]))
    print(h([5/10, 5/10]) - (3/10*h([3/3, 0/3]) + 7/10*h([2/7, 5/7]) ))

    original = pvariance([8, 6, 9, 5, 2, 1, 3, 4])
    print(6/8*(original-pvariance([8, 6, 9, 1, 3, 4])) + 2/8*(original-pvariance([5, 2])))
    print(4/8*(original-pvariance([8, 9, 1, 4])) + 4/8*(original-pvariance([6, 5, 2, 3])))
    print(4/8*(original-pvariance([8, 6, 9, 2])) + 4/8*(original-pvariance([5, 1, 3, 4])))

    print()

    original = 6.9375
    print(6/8*(original-7.8055555555556) + 2/8*(original-2.25))
    print(4/8*(original-10.25) + 4/8*(original-2.5))
    print(4/8*(original-7.1875) + 4/8*(original-2.1875))





    