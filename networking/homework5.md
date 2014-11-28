Jeremy Neal
CMSC 481 - Networking
11/10/2014

Homework 5

Q1: Consider the network...
a. Dest Address | Output Link
   -------------|------------
       h1       |    1
       h2       |    2
       h3       |    3

b. No, we cannot. Forwarding tables don't refer to source address.

c. Incoming Interface | Incoming VC # | Outgoing Interface | Outgoing VC #
   -------------------|---------------|--------------------|--------------
            1         |      13       |         3          |       31
            2         |      24       |         4          |       42

d. Forwarding table for B:

   Incoming Interface | Incoming VC # | Outgoing Interface | Outgoing VC #
   -------------------|---------------|--------------------|--------------
            1         |      12       |         2          |       21

   Forwarding table for C:

   Incoming Interface | Incoming VC # | Outgoing Interface | Outgoing VC #
   -------------------|---------------|--------------------|--------------
            1         |      12       |         2          |       21

   Forwarding table for D:

   Incoming Interface | Incoming VC # | Outgoing Interface | Outgoing VC #
   -------------------|---------------|--------------------|--------------
            1         |      13       |         3          |       31
            2         |      23       |         3          |       32

Q2: Consider a datagram network using 8-bit host addresses. Suppose a router
    uses longest prefix matching and has the following forwarding table. For
    each of the four interfaces, give the associated range of destination host
    addresses and the number of addresses in the range.

0: 00****** -> 64 different addresses
1: 010***** -> 32 different addresses
2: 10******, 011***** -> 96 different addresses
3: 11****** -> 64 different addresses

Q3: Consider a router that interconnects three subnets: Subnet 1, Subnet 2,
    Subnet 3. Suppose all of the interfaces in each of these three subnets are
    required to have the prefix 223.1.17/24. Also suppose that Subnet 1 is required
    to have at least 60 interfaces, Subnet 2 is to support at least 90 interfaces,
    and Subnet 3 is to support at least 12 interfaces. Provide three network
    addresses (of the form a.b.c.d/x) that satisfies these constraints.

Subnet 1: 223.1.17.128/26
Subnet 2: 223.1.17.0/25
Subnet 3: 223.1.17.192/28

Q4: Convert to form a.b.c.d/x

0: 200.23.16.0/21
1: 200.23.24.0/24
2: 200.23.24.0/20
3: 0.0.0.0/0

Q5: Consider sending a 2400-byte datagram into a link that has an MTU of 700
bytes. Suppose the original datagram is stamped wth the identification number
422. How many fragments are generated? What are the values in the various fields
in the IP datagram(s) generated related to fragmentation?

The datagram would be split into 4 smaller datagrams, 3 of size 696 bytes and 1
of size 312 bytes. Each fragment would contain the identification number 422.
The first fragment would have an offset value of 0 and a flag set to 1. The
second fragment would have an offset of 87 (87 * 8 = 696), and a flag set to 1.
the third fragment would have an offset of 174 (87 * 2) and a flag set to 1. The
final fragment would have an offset of 261 (87 * 3) and a flag set to 0, as
there are no more packets to reassemble.

Q6: Aggregate the following address ranges into network address represented in
CIDR notation. Show details of your calculation.

All of these addresses have 172 as the first byte. The second has a lowest value
of 16 and a highest value of 31. The range of this in binary is
00010000:00011111. Given this, we know that the entire second byte is reserved.
Therefore, the entire range of addresses can be contained in 172.16.0.0/16.
