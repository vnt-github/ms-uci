from utils import routerInterface as getInterface, calcDottedNetmask, getMask

def show_mac():
    return f"""show interfaces | i (.* line protocol is )|(.* address is)"""

def show_route_ip4():
    return f"show ip route"

def  show_route_ip6():
    return f"show ipv6 route"

def show_interface_ip4():
    return f"show ip interface brief"

def show_interface_ip6():
    return f"show ipv6 interface brief"

def disable_cdp_loop():
    return f"""
config term
no cdp run
interface f0/0
no keepalive
interface f1/0
no keepalive
interface s2/0
no keepalive
interface s2/1
end
"""

def save_config():
    return f"""
config term
copy running-config starting-config
end
"""

# privileged EXEC (default one)
def show_arp_cache():
    return f"show ip arp"

def flush_arp_cache():
    # return f"clear arp-cache" # this does not delete entries in neigh cache, Refreshes the ARP cache by issuing ARP Requests for each entry in the cache.
    return f"""
config term
interface f0/0
shutdown
interface f1/0
shutdown
interface s2/0
shutdown
interface s2/1
shutdown
end

show arp

config term
interface f0/0
no shutdown
interface f1/0
no shutdown
interface s2/0
no shutdown
interface s2/1
no shutdown
end

show arp
"""

def flush_routing_table():
    return f"""
config term
no ip routing
ip routing
end
"""

# same as above: Deletes all IPv4/IPv6 routing table entries
def clear_routing_table():
    return f"""
clear ip route *
clear ipv6 route *
"""

# privileged EXEC (default one)
def show_forwarding_status():
    return f"""
show protocols
"""

"""
configure terminal
no ip routing for disabling IP forwarding and resetting routing table
ip routing # for enabling IP forwarding
interface f0/0
ip address 10.0.2.1 255.255.255.0
no shutdown
interface f1/0
ip address 10.0.3.1 255.255.255.0
no shutdown
end
show ip interface brief
"""
def set_interface_ip4(interface, ip_address, cidr_prefix):
    return f"""
config term
no ip routing
ip routing
interface {getInterface(interface)}
ip address {ip_address} {getMask(cidr_prefix)}
no shutdown
end
{show_interface_ip4()}
"""

"""
configure terminal
ip route 10.0.1.0 255.255.255.0 10.0.2.2
end
show ip route
"""
def add_route_ip4(destination, cidr_prefix, interface_or_next_router_ip):
    return f"""
{enable_routing_cache()}
config term
ip route {destination} {getMask(cidr_prefix)} {getInterface(interface_or_next_router_ip)}
end
{show_route_ip4()}
"""

"""
configure terminal
no ip route 10.0.1.0 255.255.255.0 10.0.2.2
end
show ip route
"""
def del_route_ip4(destination, cidr_prefix, interface_or_next_router_ip):
    return f"""
config term
no ip route {destination} {getMask(cidr_prefix)} {getInterface(interface_or_next_router_ip)}
end
{show_route_ip4()}
"""

"""
configure terminal
interface f0/0
ip proxy-arp
end
configure terminal
interface f1/0
ip proxy-arp
end
"""
def enable_proxy_arp(interface):
    return f"""
config term
interface {getInterface(interface)}
ip proxy-arp
end
"""

def disable_proxy_arp(interfaces):
    interfaces_cmmd = ''.join([f"""
interface {getInterface(interface)}
no ip proxy-arp
""" for interface in interfaces])

    return f"""
config term
{interfaces_cmmd}
end
"""

def show_route_cache():
    return f"""show ip cache"""

"""
config term
ip route 0.0.0.0 0.0.0.0 10.0.2.2
end
show ip route
"""
def add_default_route_ip4(next_router_ip):
# {enable_routing_cache()}
    return f"""
config term
ip route 0.0.0.0 0.0.0.0 {next_router_ip}
end
{show_route_ip4()}
"""

