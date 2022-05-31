
#define CHKSETUP_C
#include "chksetup.h"

#include <stdio.h>
#include <stdlib.h>

#include "../src/mctyfile.h"

void setup_mcityfile() {
   FILE* mcityfile_cty = NULL;
   uint32_t file_sz = 0;
   
   mcityfile_cty = fopen( TEST_CITY_FILENAME, "rb" );
   ck_assert_ptr_ne( mcityfile_cty, NULL );

   /* Get what the file says its size is. */
   fseek( mcityfile_cty, MCITY_FILE_SZ_OFFSET, SEEK_SET );
   fread( &file_sz, sizeof( uint32_t ), 1, mcityfile_cty );
   file_sz = mcityfile_endian_swap_32( file_sz );
   
   /* Get city file size. */
   fseek( mcityfile_cty, 0, SEEK_END );
   mcityfile_sz = ftell( mcityfile_cty );
   fseek( mcityfile_cty, 0, SEEK_SET );

   ck_assert_int_eq( mcityfile_sz - 8, file_sz );

   mcityfile_bytes = calloc( mcityfile_sz + 1, 1 );
   fread( mcityfile_bytes, mcityfile_sz, 1, mcityfile_cty );

   fclose( mcityfile_cty );
}

void teardown_mcityfile() {
   free( mcityfile_bytes );
}

