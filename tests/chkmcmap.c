
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
   char data[MCITY_CHUNK_DATA_SZ_MAX] = { 0 };

   offset = mcityfile_find_chunk( mcityfile_bytes, mcityfile_sz, "CNAM" );

   data_sz = mcityfile_chunk_data(
      mcityfile_bytes, offset, (uint8_t*)data, MCITY_CHUNK_DATA_SZ_MAX );

   ck_assert_int_eq( data_sz, 32 );
   ck_assert_str_eq( "Floating Island", &(data[1]) ); /* Skip first 0x1F */
}
END_TEST

Suite* mcitymaps_suite( void ) {
   Suite* s;
   TCase* tc_core;

   s = suite_create( "mcityfile" );

   /* Core test case */
   tc_core = tcase_create( "Core" );

   tcase_add_checked_fixture( tc_core, setup_mcityfile, teardown_mcityfile );
   tcase_add_test( tc_core, test_mcitymaps_altm );

   suite_add_tcase( s, tc_core );

   return s;
}

