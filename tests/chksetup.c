
#define CHKSETUP_C
#include "chksetup.h"

#include <stdio.h>
#include <stdlib.h>

#include "../src/mctyfile.h"

void setup_mcityfile() {
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

void teardown_mcityfile() {
   free( mcityfile_bytes );
}

