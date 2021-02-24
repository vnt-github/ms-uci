from socket import inet_ntoa
from struct import pack

router_interface_mapping = {
    'e0': 'f0/0',
    'e1': 'f1/0',
    'e3': 'f3/0',
    's0': 's2/0',
    's1': 's2/1'
}

def routerInterface(interface):
    global router_interface_mapping
    return router_interface_mapping.get(interface.lower(), interface)

pc_interface_mapping = {
    'e0': 'eth0',
    'e1': 'eth1'
}
def pcInterface(interface):
    return pc_interface_mapping.get(interface.lower(), interface)

def calcDottedNetmask(mask):
    mask = int(mask)
    bits = 0
    for i in range(32-mask,32):
        bits |= (1 << i)
    return inet_ntoa(pack('>I', bits))

def getMask(cidr_prefix):
    if isinstance(cidr_prefix, int) or cidr_prefix.isdigit():
        mask = calcDottedNetmask(cidr_prefix)
    return mask

def mac2ipv6(mac):
    # only accept MACs separated by a colon
    parts = mac.split(":")

    # modify parts to match IPv6 value
    parts.insert(3, "ff")
    parts.insert(4, "fe")
    parts[0] = "%x" % (int(parts[0], 16) ^ 2)

    # format output
    ipv6Parts = []
    for i in range(0, len(parts), 2):
        ipv6Parts.append("".join(parts[i:i+2]))
    ipv6 = "fe80::%s/64" % (":".join(ipv6Parts))
    return ipv6

def ipv62mac(ipv6):
    # remove subnet info if given
    subnetIndex = ipv6.find("/")
    if subnetIndex != -1:
        ipv6 = ipv6[:subnetIndex]

    ipv6Parts = ipv6.split(":")
    macParts = []
    for ipv6Part in ipv6Parts[-4:]:
        while len(ipv6Part) < 4:
            ipv6Part = "0" + ipv6Part
        macParts.append(ipv6Part[:2])
        macParts.append(ipv6Part[-2:])

    # modify parts to match MAC value
    macParts[0] = "%02x" % (int(macParts[0], 16) ^ 2)
    del macParts[4]
    del macParts[3]

    return ":".join(macParts)

# ipv6 = mac2ipv6("52:74:f2:b1:a8:7f")
# back2mac = ipv62mac(ipv6)
# print "IPv6:", ipv6    # prints IPv6: fe80::5074:f2ff:feb1:a87f/64
# print "MAC:", back2mac # prints MAC: 52:74:f2:b1:a8:7f