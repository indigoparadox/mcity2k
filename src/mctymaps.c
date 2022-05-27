
#include "mctymaps.h"

#include <stddef.h>

uint8_t mcitymaps_get_altm( uint8_t* altm_buf, uint8_t x, uint8_t y ) {
   uint16_t* alt_map = NULL,
      tile = 0;

   altm_buf += MCITY_CHUNK_HEADER_SZ;
   alt_map = (uint16_t*)altm_buf;
   tile = mcityfile_endian_swap_16( alt_map[(y * MCITY_MAP_WIDTH) + x] );
   
   return ((uint8_t)tile & MCITY_MAP_ALT_MASK);
}

