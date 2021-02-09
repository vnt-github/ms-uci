- who configures the error recovery policy correction or retransmission.
    - because for critircal(bank transactional) secure priority, it's should be dropped and retransmitted.
        - because to prevention malicious correction.
    - for voip, video non-critical it could be correction.

- MAP: code == cdna ?

- what if we only had mac and not ip addresses 
    - how would we can make it work globally.

- switches does'nt crete new network it just extends the range of the subnetwork
    - switches are useds between same building
    - don't change the frame
- routers create network on each of their interfaces
    - change frame passing through ie. change mac addresses.


- mac doesn't allow override cache.
- ssl: encrypt
    - security layer.

- arp: security doesn'nt one can be saved from man in middle using ssl.
    - how can arp be used to do malicious on fully secure https system and environment.

- what if i ping 1000 pings does arp waits for the 1000 pings.
    - simultaneously pc2 fails.
    - will the pc2 to pc1 meanwhile fail.

- links local address limitation and zone index.

- python3 code for faster binary to int and & operation.
```
bin(255)
int("11110000",2) & 187

# Q1. create a subnet of 500 hosts with all 0 and 1 unused for 125.36.0.0/16

from math import log2, ceil

def q1(old_prefix):
    bits_for_host_id = ceil(log2(500+2)) #bits required for each subnet host
    bits_for_subnet_id = (32-old_prefix)-bits_for_host_id
    no_hots = 2**bits_for_host_id
    no_subnets = 2**bits_for_subnet_id
    new_prefix = old_prefix + bits_for_subnet_id
    print(new_prefix, no_subnets, no_hots)

q1(16)

# Q2. create 5 subnets for address prefix 125.36.0.0/16 with min 250 hosts

from math import log2, ceil

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

get_subnets(16, 5, 250)
get_subnets(18, 10, 250)
```


- for the `show ip route` for the cisco routers, there are no entries for the subnet or for network prefix in the routing table,
- is the 0s in the destination addresses in the routing table tell the network id?
    - solution adding different subnet masks shows it
    ```    
    Router2#show ip route
    Codes: C - connected, S - static, R - RIP, M - mobile, B - BGP
        D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
        N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
        E1 - OSPF external type 1, E2 - OSPF external type 2
        i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
        ia - IS-IS inter area, * - candidate default, U - per-user static route
        o - ODR, P - periodic downloaded static route

    Gateway of last resort is not set

        10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
    C       10.0.2.0/24 is directly connected, FastEthernet0/0
    C       10.0.3.0/24 is directly connected, FastEthernet1/0
    S       10.0.1.0/24 [1/0] via 10.0.2.0
    S       10.4.0.0/16 [1/0] via 10.0.3.0

    ```

- cisco routing and forwarding table show and route cache.

- last ip entry in the cache is for to find the mac address of the router on an Broadcast environment via ARP like Ethernet. Serial is not a broadcast env.

- page 93 how its the /24 10.0.64.0/24 came
    - 10.32.0.0/19
    - 10.0.96.100/24 - 10.0.96.100/32 typo?
    - on netwrork of R1: 10.0.96.0/24