"""
config term
ipv6 route ::/0 f0/0 fd15:8f7e:158f:ab02::1
end
show ip route
"""
def add_default_route_ip6(interface, next_router_ip):
    return f"""
config term
ipv6 route ::/0 {getInterface(interface)} {next_router_ip}
end
{show_route_ip6()}
"""

"""
configure terminal 
interface f0/0
ipv6 address fd01:2345:6789:2::1/64
no shutdown
interface f1/0
ipv6 address fd01:2345:6789:3::1/64
no shutdown
exit
ipv6 unicast-routing
end
"""
def set_interface_ip6(interface, ip_address, cidr_prefix=64):
    return f"""
configure terminal 
interface {getInterface(interface)}
ipv6 address {ip_address}/64
no shutdown
exit
ipv6 unicast-routing
end
{show_interface_ip6()}
"""

def del_interface_ip6(interface, ip_address, cidr_prefix=64):
   return f"""
configure terminal 
interface {getInterface(interface)}
no ipv6 address {ip_address}/64
no shutdown
exit
ipv6 unicast-routing
end
{show_interface_ip6()}
""" 

def enable_unicast_routing():
    return f"""
config term
ipv6 unicast-routing
end
"""

"""
config term
ipv6 route fd01:2345:6789:1::/64 f0/0 fd01:2345:6789:2::22
"""
def add_route_ip6(destination_ntw, interface, next_router_ip):
    return f"""
config term
ipv6 route {destination_ntw} {getInterface(interface)} {next_router_ip}
end
{show_route_ip6()}
"""

"""
config term
interface FastEthernet0/0
no ip route-cache
ip route-cache
interface FastEthernet1/0
no ip route-cache
ip route-cache
end
show ip cache
"""
def enable_routing_cache():
    return f"""
config term
interface f0/0
no ip route-cache
ip route-cache
interface f1/0
no ip route-cache
ip route-cache
interface s2/0
no ip route-cache
ip route-cache
interface s2/1
no ip route-cache
ip route-cache
end
show ip cache
"""

def traceroute(destination):
    return f"""trace {destination}"""

def show_routing_config():
    return f"show ip protocols"

def enable_debugging_rip():
    return f"debug ip rip"

def disable_debugging_rip():
    return f"no {enable_debugging_rip()}"

def enable_rip():
    return f"""
config term
router rip
exit
"""

def disable_rip():
    return f"""
config term
no router rip
exit
"""

# THE SUBNET IS ALWAYS 24, use end 0s for subnets
# https://learncisco.net/courses/icnd-1/ip-routing-technologies/enabling-rip.html
# https://learningnetwork.cisco.com/s/question/0D53i00000Kt6cX/rip-timers
def setup_rip(network, update_sec='', invalid_sec='', hold_sec='', flush_sec=''):
    return f"""
config term
router rip
version 2
network {network}
timers basic {update_sec} {invalid_sec} {hold_sec} {flush_sec}
end
"""

# offset-list 0 in 10 f0/0
def set_rip_offset(interface, in_out, value):
    return f"""
config term
router rip
offset-list 0 {in_out} {value} {getInterface(interface)}
end
"""
# no offset-list 0 in 10 f0/0
def unset_rip_offset(interface, in_out, value):
    return f"""
config term
router rip
no offset-list 0 {in_out} {value} {getInterface(interface)}
end
"""

# Triggered updates are disabled by setting the flash-update-threshold timer to the same value as the update timer(default=30s).
def disable_trigger_update(time=30):
    return f"""
config term
router rip
flash-update-threshold {time}
end
"""

# IOS: privileged EXEC
def ospf_config():
    return f"show ip ospf"

def show_ospf_routes():
    return f"show ip route ospf"

def show_ospf_db():
    return f"show ip ospf database"

def show_ospf_netork_link_state():
    return f"show ip ospf database network"

def show_ospf_router_link_state():
    return f"show ip ospf database router"

def ospf_passive(interface):
    return f"""
config term
passive-interface {getInterface(interface)}
end
"""

