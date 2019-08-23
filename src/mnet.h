
#ifndef NET_H
#define NET_H

#include <stddef.h>
#include <stdint.h>

#include "mether.h"

#define NET_MID_SOCKET 1
#define NET_MID_RECEIVED 2
#define NET_MID_RESPONDED 3

typedef void* NET_SOCK;
typedef const char* SOCKET_ID;

#define RECV_BUFFER_LEN 65535

uint8_t net_respond_arp_request(
   NET_SOCK socket, struct ether_frame* frame, int frame_len );
uint8_t net_respond_arp(
   NET_SOCK socket, struct ether_frame* frame, int frame_len );
NET_SOCK net_open_socket( const SOCKET_ID if_name );
void net_close_socket( NET_SOCK socket );
int net_send_frame(
   const NET_SOCK socket, struct ether_frame* frame, int frame_len );
int net_poll_frame(
   const NET_SOCK socket, struct ether_frame* frame, int frame_sz );
void net_print_frame( struct ether_frame* frame, int frame_len );
void net_init();

#ifdef MNET_C
uint16_t mnet_responded = 0;
uint16_t mnet_received = 0;
#else
extern uint16_t mnet_responded;
extern uint16_t mnet_received;
#endif /* MNET_C */

#endif /* NET_H */

