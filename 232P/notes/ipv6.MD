- ipv6: 8,4 digits hexs = 32 hex digits = 128 bits = 2^7 bits
    - THERER ARE DIFFERENT TYPES BECAUSE, USE OF ADDRESSES DEPDENDING UPON TYPE OF NTW, LIKE HOME NTW DON"T NEED GLOBAL UNIQUE ADDRESSES(like sensors only need link-local).
    - link-local(like mac ARP and LOCAL SUBNET NTW): fe80::/10
        - prefix: fe80::/10, fe80::/64 (with subnet till 64 bits)
        - not forwarded by routers in btw ntws, ie. it's packets are local to subnet.
        - all devices reads FE80 packets, its  is necessary even if node has global unicast address.
        - used for NDP(solicitation and advertisements), used for multicast listening,  
        - zone index: %eth0 or %1, is used as all link-local(fe80::) have same network prefix so sender don’t know which interface to use.
            - it cant uses ntw prefix(fe80::) to match destination to interface from ROUTING TABLE.
        - prefix = (fe80:0:0:0)/64 + (d875:56ff:fe4d:2d82 EUI-64 host id from mac) /64.
            - flip 7th get bin = bin(int('CA', 16)) flip the 7th and hex(int('flipped_bin', 2))
    
    -  unique-local(like 10.0.0.0/8 PRIVATE NTW): fc00::/7
        - prefix: fd00::/7 (c is not found in the wild as 1 is always set to identify that the global id is locally assigned and defined).
        - only routed by routers in btw LOCAL ntw, ie. not routed over internet.
        - prefix = (fd + (global_id 10 hex digits(40 bits))/48 bits + ---> subnet 4 hex digits(16 bits)/64) + interface_id = (--->64 bits HEX(host no))
            - for ex: 40 bits or 10 hex digits = 158f7e158f and subnet number 3 make host unique-local for host no 103
                - fd15:8f7e:158f:3::67/64

    - global unicast(GLOBAL NTW): 2000::/3 - 2000::/12
        - always /64, need to have 64 bit interface IDs (EUI-64 from MAC)

        - prefix = (global_id + [:0:0:] + --->/64 bits HEX(subnet no)) +  interface_id = (--->/64 bits HEX(host_no))
            - for ex: 2600::/12 global prefix create global host address with host no 10 with subnet no 15
                - 2600:0:0:f::A/64
        - after pings the link-locals node solicitation and adv also occurese automatically on both sides PC1 -> PC2 and PC2 -> PC1.

    - multicast messages are ff00::/8
        - solicited node multicast destination for node solicitation is ff02::1:ff__:__:__(last 3 bytes ie 24 bits from dst).
            - mac is 33:33:ff:__:__:__(last 3 bytes ie 24 bits from dst)
            - every host interface listens to their respective solicited node multicast addresses when they get up.
        - ff02:2: is the dest address for multicast to all IPV6 Routers.
        - ff02::16: is the address which reacches all IPV6 Router that interpret MLDv2 messages.
        - ff02::1 is the dest address for multicast to all nodes.
- Duplicate Address Detection: causes dadfailed tentative on duplicate address on same subnet.

- reserved
    - ::/128 = not assigned, absence of an address, unspecified, = all zeros
    - ::1/128 = loopback = only last bit 1.
    - 1607:f2c0:9272::/48 = anycast address = interface all zeros
    - largest 128 addresses on subnet: resrved for anycast addresses for host servers.