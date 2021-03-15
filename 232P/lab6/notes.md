- tcp uses checksum, sequence number, timeout and acknowledgements and retranmission to detect damaged or lost segments and recover from them for reliable delivery.

- sudo netstat -atnp | grep ":500:

- duplicate ack wireshark filter
    - tcp.analysis.duplicate_ack_num == 1
- sack options filter
    - tcp.option_kind == 5
- neet to enable_mtu_path_discovery at hosts to enable PDMTU.