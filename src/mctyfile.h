
#ifndef MCTYFILE_H
#define MCTYFILE_H

#include <stdint.h>

#define MCITY_FILE_HEADER_SZ 12
#define MCITY_CHUNK_HEADER_SZ 8
#define MCITY_CHUNK_DATA_SZ_MAX 16384
#define MCITY_CHUNK_SZ_OFFSET 4

#define mcityfile_endian_swap_32( num ) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

#define mcityfile_chunk_sz( city_buf, offset ) (mcityfile_endian_swap_32( *(uint32_t*)&(city_buf[offset + MCITY_CHUNK_SZ_OFFSET]) ))

#define mcityfile_chunk_id( city_buf, offset, id ) id[0] = city_buf[offset]; id[1] = city_buf[offset + 1]; id[2] = city_buf[offset + 2]; id[3] = city_buf[offset + 3];

struct MCITY_FILE_HEADER {
   char magic[4];
   uint32_t file_sz;
   char iff_type[4];
};

uint32_t mcityfile_next_chunk(
   const uint8_t* city_buf, uint32_t city_buf_sz, uint32_t prev_offset );

uint32_t mcityfile_chunk_data(
   const uint8_t* city_buf, uint32_t offset,
   uint8_t* buffer, uint32_t buffer_sz );

uint32_t mcityfile_chunk_data_rle(
   const uint8_t* city_buf, uint32_t offset,
   uint8_t* buffer, uint32_t buffer_sz );

#endif /* !MCTYFILE_H */