def ospf_active(interface, area=1):
    return f"""
config term
router ospf {area}
no passive-interface {getInterface(interface)}
end
"""

# NOTE: id can only be a valid ipv4 address
def ospf_router_id(id, area=1):
    return f"""
config term
router ospf {area}
router-id {id}
end
"""

# INVERT NET MASK http://saloperie.com/docs/mask.html
# Router1# configure terminal
# Router1(config)# no ip routing
# Router1(config)# ip routing
# Router1(config)# router ospf 1
# Router1(config-router)# network 10.0.0.0 0.255.255.255 area 1
# Router1(config-router)# end
def setup_ospf(network, mask, area=1):
    return f"""
config term
router ospf 1
network {network} {getMask(mask, True)} area {area}
end
"""

def set_ospf_metric(interface, value):
    return f"""
config term
interface {getInterface(interface)}
ip ospf cost {value}
end
show ip ospf interface
"""

def show_bgp_routes():
    return f"show ip bgp"

def show_bgp_peers():
    return f"show ip bgp neighbors"

def show_bgp_paths():
    return f"show ip bgp paths"

def flush_bgp_routes():
    return f"clear ip bgp *"

def set_bgp_timers(as_id, keep_alive=60, hold_time=180):
    return f"""
config term
router bgp {as_id}
timers bgp {keep_alive} {hold_time}
end
"""

def setup_bgp(as_id, adv_networks, neighbors):
    neighbors_add_commands = '\n'.join([f'neighbor {ip} remote-as {as_id}'  for ip, as_id in neighbors])
    next_hop_self = '\n'.join([f'neighbor {ip} next-hop-self'  for ip, as_id in neighbors])
    network_adv_commands = '\n'.join([f'network {network} mask {getMask(mask)}' for network, mask in adv_networks])
    return f"""
config term
router bgp {as_id}
{neighbors_add_commands}
{next_hop_self}
{network_adv_commands}
end
show ip bgp summary
"""

def show_bgp_session_to_peers():
    return "show ip bgp summary"

def show_bridge_mac_table(group=1):
    return f"show bridge {group}"

def show_spanning_tree():
    return f"show spanning-tree"


# config term
# ip prefix-list MYLIST permit 10.0.1.0/24
# ip prefix-list MYLIST permit 10.0.3.0/24
# router bgp 300
# neighbor 10.0.10.1 prefix-list MYLIST in
# neighbor 10.0.10.2 prefix-list MYLIST in
# end
# clear ip bgp *
# show ip bgp
# show ip route
def bgp_selective_transit(allow_networks, to_apply_neigh_networks, as_id, list="MYLIST"):
    alow_network_cmds = '\n'.join([f'ip prefix-list {list} permit {ntw}' for ntw in allow_networks])
    apply_list_cmds = '\n'.join([f'neighbor {ntw} prefix-list {list} in' for ntw in to_apply_neigh_networks])
    return f"""
config term
{alow_network_cmds}
router bgp {as_id}
{apply_list_cmds}
end
clear ip bgp *
show ip bgp
show ip route
"""

def disable_bridge(group=1):
    return f"""
config term
no bridge {group}
end"""

def flush_bridge_mac_table():
    return f"clear bridge"

def flush_arp_cache():
    return f"clear arp-cache"


