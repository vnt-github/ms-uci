from typing import DefaultDict
from utils import pcInterface as getInterface, calcDottedNetmask, getMask

"""
sudo ip link set dev eth0 down
sudo ip link set dev eth0 address aa:8d:db:2b:20:40
sudo ip link set dev eth0 up
sudo ip addr show dev eth0
"""
def set_mac_addr(interface, addr):
    return f"""
sudo ip link set dev {getInterface(interface)} down
sudo ip link set dev {getInterface(interface)} address {addr}
sudo ip link set dev {getInterface(interface)} up    
sudo ip addr show dev {getInterface(interface)}
"""

"""
sudo ip addr flush dev eth0
sudo ip addr add 10.0.1.11/24 dev eth0
sudo ip addr add fd01:2345:6789:1::11/64 dev eth0
sudo ip addr show dev eth0
"""
# BOTH IPV4 and IPV6
def set_interface(interface, ip_address, cidr_prefix):
    return f"""
{flush_arp_cache()}
sudo ip addr flush dev {getInterface(interface)}
sudo ip addr add {ip_address}/{cidr_prefix} dev {getInterface(interface)}
sudo ip addr show dev {getInterface(interface)}
"""

def show_route_cache():
    return f"""sudo ip route show cache
"""

def flush_arp_cache():
    return f"sudo ip neigh flush all"

def flush_route_cache():
    return f"""sudo ip route flush cache
{show_route_cache()}
"""

def add_default_route_ip4(next_router_ip):
    return f"""
{flush_arp_cache()}
{flush_route_cache()}
sudo ip route add default via {next_router_ip}
{show_routes_ip4()}
"""

def del_default_route_ip4():
    return f"""
sudo ip route del default
{show_routes_ip4()}
{flush_arp_cache()}
{flush_route_cache()}
"""

"""
sudo ip route add 10.0.0.0/16 via 10.0.1.71
sudo ip route add 10.0.3.9 via 10.0.1.81
# above is /32 by default and is called host route.
sudo ip route add default via 10.0.1.91
"""
def add_static_route_ip4(destination_ntw, next_router_ip):
    return f"""
{flush_arp_cache()}
{flush_route_cache()}
sudo ip route add {destination_ntw} via {next_router_ip}
{show_routes_ip4()}
"""

"""
sudo ip route del 10.0.2.0/24 
"""
def del_static_route_ip4(destination_ntw):
    return f"""
sudo ip route del {destination_ntw}
{show_routes_ip4()}
{flush_arp_cache()}
{flush_route_cache()}
"""

def flush_interface_routes(interface):
    return f"""
sudo ip link set dev {getInterface(interface)} down
sudo ip link set dev {getInterface(interface)} up
{flush_arp_cache()}
{flush_route_cache()}
"""

# or sudo ip route show
def show_routes_ip4():
    return f"""netstat -rn"""

# netstat -rn -6 route 
def show_routes_ip6():
    return f"""netstat -rn -6"""

def show_ip_local_table():
    return f"""
ip route show table local
"""

def flush_routing_table():
    return f"""
sudo ip route flush
{show_routes_ip4()}
"""

def traceroute(destination):
    return f"""traceroute {destination}"""

def get_all_matches(destination):
    return f"sudo ip route show to match {destination}"

def get_match(destination):
    return f"sudo ip route get {destination}"


def show_arp_cache():
    return f"sudo ip neigh"

def set_icmp_redirects():
    return f"""
sudo sysctl -w net.ipv4.conf.all.accept_redirects=1
sudo sysctl -a | grep accept_redirects
"""

# ip neigh add 192.128.1.1 lladdr 1:2:3:4:5:2 dev eth1
def add_arp_entry(interface, destination, mac):
    return f"sudo ip neigh add {destination} lladdr {mac} dev {getInterface(interface)}"

# ip neigh add 192.128.1.1 lladdr 1:2:3:4:5:2 dev eth1
def del_arp_entry(interface, destination, mac):
    return f"sudo ip neigh del {destination} lladdr {mac} dev {getInterface(interface)}"

# ping6 -c2 IPv6_address_of_PC1
# traceroute6 IPv6_address_of_PC1

# OR sudo cat /etc/quagga/ripd.conf
def get_zebra_password():
    return f"sudo cat /etc/quagga/ospfd.conf"

