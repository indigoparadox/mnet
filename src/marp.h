
#ifndef ARP_H
#define ARP_H

#include <stdint.h>

#include "mether.h"

#define ARP_PACKET_HEADER_SIZE 24
#ifdef NET_IPV6
#define ARP_PACKET_DATA_SIZE_MAX 44 /* Support bigger addresses. */
#else
#define ARP_PACKET_DATA_SIZE_MAX 20 /* 4 + 4 + 6 + 6 */
#endif /* NET_IPV6 */
#define ARP_PACKET_SIZE_MAX (ARP_PACKET_HEADER_SIZE + ARP_PACKET_DATA_SIZE_MAX)

#define ARP_INVALID_PACKET 64

#define ARP_ERROR_ADDRESS_OVERFLOW -2
#define ARP_ERROR_BAD_PACKET_SIZE -4
#define ARP_ERROR_PACKET_OVERFLOW -8

struct arp_header {
   uint16_t hwtype;
   uint16_t prototype;
   uint8_t hwsize;
   uint8_t protosize;
   uint16_t opcode;
} __attribute__((packed));

struct arp_packet {
   struct arp_header header;
   uint8_t data[ARP_PACKET_DATA_SIZE_MAX];
} __attribute__((packed));

/*
struct arp_packet_ipv4 {
   struct arp_header header;
   uint8_t src_mac[ETHER_ADDRLEN];
   uint8_t src_ip[ETHER_ADDRLEN_IPV4];
   uint8_t dest_mac[ETHER_ADDRLEN];
   uint8_t dest_ip[ETHER_ADDRLEN_IPV4];
} __attribute__((packed));
*/

enum arp_opcode {
   ARP_REQUEST    = 0x0001,
   ARP_REPLY      = 0x0002,
   ARP_RARP       = 0x0003,
   ARP_RARP_REPLY = 0x0004
};

void arp_print_packet( struct arp_packet* packet, int packet_len );
int arp_get_dest_mac( uint8_t* mac, int mac_sz, struct arp_packet* arp );
int arp_respond( 
   struct arp_packet* call_packet, int call_packet_sz,
   struct arp_packet* resp_packet, int resp_packet_sz,
   const uint8_t* my_mac, int my_mac_len, const uint8_t* my_ip, int my_ip_len );
/*
struct arp_packet_ipv4* arp_new_packet_ipv4(
   enum arp_opcode op, const uint8_t* src_mac, const uint8_t* dest_mac,
   const uint8_t* src_ip, const uint8_t* dest_ip );
*/

#endif /* ARP_H */

