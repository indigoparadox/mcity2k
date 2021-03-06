
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
      return MCITYFILE_ERROR;
   }

   return prev_offset + MCITY_CHUNK_HEADER_SZ + chunk_sz;
}

uint32_t mcityfile_find_chunk(
   const uint8_t* city_buf, uint32_t city_buf_sz, char id[5]
) {
   uint32_t offset = 0;
   char id_iter[5] = { 0 };

   do {
      offset = mcityfile_next_chunk( city_buf, city_buf_sz, offset );
      if( MCITYFILE_ERROR == offset ) {
         break;
      }
      mcityfile_chunk_id( city_buf, offset, id_iter );
   } while( 0 != strncmp( id_iter, id, 4 ) );

   return offset;
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

   /* Grab chunk size and skip the header. */
   chunk_sz = mcityfile_chunk_sz( city_buf, offset );
   offset += MCITY_CHUNK_HEADER_SZ;

   /* Decode the chunk data. */
   while( i_src < chunk_sz ) {
      if( 0 == city_buf[offset + i_src] || 128 == city_buf[offset + i_src] ) {
         /* Invalid encoding byte. */
         return MCITYFILE_ERROR;
      }

      if( 128 > city_buf[offset + i_src] ) {
         /* Compression: next i_rle bytes are uncompressed. */

         /* Grab RLE count and move to data start. */
         i_rle = city_buf[offset + i_src];
         i_src++;

         while( 0 < i_rle ) {
            buffer[i_dest++] = city_buf[offset + i_src];

            i_src++;
            i_rle--;
            if( i_dest >= buffer_sz ) {
               /* Buffer too small. */
               return MCITYFILE_ERROR;
            }
         }

      } else if( 128 < city_buf[offset + i_src] ) {
         /* Compression: next byte repeated i_rle times. */

         /* Grab RLE count and move to data start. */
         i_rle = city_buf[offset + i_src] - 127;
         i_src++;

         /* Unroll compressed byte into dest buffer. */
         while( 0 < i_rle ) {
            
            buffer[i_dest++] = city_buf[offset + i_src];
            i_rle--;

            if( i_dest >= buffer_sz ) {
               /* Buffer too small. */
               return MCITYFILE_ERROR;
            }
         }

         i_src++;
      }

   }

   return i_dest;
}

