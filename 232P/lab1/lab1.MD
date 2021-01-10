- datagram vs packets vs frame vs segment
    - https://networkengineering.stackexchange.com/questions/50083/what-are-the-differences-in-the-contents-of-datagrams-frames-and-network-packe#:~:text=I%20know%20that%20datagrams%20are,as%20a%20payload%20of%20data.
    - https://i.stack.imgur.com/6dKkj.gif
    - http://www.practicalnetworking.net/series/packet-traveling/osi-model/#osi-layer-23

- higher lever 5,6,7 OSI (application leyer TCP/IP) details

- tcp vs udp

- ping: https://linux.die.net/man/8/ping
    - icmp: internet control message protocol - error reporting protocol used by network devices like routers.
    - https://searchnetworking.techtarget.com/definition/ICMP#:~:text=ICMP%20(Internet%20Control%20Message%20Protocol)%20is%20an%20error%2Dreporting,prevent%20delivery%20of%20IP%20packets.

- arp: discovering link layer mac address associated with internet layer ipv4/6

- config
    - router server: gns3 vm

- commands
    - router
        - current router running configuration
            ```
            show running-config
            show interface
            ```
        - set ip address, for ethernet(lan) and serial(wan) interface
            ```
            Router1# config term
            Router1 (config)# interface FastEthernet0/0 
            Router1 (config-if)# ip address 10.0.1.1 255.255.255.0
            Router1 (config-if)# no shutdown
            Router1 (config-if)# interface Serial2/0 
            Router1 (config-if)# ip address 10.0.2.1 255.255.255.0
            Router1 (config-if)# no shutdown
            Router1 (config-if)# exit
            Router1 (config)# exit
            ```
    - pc
        - set ip
            ```
            PC1$ sudo ip addr flush dev eth0
            PC1$ sudo ip addr add 10.0.1.11/24 dev eth0
            ```
        - disable ping
            ```
            PC1$ sudo sh -c 'echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_all'
            ```
            or
            ```
            PC1$ sudo sysctl -w net.ipv4.icmp_echo_ignore_all=1
            ```