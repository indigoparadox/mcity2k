
#include "mctyfile.h"

/* memcpy() */
#include <string.h>

uint32_t mcityfile_next_chunk(
   const uint8_t* city_buf, uint32_t city_buf_sz, uint32_t prev_offset
) {
   uint32_t chunk_sz = 0;

   if( 0 == prev_offset ) {
      return MCITY_FILE_HEADER_SZ;
   }

   chunk_sz = mcityfile_chunk_sz( city_buf, prev_offset );

   /* Make sure next chunk is within the city buffer. */
   if( prev_offset + MCITY_CHUNK_HEADER_SZ + chunk_sz > city_buf_sz ) {
      return 0;
   }

   return prev_offset + MCITY_CHUNK_HEADER_SZ + chunk_sz;
}

uint32_t mcityfile_chunk_data(
   const uint8_t* city_buf, uint32_t offset, uint8_t* buffer, uint32_t buffer_sz
) {
   uint32_t chunk_sz = 0;

   chunk_sz = mcityfile_chunk_sz( city_buf, offset );

   /* Make sure the buffer can hold the chunk. */
   if( chunk_sz > buffer_sz ) {
      return 0;
   }

   memcpy( buffer, &(city_buf[offset + MCITY_CHUNK_HEADER_SZ]), chunk_sz );

   return chunk_sz;
}

uint32_t mcityfile_chunk_data_rle(
   const uint8_t* city_buf, uint32_t offset, uint8_t* buffer, uint32_t buffer_sz
) {
   uint32_t chunk_sz = 0,
      i_src = 0,
      i_dest = 0,
      i_rle = 0;

   chunk_sz = mcityfile_chunk_sz( city_buf, offset );

   while( i_src < chunk_sz ) {
      if( 128 > city_buf[offset + i_src] ) {
         /* Compression: next i_rle bytes are uncompressed. */
         i_rle = city_buf[offset + i_src];
         i_src++;

         while( 0 < i_rle ) {
            buffer[i_dest++] = i_src++;
            if( i_dest >= buffer_sz ) {
               /* Buffer too small. */
               return 0;
            }
            i_rle--;
         }

      } else if( 128 < city_buf[offset + i_src] ) {
         /* Compression: next byte repeated i_rle times. */
         i_rle = city_buf[offset + i_src] - 127;
         i_src++;

         /* Unroll compressed byte into dest buffer. */
         while( 0 < i_rle ) {
            buffer[i_dest++] = i_src;
            if( i_dest >= buffer_sz ) {
               /* Buffer too small. */
               return 0;
            }
            i_rle--;
         }

         i_src++;
      }

   }

   return chunk_sz;
}

