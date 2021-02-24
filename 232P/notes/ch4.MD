- router replies to it's own neigh solicitation with neigh adv if no one else replies.

- ICMP:
    - ipv4:
        - echo req: 8/0 , echo reply: 0/0
        - router solicitation: 10/0, router advertisement: 9/0

- ICMP redirects only work after enabling to accept forwarding redirects(for ipv4)
    - it only updates the routing cache not the routing table.

- ff01::1 is the router advertisement multicast for all nodes.
- ff01::2 is the router solicitation mulitcast for all routers.