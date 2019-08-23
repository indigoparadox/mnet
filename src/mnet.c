
#define MNET_C
#include "mnet.h"
#include "marp.h"

#include <stddef.h>
#include <stdint.h>

const uint8_t g_bcast_mac[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
const uint8_t g_src_ip[4] = { 10, 137, 2, 88 };
const uint8_t g_search_ip[4] = { 10, 137, 2, 11 };
const uint8_t g_src_mac[6] = { 0xab, 0xcd, 0xef, 0xde, 0xad, 0xbf };

uint8_t net_respond_arp_request(
   NET_SOCK socket, struct ether_frame* frame, int frame_len
) {
   struct arp_packet* arp = (struct arp_packet*)&(frame->data);
   int arp_len = 0;
   int arp_sz = frame_len - ether_get_header_len( frame, frame_len );
   uint8_t retval = 0;
   uint8_t dest_mac[6];

   arp_len = arp_respond( arp, arp_sz, NULL, 0,
      g_src_mac, ETHER_ADDRLEN, g_src_ip, ETHER_ADDRLEN_IPV4 );
   if( 0 == arp_len ) {
      goto cleanup;
   }

   mnet_responded++;

#ifdef NET_CON_ECHO
   tputs( g_str_responding );
   arp_print_packet( arp, arp_len );
#endif /* NET_CON_ECHO */

   /* Send ARP response inside of a new ethernet frame. */
   arp_get_dest_mac( dest_mac, 6, arp );
   frame_len = ether_new_frame( frame, sizeof( struct ether_frame ),
      g_src_mac, dest_mac, ETHER_TYPE_ARP, arp, arp_len );
   if( 0 == frame_len ) {
      retval = 1;
      goto cleanup;
   }

   net_send_frame( socket, frame, frame_len );

cleanup:
   return retval;
}

uint8_t net_respond_arp(
   NET_SOCK socket, struct ether_frame* frame, int frame_len
) {
   struct arp_header* arp_header = (struct arp_header*)&(frame->data);
   switch( ether_ntohs( arp_header->opcode ) ) {
      case ARP_REQUEST:
         return net_respond_arp_request( socket, frame, frame_len );
   }
   return ARP_INVALID_PACKET;
}

void net_init() {

}

