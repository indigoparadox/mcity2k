
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/mctyfile.h"
#include "../src/mctymaps.h"

#include "chksetup.h"

START_TEST( test_mcitymaps_altm ) {
   uint32_t offset = 0,
      data_sz = 0;
   uint8_t t = 0;
   uint8_t data[MCITY_CHUNK_DATA_SZ_MAX] = { 0 };

   offset = mcityfile_find_chunk( mcityfile_bytes, mcityfile_sz, "ALTM" );

   data_sz = mcityfile_chunk_data(
      mcityfile_bytes, offset, data, MCITY_CHUNK_DATA_SZ_MAX );

   ck_assert_int_eq( data_sz, 32768 );

   t = mcitymaps_get_altm(
      mcityfile_bytes, mcityfile_sz, _i * 10, 127 );

   switch( _i ) {
   case 0:
      ck_assert_int_eq( t, 30 );
      break;

   case 1:
      ck_assert_int_eq( t, 20 );
      break;

   case 2:
      ck_assert_int_eq( t, 10 );
      break;

   default:
      ck_assert_int_eq( t, 7 );
      break;
   }
}
END_TEST

START_TEST( test_mcitymaps_xbld ) {
   uint32_t offset = 0,
      data_sz = 0;
   uint8_t data[MCITY_CHUNK_DATA_SZ_MAX] = { 0 };

   offset = mcityfile_find_chunk( mcityfile_bytes, mcityfile_sz, "XBLD" );

   data_sz = mcityfile_chunk_data_rle(
      mcityfile_bytes, offset, data, MCITY_CHUNK_DATA_SZ_MAX );

   ck_assert_int_eq( data_sz, 16384 );
}
END_TEST

Suite* mcitymaps_suite( void ) {
   Suite* s;
   TCase* tc_core;

   s = suite_create( "mcityfile" );

   /* Core test case */
   tc_core = tcase_create( "Core" );

   tcase_add_checked_fixture( tc_core, setup_mcityfile, teardown_mcityfile );
   tcase_add_loop_test( tc_core, test_mcitymaps_altm, 0, 12 );
   tcase_add_test( tc_core, test_mcitymaps_xbld );

   suite_add_tcase( s, tc_core );

   return s;
}

