- spanning tree makes the smalles bridge id bridge the root.
- https://www.youtube.com/watch?v=NbY4vxIEv0U&ab_channel=danscourses

- Learning bridges that run the spanning tree protocol are called transparent bridges.  	

- bridge id(8 bytes length): (bytes 1 and 2 is priority) (byte 3-8 is lowest mac address of interface).
- BPDU(Bridge Protocol Data Units): shared every 4 seconds btw bridges of the same LAN(HUB).
- 
- The BPDU of a bridge advertises the best path from this bridge to the root bridge. Specifically, a BPDU (R, C, B, P).
    - R(8 bytes): root bridge id of the sender
    - C(4 bytes): cost of the path from sender to its root bridge
    - B(8 bytes): senderd bridge id
    - P(2 bytes): port where the best yes root info is got.
- “I am bridge B and I am sending from my port P. I believe R to be the root bridge, and the cost of my path to the root bridge is C.”
- sorting order for better lower is (R, C, B, P)


- designated bridge, which, among all bridges on the same LAN, has the best path to the root bridge
- The port that connects a bridge to the LAN where it is a designated bridge is called designated port

- stp: spanning tree protocol filter wireshark


- disconnecting the router router interface did'nt change the spanning tree root for me.
- changing priority did.