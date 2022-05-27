
#ifndef MCTYMAPS_H
#define MCTYMAPS_H

#include <stdint.h>

#include "mctyfile.h"

/**
 * \file mctymaps.h
 * \brief Higher-level functions and constants for dealing with city maps.
 */

/*! \brief Width/height of a city map in tiles. */
#define MCITY_MAP_WIDTH 128

/*! \brief Altitude mask for the bits in a short in the ALTM section. */
#define MCITY_MAP_ALT_MASK 0x1f

/**
 * \brief Get the altitude of the tile at the given position.
 */
uint8_t mcitymaps_get_altm(
   uint8_t* city_buf, uint32_t city_buf_sz, uint8_t x, uint8_t y );

#endif /* !MCTYMAPS_H */

