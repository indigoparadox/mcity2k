
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

#define MCITY_MAP_ALT_MAX 0x14

/*! \brief Altitude mask for the bits in a short in the ALTM section. */
#define MCITY_MAP_ALT_MASK 0x1f

/**
 * \brief Get the altitude of the tile at the given position.
 * \param altm_buf Pointer to the ALTM chunk from which to retrieve the tile.
 * \param x LR coordinates of the tile, in tiles (from 0 - ::MCITY_MAP_WIDTH).
 * \param y UD coordinates of the tile, in tiles (from 0 - ::MCITY_MAP_WIDTH).
 * \return Altitude of the tile (from 0 - ::MCITY_MAP_ALT_MAX).
 */
uint8_t mcitymaps_get_altm( uint8_t* altm_buf, uint8_t x, uint8_t y );

#endif /* !MCTYMAPS_H */