# Router1# configure terminal
# Router1(config)# no ip routing 
# Router1(config)# no cdp run
# Router1(config)# bridge 1 protocol ieee
# Router1(config)# bridge 1 priority 128
# Router1(config)# interface FastEthernet0/0
# Router1(config-if)# no keepalive # to stop LOOP cisco messages
# Router1(config-if)# bridge-group 1
# Router1(config-if)# bridge-group 1 spanning-disabled
# Router1(config-if)# no shutdown
# Router1(config-if)# interface FastEthernet1/0
# Router1(config-if)# no keepalive
# Router1(config-if)# bridge-group 1
# Router1(config-if)# bridge-group 1 spanning-disabled
# Router1(config-if)# no shutdown
# Router1(config-if)# end
# Router1# clear bridge
# Router1# clear arp-cache
def setup_bridge(interfaces, group=1, priority=128, spanning_tree=True):
    interface_commands = ''.join([f"""
interface {getInterface(each)}
no keepalive
bridge-group {group}
{"no" if spanning_tree else ''} bridge-group {group} spanning-disabled
no shutdown    
""" for each in interfaces])

    return f"""
config term
no ip routing
no cdp run
bridge {group} protocol ieee
bridge {group} priority {priority}
{interface_commands}
end
clear bridge
clear arp-cache
"""

def make_bridge_root(group=1, lowest_priority=4):
    return f"""
config term
bridge {group} priority {lowest_priority}
end
"""

def set_interface_mtu(interface, size):
    return f"""
config term
interface {getInterface(interface)}
mtu {size}
end
show interfaces
"""

# CAN'T BE SET FOR ETHERNETs but with SERIALS
def set_data_rate(interface, rate_bps=1200):
    return f"""
config term
interface {getInterface(interface)}
clock rate {rate_bps}
end
"""

