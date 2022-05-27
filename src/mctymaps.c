
#include "mctymaps.h"

#include <stddef.h>

uint8_t mcitymaps_get_altm(
   uint8_t* city_buf, uint32_t city_buf_sz, uint8_t x, uint8_t y
) {
   uint16_t* alt_map = NULL,
      tile = 0;
   uint8_t* alt_map_bytes = NULL;
   uint32_t offset = 0;

   offset = mcityfile_find_chunk( city_buf, city_buf_sz, "ALTM" );

   alt_map_bytes = &(city_buf[offset + MCITY_CHUNK_HEADER_SZ]);
   alt_map = (uint16_t*)alt_map_bytes;

   tile =
      mcityfile_endian_swap_16( alt_map[(y * MCITY_MAP_WIDTH) + x] );
   
   return ((uint8_t)tile & MCITY_MAP_ALT_MASK);
}

