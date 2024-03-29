
#include <check.h>
#include <stdint.h>
#include "../src/mnet.h"

#define NET_MID_SOCKET 1

#define NET_PID_SOCKET 1

static void setup_net() {
   NET_SOCK* socket = NULL;

   minit();

   socket = mget( NET_PID_SOCKET, NET_MID_SOCKET, sizeof( NET_SOCK ) );
   if( NULL == *socket ) {
      *socket = net_open_socket( "eth0" );
   }
}

static void teardown_net() {

}

START_TEST( test_poll_frame ) {
   NET_SOCK* socket = NULL;
   struct ether_frame frame;

   socket = mget( NET_PID_SOCKET, NET_MID_SOCKET, sizeof( NET_SOCK ) );
   net_poll_frame( *socket, &frame, sizeof( struct ether_frame ) );
}
END_TEST

Suite* net_suite( void ) {
   Suite* s = NULL;
   TCase* tc_task = NULL;

   s = suite_create( "net" );

   tc_task = tcase_create( "NetTask" );
   tcase_add_checked_fixture( tc_task, setup_net, teardown_net );

   tcase_add_test( tc_task, test_poll_frame );

   suite_add_tcase( s, tc_task );

   return s;
}

