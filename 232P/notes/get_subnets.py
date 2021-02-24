
from math import log2, ceil

def q1(old_prefix, min_hosts):
    bits_for_host_id = ceil(log2(min_hosts+2)) #bits required for each subnet host
    bits_for_subnet_id = (32-old_prefix)-bits_for_host_id
    no_hosts = 2**bits_for_host_id
    no_subnets = 2**bits_for_subnet_id
    new_prefix = old_prefix + bits_for_subnet_id
    print(new_prefix, no_subnets, no_hosts)

def get_subnets(old_prefix, no_subnets_req, min_hosts):
    bits_for_subnet_id = ceil(log2(no_subnets_req))
    bits_for_host_id = (32-old_prefix)-bits_for_subnet_id
    no_subnets = 2**bits_for_subnet_id
    no_hosts = 2**bits_for_host_id
    if no_hosts < min_hosts:
        return "ABORT!!, NOT POSSIBLE"
    for i in range(no_subnets_req):
        right_adjusted_subnet_bin = f"{bin(i)[2:]:0>{bits_for_subnet_id+old_prefix%8}}"
        eight_bit_bin = f"{right_adjusted_subnet_bin:0<8}"
        subnet_doted_decimal = int(eight_bit_bin, 2)
        print(subnet_doted_decimal)
    new_prefix = old_prefix + bits_for_subnet_id
    print(f"/{new_prefix}")

if __name__ == "__main__":
    q1(16, 500)
    get_subnets(16, 5, 250)
    # get_subnets(18, 10, 250)
    # get_subnets(23, 4, 200)