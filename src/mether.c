
#include "mether.h"

#include "mmem.h"

#include <stddef.h>

int ether_new_frame(
   struct ether_frame* frame_out, int frame_out_sz,
   const uint8_t src_mac[6], const uint8_t dest_mac[6],
   enum ether_type type, void* packet, int packet_len
) {
   struct ether_header* header_out = NULL;
   int frame_len = 0;

   /* Sanity/security checks. */
   frame_len = sizeof( struct ether_header ) + packet_len;
   if( frame_len > frame_out_sz ) {
      frame_len = ETHER_ERROR_FRAME_OVERFLOW;
      goto cleanup;
   }

   if( NULL == frame_out ) {
      frame_len = ETHER_ERROR_INVALID_BUFFER;
      goto cleanup;
   }

   /* Set the frame fields and encapsulate the provided packet. */
   header_out = (struct ether_header*)frame_out;
   mnet_copy( header_out->src_mac, src_mac, 6 );
   mnet_copy( header_out->dest_mac, dest_mac, 6 );
   header_out->type = ether_htons( (uint16_t)type );
   mnet_copy( frame_out->data, packet, packet_len );

cleanup:
   return frame_len;
}

int ether_get_header_len( struct ether_frame* frame, int frame_len ) {
   /* TODO: Account for VLANs and stuff. */
   return frame_len - sizeof( struct ether_header );
}

uint16_t ether_ntohs( const uint16_t input ) {
   uint8_t output[2] = { 0 };

   mnet_copy( &output, &input, sizeof( output ) );

   return
      ((uint16_t) output[1] << 0) |
      ((uint16_t) output[0] << 8);
}

uint32_t ether_ntohl( const uint32_t input ) {
   uint8_t output[4] = {};
   mnet_copy( &output, &input, sizeof( output ) );

   return
      ((uint32_t) output[3] << 0) |
      ((uint32_t) output[2] << 8) |
      ((uint32_t) output[1] << 16) |
      ((uint32_t) output[0] << 24);
}