# https://learningnetwork.cisco.com/s/question/0D53i00000Kt6cX/rip-timers
def setup_rip(network, prefix, interface):
    return f"""
sudo service zebra restart
sudo service ripd restart
telnet localhost 2602
zebra
enable
config term
router rip
version 2
network {network}/{prefix}
passive-interface {getInterface(interface)}
end
show ip rip
exit
netstat -rn
"""

def setup_ospf(network, prefix, interface, area=1):
    return f"""
sudo service zebra restart
sudo service ospfd restart
telnet localhost 2604
zebra
enable
config term
router ospf
network {network}/{prefix} area {area}
no passive-interface {getInterface(interface)}
end
show ip ospf interface
show ip ospf
exit
netstat -rn
"""

def disable_ip6():
    return f"""
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
"""
def enable_ip6():
    return f"""
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=0
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=0
"""

def disable_sack():
    return f'sudo sysctl -w net.ipv4.tcp_sack=0'

def set_mtu(interface, value):
    return f"sudo ip link set dev {getInterface(interface)} mtu {value}"

def send_data(bytessize, destination, port=10086, udp=False, ipv6=False):
    return f"""
rm -rf a.txt
for i in {{0..{bytessize}}}; do echo -n 'a' >> a.txt; done;
cat a.txt | nc {'-u' if udp else ''} {'-6' if ipv6 else ''} {destination} {port}
"""
def setup_nc_server(port=10086, udp=False, ipv6=False):
    return f"nc -l {'-u' if udp else ''} {'-6' if ipv6 else ''} {port}"

# DONE TO REDUCE THE PACKET SIZE TO OBSERVE FRAGMENTATION, and prevent fragmentation due to larger headers.
def disable_tcp_options():
    return f"""
sudo sysctl -w net.ipv4.tcp_timestamps=0
sudo sysctl -w net.ipv4.tcp_sack=0
"""

def enable_mtu_path_discover():
    return "sysctl -w net.ipv4.tcp_mtu_probing=2"

def set_mtu_expires(seconds):
    return f"sudo sysctl -w net.ipv6.route.mtu_expires={seconds}"

