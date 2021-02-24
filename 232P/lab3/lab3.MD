- Lec-Jan20/21-part1 covers it mostly.

- traceroute: https://en.wikipedia.org/wiki/Traceroute
    - used to check the route by firing UDPs with increasing ttl
    - returns the latency in ms
    - usage `traceroute --help | less`
        - `traceroute --wait=3 --max-hop=64 --tries=3 example.com`

- proxy arp: https://www.practicalnetworking.net/series/arp/proxy-arp/
    - we simulated this by making address from PC3 from 10.0.3.33/24 to 10.0.3.33/8 and pinging PC1.
    - Proxy ARP occurs when one node is responding to an ARP request on behalf of another node.
    - inconfigured PC tries to arp broadcast to outof network destination, then router acts as proxy on behalf of destination.
    - no arp message forwarding occures from router.
    - from lab3 step 5
        - PC3(misconfigured host) arp braodcast for PC1.
        - router1(PC3 ntw router with proxy-arp enabled) replies it's own mac as PC1's.
        - neighbour cache for PC3 adds entry for PC1 ip with router1 mac. the same is in the ARP reply.
        - but the router forwards the ICMP messages.
        - adds so much load on router, so not scalable and misconfigured host should be corrected.
        - for Network Address Translation(NAT) to work properly, the translation device must use Proxy ARP to properly receive packets to be translated.

- ip routing: http://linux-ip.net/html/tools-ip-route.html
    - search this via keyword

- ip forwarding
    - mating the incomming interface/port to each incomming packet.

- FastEthernet1/0 is port 0 of card in slot 1 of the router.

- ICMP Redirects are by router: https://www.cisco.com/c/en/us/support/docs/ip/routing-information-protocol-rip/13714-43.html#:~:text=ICMP%20redirect%20messages%20are%20used,configured%20to%20use%20router%20R1.
    - occurs when host has multiple routers directly on ntw but for a particular host uses the wrong of less suitable router.
    - in lab done by setting PC2 default to Router2 and quering PC3 which is behing Router1.
    - flow is correct in the lab3.docs
        - router 2 acts forwards requests till pc2 updates it's destination
        - router 2 does not forwards the respose, as the router1 sends response directly to PC2.
        - the destination is provided in the ICMP redirect reply's gateway address field.(Gateway address: 10.0.2.1)

- auto configuration
    - if PC1 knows already mac for router 2 then on ping to PC3.
        - PC1 does not neigh soliciatated, But after 1 ping is received by Router2 from new PC1's unique local address, router2 does the neigh solicitate for new unique local address for PC1
    - after flushing PC1 does not know mac for router so before pinging the PC1 solicates for mac for Router 2 twice one for link-local and other for unique local address.

- NDP is Application layer: it is a network application, transported via ICMP protocol over IP. 
- ARP is in layer btw Network and Data link layer: it is transported via data link layer.