if __name__ == "__main__":
    # print(disable_cdp_loop())
    # print(set_interface_ip4("s0", "10.0.1.1", 24))
    # print(set_interface_ip4("eth0", "10.0.1.1", 24))

    # print(set_interface_ip4("e0", "10.0.1.1", 24))
    # print(set_interface_ip4("s0", "10.0.1.1", "24"))
    # print(set_interface_ip4("e1", "10.0.1.1", "255.255.255.0"))
    # print(add_route_ip4("10.0.3.0", 24, "10.0.2.1"))
    # print(add_route_ip4("10.2.1.0", 24, "eth0"))


    # lab 3
    # both before
    # print(flush_arp_cache())
    # # ROUTER1
    # print(set_interface_ip4("e0", "10.0.2.1", 24))
    # print(set_interface_ip4("e1", "10.0.3.1", 24))
    # print(add_route_ip4("10.0.1.0", "24", "10.0.2.2"))
    # # print(traceroute("10.0.1.11"))
    # print(add_default_route_ip4("10.0.2.2"))

    # # # ROUTER2
    # print(set_interface_ip4("e0", "10.0.1.2", 24))
    # print(set_interface_ip4("e1", "10.0.2.2", 24))
    # print(add_route_ip4("10.0.3.0", "24", "10.0.2.1"))
    # print(add_default_route_ip4("10.0.2.1"))

    # # ROUTER 1
    # print(enable_proxy_arp("e0"))
    # print(enable_proxy_arp("e1"))
    # print(set_interface_ip4("e0", "10.0.1.2", "24"))
    # print(set_interface_ip4("e1", "10.0.2.138", "24"))

    # QUIZ 1.
    # print(set_interface_ip6("e0", "fd01:2345:6789:2::1", "64"))
    # print(set_interface_ip6("e1", "fd01:2345:6789:3::1", "64"))
    # print(add_route_ip6("fd01:2345:6789:1::/64", "e0", "fd01:2345:6789:2::2"))

    
    # print(set_interface_ip6("e0", "fd01:2345:6789:1::2", "64"))
    # print(set_interface_ip6("e1", "fd01:2345:6789:2::2", "64"))
    # print(add_route_ip6("fd01:2345:6789:3::/64", "e1", "fd01:2345:6789:2::1"))

    # GNS3 example slides
    # R1
    # print(set_interface_ip4("e0", "10.0.1.1", "24"))
    # print(set_interface_ip4("e1", "10.0.2.1", "24"))
    # print(add_default_route_ip4("10.0.2.2"))

    # R2
    # print(set_interface_ip4("e0", "10.0.2.2", "24"))
    # print(set_interface_ip4("e1", "10.0.3.2", "24"))
    # print(add_default_route_ip4("10.0.2.1"))

    # MY ipv6 subnet example
    # # # R1
    # print(set_interface_ip6("e0", "fd15:8f7e:158f:ab00::1", "63"))
    # print(set_interface_ip6("e1", "fd15:8f7e:158f:ab02::1", "63"))
    # print(add_default_route_ip6("e1", "fd15:8f7e:158f:ab02::2"))
    # R2
    # print(set_interface_ip6("e0", "fd15:8f7e:158f:ab02::2", "63"))
    # print(set_interface_ip6("e1", "fd15:8f7e:158f:ab04::1", "63"))
    # print(add_default_route_ip6("e0", "fd15:8f7e:158f:ab02::1"))

    # R1
    # print(set_interface_ip4("e0", "66.45.1.1", "24"))
    # print(set_interface_ip4("e1", "66.45.2.1", "24"))
    # print(add_default_route_ip4("66.45.2.3"))

    # # R2
    # print(set_interface_ip4("e0", "66.45.1.2", "24"))
    # print(set_interface_ip4("e1", "66.45.3.2", "24"))
    # print(add_default_route_ip4("66.45.1.1"))

    # R3
    # print(set_interface_ip4("e0", "66.45.2.3", "24"))
    # print(set_interface_ip4("e1", "66.45.3.3", "24"))
    # print(add_default_route_ip4("66.45.2.1"))
    
    # LAB 4
    # R1
    # print(set_interface_ip4("e0", "10.0.1.1", "24"))
    # print(set_interface_ip4("e1", "10.0.2.1", "24"))

    # R2
    # print(set_interface_ip4("e0", "10.0.3.2", "24"))
    # print(set_interface_ip4("e1", "10.0.2.2", "24"))
    
    # R3
    # print(set_interface_ip4("e0", "10.0.3.3", "24"))
    # print(set_interface_ip4("e1", "10.0.4.3", "24"))
    
    # R1, R2 and R3
    # print(setup_rip("10.0.0.0"))

    # R4
    # print(set_interface_ip4("e0", "10.0.1.33", "24"))
    # print(set_interface_ip4("e1", "10.0.3.33", "24"))

    # print(setup_rip("10.0.0.0", 10, 60, 60, 80))

    # R5
    # print(set_interface_ip4("e0", "10.0.2.4", "24"))
    # print(set_interface_ip4("e1", "10.0.4.4", "24"))

    # print(setup_ospf("10.0.0.0", "8"))

    # print(set_ospf_metric("e0", 1))

    # BGP
    
    # network network-number [mask network-mask ] [route-map route-map-name ]

    # Example:

    # Device(config-router)# network 10.1.1.0 mask 255.255.255.0
    # (Optional) Specifies a network as local to this autonomous system and adds it to the BGP routing table.

    # For exterior protocols, the network command controls which networks are advertised. Interior protocols use the network command to determine where to send updates

    # R1
    # print(set_interface_ip4("e0", "10.0.1.1", "24"))
    # print(set_interface_ip4("e1", "10.0.10.1", "24"))
    # print(setup_bgp(100, [
    #     ("10.0.1.0", 24)
    # ], [
    #     ("10.0.10.2", 200),
    #     ("10.0.10.33", 300),
    # ]))

    # R2
    # print(set_interface_ip4("e0", "10.0.2.2", "24"))
    # print(set_interface_ip4("e1", "10.0.10.2", "24"))
    # print(setup_bgp(200, [
    #     ("10.0.2.0", 24)
    # ], [
    #     ("10.0.10.1", 100),
    #     ("10.0.10.33", 300),
    # ]))

    # R3
    # print(set_interface_ip4("e0", "10.0.3.3", "24"))
    # print(set_interface_ip4("e1", "10.0.20.3", "24"))
    # print(setup_bgp(300, [
    #     ("10.0.3.0", 24),
    #     ("10.0.20.0", 24)
    # ], [
    #     ("10.0.20.4", 400),
    #     ("10.0.3.33", 300) # FINAL CONFIG NEEDS THIS
    # ]))

    # R4
    # print(set_interface_ip4("e0", "10.0.4.4", "24"))
    # print(set_interface_ip4("e1", "10.0.20.4", "24"))
    # print(setup_bgp(400, [
    #     ("10.0.4.0", 24),
    #     ("10.0.20.0", 24) # redundant as r3 already publishes this but putting as a practice
    # ], [
    #     ("10.0.20.3", 300),
    # ]))

    # R5
    # print(set_interface_ip4("e0", "10.0.3.33", "24"))
    # print(set_interface_ip4("e1", "10.0.10.33", "24"))
    # print(setup_bgp(300, [
    #     # ("10.0.1.0", 24), NOTE: R5 DO NOT NEED TO advertise 10.0.1.0, router only need to advertise their connected interface subnets 
    #     # ("10.0.2.0", 24), NOTE: R5 DO NOT NEED TO advertise 10.0.2.0, router only need to advertise their connected interface subnets
    #      ("10.0.10.33", 24),
    #      ("10.0.3.33", 23)
    # ], [
    #     ("10.0.10.1", 100),
    #     ("10.0.10.2", 200),
    #     ("10.0.3.3", 300) # FINAL CONFIG NEEDS THIS
    # ]))
    
    # R5 iBGP
    # print(setup_bgp(300, [], [
    #     ("10.0.3.3", 300)
    # ]))
    
    # R3 iBGP
    # print(setup_bgp(300, [], [
    #     ("10.0.3.33", 300)
    # ]))

    # print(bgp_selective_transit(["10.0.1.0/24", "10.0.3.0/24"], ["10.0.10.1", "10.0.10.2"], 300))

    #  LAB 5
    # R1 & R4
    # print(setup_bridge(["e0", "e1"]))

    # R2
    # print(set_interface_ip4("e0", "10.0.3.2", "24"))
    # print(set_interface_ip4("e1", "10.0.1.2", "24"))
    # print(add_default_route_ip4("10.0.3.3"))
    # print(disable_proxy_arp(["e0", "e1"]))

    # # R3
    # print(set_interface_ip4("e0", "10.0.3.3", "24"))
    # print(set_interface_ip4("e1", "10.0.4.3", "24"))
    # print(add_default_route_ip4("10.0.3.2"))
    # print(disable_proxy_arp(["e0", "e1"]))

    # LAB 6
    # # R1
    # print(set_interface_ip4("e0", "10.0.1.1", "24"))
    # print(set_interface_ip4("s0", "10.0.2.1", "24"))
    # print(add_default_route_ip4("10.0.2.2"))
    # print(disable_cdp_loop())

    # # R2
    # print(set_interface_ip4("e0", "10.0.3.1", "24"))
    # print(set_interface_ip4("s0", "10.0.2.2", "24"))
    # print(add_default_route_ip4("10.0.2.1"))
    # print(disable_cdp_loop())

    # R1
    # print(set_interface_ip6("e0", "fd01:2345:6789:1::1", "64"))
    # print(set_interface_ip6("s0", "fd01:2345:6789:2::1", "64"))
    # print(add_default_route_ip6("e0", "fd01:2345:6789:2::2"))
    # print(add_default_route_ip6("s0", "fd01:2345:6789:2::2"))
    # print(disable_cdp_loop())
    # print(set_interface_mtu("s0", 1280))

    # R2
    # print(set_interface_ip6("e0", "fd01:2345:6789:3::1", "64"))
    # print(set_interface_ip6("s0", "fd01:2345:6789:2::2", "64"))
    # print(add_default_route_ip6("e0", "fd01:2345:6789:2::1"))
    # print(add_default_route_ip6("s0", "fd01:2345:6789:2::1"))
    # print(disable_cdp_loop())
    # print(set_interface_mtu("s0", 1280))

    # print(ospf_active("e0"))
    # print(ospf_router_id("1.2.3.4"))
    # print(set_data_rate("s0", 1200))