if __name__ == "__main__":
    # lab 3
    # PC1
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(add_default_route_ip4("10.0.1.2"))
    # print(set_icmp_redirects())
    # print(traceroute("10.0.3.33"))

    # print(add_static_route_ip4("10.0.0.0/16", "10.0.1.71"))
    # print(add_static_route_ip4("10.0.3.9", "10.0.1.81"))
    # print(del_default_route_ip4())
    # print(add_default_route_ip4("10.0.1.91"))

    # print(get_all_matches("10.0.3.9"))
    # print(get_all_matches("10.0.3.14"))
    # print(get_all_matches("10.0.4.1"))
    # print(get_all_matches("10.1.4.18"))

    # print(get_match("10.0.3.9"))
    # print(get_match("10.0.3.14"))
    # print(get_match("10.0.4.1"))
    # print(get_match("10.1.4.18"))

    # print(del_static_route_ip4("10.0.0.0/16"))
    # print(del_static_route_ip4("10.0.3.9"))
    # print(del_default_route_ip4())
    # print(add_default_route_ip4("10.0.1.2"))

    # PC2
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:02"))
    # print(set_interface("e0", "10.0.2.22", "24"))
    # print(add_default_route_ip4("10.0.2.2"))
    # print(set_icmp_redirects())

    # PC3
    # print(set_interface("e0", "10.0.3.33", "24"))
    # print(add_default_route_ip4("10.0.3.1"))
    # print(set_icmp_redirects())

    # print(flush_interface_routes("e0"))

    # PC4
    # print(set_interface("e0", "10.0.2.139", "24"))
    # print(add_default_route_ip4("10.0.2.138"))
    # print(set_icmp_redirects())

    # print(set_interface("e0", "fd15:8f7e:158f:3::0067", "64"))
    # print(set_interface("e0", "fd15:8f7e:158f:3::0068", "64"))
    # print(set_interface("e0", "fd15:8f7e:158f:3::0069", "64"))

    # GNS3 slides example
    # PC1
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(add_default_route_ip4("10.0.1.1"))

    # PC2
    # print(set_interface("e0", "10.0.3.22", "24"))
    # print(add_default_route_ip4("10.0.3.2"))
    
    # PC1
    # print(set_interface("e0", "66.45.1.11", "24"))
    # print(add_default_route_ip4("66.45.1.1"))


    # # PC2
    # print(set_interface("e0", "66.45.2.22", "24"))
    # print(add_default_route_ip4("66.45.2.3"))


    # # PC3
    # print(set_interface("e0", "66.45.3.33", "24"))
    # print(add_default_route_ip4("66.45.3.2"))

    # LAB4
    # PC1
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:11"))
    # print(set_interface("e0", "10.0.1.11", "24"))
    
    # PC4
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:44"))
    # print(set_interface("e0", "10.0.4.44", "24"))
    
    # RIP
    # PC1
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:11"))
    # print(set_interface("e0", "10.0.1.11", "24"))
    
    # [x] ONLY USE if if host not passive RIP
    # DOEST NOT UPDATE THE BETTER ROUTER EVEN ON ICMP_REDIRECT ENABLE
    # print(add_default_route_ip4("10.0.1.1"))

    # PC4
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:44"))
    # print(set_interface("e0", "10.0.4.44", "24"))
    
    # # [x]  ONLY USE if if host not passive RIP
    # DOEST NOT UPDATE THE BETTER ROUTER EVEN ON ICMP_REDIRECT ENABLE
    # print(add_default_route_ip4("10.0.4.3"))

    # print(setup_rip("10.0.0.0", "8", "e0"))
    
    # OSPF
    # print(setup_ospf("10.0.0.0", "8", "e0"))

    # BGP
    # PC1
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:11"))
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(add_default_route_ip4("10.0.1.1"))

    # PC2
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:22"))
    # print(set_interface("e0", "10.0.2.22", "24"))
    # print(add_default_route_ip4("10.0.2.2"))

    # PC4
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:44"))
    # print(set_interface("e0", "10.0.4.44", "24"))
    # print(add_default_route_ip4("10.0.4.4"))

    # LAB 5
    # PART 3
    # # PC2
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:22"))
    # print(set_interface("e0", "10.0.1.22", "24"))
    # print(disable_ip6())

    # # PC1
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:11"))
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(disable_ip6())
    # print(flush_arp_cache())
    # print(add_arp_entry("e0", "10.0.1.33", "aa:bb:cc:dd:ee:33"))
    # print(add_arp_entry("e0", "10.0.1.44", "aa:bb:cc:dd:ee:44"))

    # # PC3
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:33"))
    # print(set_interface("e0", "10.0.1.33", "24"))
    # print(disable_ip6())
    # print(flush_arp_cache())
    # print(add_arp_entry("e0", "10.0.1.11", "aa:bb:cc:dd:ee:11"))
    # print(add_arp_entry("e0", "10.0.1.44", "aa:bb:cc:dd:ee:44"))

    # # PC4
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:44"))
    # print(set_interface("e0", "10.0.1.44", "24"))
    # print(disable_ip6())
    # print(flush_arp_cache())
    # print(add_arp_entry("e0", "10.0.1.11", "aa:bb:cc:dd:ee:11"))
    # print(add_arp_entry("e0", "10.0.1.33", "aa:bb:cc:dd:ee:33"))
    

    # lAB 5 5-a
    # # PC1
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:11"))
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(add_default_route_ip4("10.0.1.2"))

    # PC2
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:22"))
    # print(set_interface("e0", "10.0.3.22", "24"))
    # print(add_default_route_ip4("10.0.3.2"))
    # print(set_icmp_redirects())

    # PC3
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:33"))
    # print(set_interface("e0", "10.0.4.33", "24"))
    # print(add_default_route_ip4("10.0.4.3"))

    # PC4
    # print(set_mac_addr("e0", "aa:bb:cc:dd:ee:44"))
    # print(set_interface("e0", "10.0.4.44", "16"))
    # print(add_default_route_ip4("10.0.4.3"))
    
    # print(disable_ip6())

    # LAB6
    # # PC1
    # print(set_interface("e0", "10.0.1.11", "24"))
    # print(add_default_route_ip4("10.0.1.1"))
    # print(disable_sack())

    # # PC2
    # print(set_interface("e0", "10.0.3.33", "24"))
    # print(add_default_route_ip4("10.0.3.1"))
    # print(disable_sack())

    # print(set_mtu("e0", 700))

    # print(disable_tcp_options())
    # print(set_mtu_expires(60))
    # print(send_data(800, "fd01:2345:6789:3:143c:40ff:fe03:b4bf", udp=True, ipv6=True))
    
    # print(setup_nc_server(udp=True))
    # print(send_data(1000000, "10.0.3.33"))