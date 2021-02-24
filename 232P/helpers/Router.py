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

def disable_cdp():
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

def show_route_cache():
    return f"""show ip cache"""

"""
config term
ip route 0.0.0.0 0.0.0.0 10.0.2.2
end
show ip route
"""
def add_default_route_ip4(next_router_ip):
    return f"""
{enable_routing_cache()}
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



if __name__ == "__main__":
    # print(disable_cdp())
    # print(set_interface_ip4("s0", "10.0.1.1", 24))
    # print(set_interface_ip4("eth0", "10.0.1.1", 24))

    # print(set_interface_ip4("e0", "10.0.1.1", 24))
    # print(set_interface_ip4("s0", "10.0.1.1", "24"))
    # print(set_interface_ip4("e1", "10.0.1.1", "255.255.255.0"))
    # print(add_route_ip4("10.3.1.0", 24, "10.2.1.0"))
    # print(add_route_ip4("10.2.1.0", 24, "eth0"))


    # lab3
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
    # # print(add_route_ip4("10.0.3.0", "24", "10.0.2.1"))
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