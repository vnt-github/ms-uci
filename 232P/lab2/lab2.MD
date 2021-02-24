- ip commands
    - https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print.pdf
    - https://baturin.org/docs/iproute2/
    - https://www.cyberciti.biz/faq/linux-ip-command-examples-usage-syntax/
- arp-ndp
    - https://docs.sophos.com/nsg/sophos-firewall/v17.0.0/Help/en-us/webhelp/onlinehelp/index.html#page/onlinehelp/ARPNDP.html

- link-local
    - https://www.omnisecu.com/tcpip/ipv6/link-local-ipv6-addresses.php


Yes, these are the expected output.

the reason for both of these failures is due to the out of range of the IPs defined by the PC1 and PC3's subnet, as shown below.

PC1 => 10.0.64.130/20 with host min IP = 10.0.64.1 and host max IP = 10.0.79.254

PC2 => 10.0.64.71/26 with host min IP = 10.0.64.65 and host max IP = 10.0.64.126 




now for PC1 to PC3 the ping request goes to the wire and reaches PC3 but PC3 can't reply cos the PC1 IP is higher than the host max IP of PC3 subnet.




for PC3 to PC1 the ping fails before it reaches the wire as the PC1 have IP larger that the host max IP.

- unique local address:
                        subnet = 16 bites
    - (fd01:2345:6789):(0001)::(1)/64
        global_id=4*4*3=48 bits host interface id =64 bits
- global unicast address:
    - global Id: fd15:8f7e:158f::/48
                            host interface id = 64 bits
    - (fd15:8f7e:158f):(0003)::(hex(105))
        global_id + subnet = 64 bits 

- loopback addresses:
    - ipv4 127.0.0.1-127.255.255.254
    - ipv6 ::1/128

- ranges: http://jodies.de/ipcalc?host=10.0.64.130&mask1=20&mask2=
