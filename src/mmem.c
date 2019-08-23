
#include "mmem.h"

#include <stdint.h>

int mnet_copy( void* dest, const void* src, int sz ) {
   int i = 0;
   for( i = 0 ; sz > i ; i++ ) {
      ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
   }
   return i;
}

int mnet_compare( const void* c1, const void* c2, int sz ) {
   int i = 0;
   for( i = 0 ; sz > i ; i++ ) {
      if( ((uint8_t*)c1)[i] != ((uint8_t*)c2)[i] ) {
         return 1;
      }
   }
   return 0;
}

