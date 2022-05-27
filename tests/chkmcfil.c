
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/mctyfile.h"

uint8_t* mcityfile_bytes = NULL;
uint32_t mcityfile_sz = 0;

static void setup_mcityfile() {
   FILE* mcityfile_cty = NULL;
   struct MCITY_FILE_HEADER header;
   
   mcityfile_cty = fopen( "floating.sc2", "rb" );
   ck_assert_ptr_ne( mcityfile_cty, NULL );

   fread( &header, sizeof( struct MCITY_FILE_HEADER ), 1, mcityfile_cty );
   header.file_sz = mcityfile_endian_swap_32( header.file_sz );
   
   /* Get city file size. */
   fseek( mcityfile_cty, 0, SEEK_END );
   mcityfile_sz = ftell( mcityfile_cty );
   fseek( mcityfile_cty, 0, SEEK_SET );

   ck_assert_int_eq( mcityfile_sz - 8, header.file_sz );

   mcityfile_bytes = calloc( mcityfile_sz + 1, 1 );
   fread( mcityfile_bytes, mcityfile_sz, 1, mcityfile_cty );

   fclose( mcityfile_cty );
}

static void teardown_mcityfile() {
   free( mcityfile_bytes );
}

START_TEST( test_mcityfile_sect ) {
   uint32_t offset = 0,
      data_sz = 0;
   char id[5] = { 0 };
   char data[MCITY_CHUNK_DATA_SZ_MAX] = { 0 };

   do {
      offset = mcityfile_next_chunk(
         mcityfile_bytes, mcityfile_sz, offset );
      if( 0 == offset ) {
         break;
      }
      mcityfile_chunk_id( mcityfile_bytes, offset, id );
   } while( 0 != strncmp( id, "CNAM", 4 ) );

   data_sz = mcityfile_chunk_data(
      mcityfile_bytes, offset, (uint8_t*)data, MCITY_CHUNK_DATA_SZ_MAX );

   ck_assert_int_eq( data_sz, 32 );
   ck_assert_str_eq( "Floating Island", &(data[1]) ); /* Skip first 0x1F */
}
END_TEST

Suite* mcityfile_suite( void ) {
   Suite* s;
   TCase* tc_core;

   s = suite_create( "mcityfile" );

   /* Core test case */
   tc_core = tcase_create( "Core" );

   tcase_add_checked_fixture( tc_core, setup_mcityfile, teardown_mcityfile );
   tcase_add_test( tc_core, test_mcityfile_sect );

   suite_add_tcase( s, tc_core );

   return s;
}

