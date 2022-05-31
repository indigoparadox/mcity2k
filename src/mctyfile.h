
#ifndef MCTYFILE_H
#define MCTYFILE_H

#include <stdint.h>

/**
 * \addtogroup mcity2k_chunks Chunks
 *
 * \{
 */

/**
 * \file mctyfile.h
 * \brief Low-level functions and constants for dealing with city files.
 */

/*! \} */

/*! \brief Returned when there is an error parsing a chunk or file. */
#define MCITYFILE_ERROR 0

/*! \brief Offset of the file size in the file header in bytes. */
#define MCITY_FILE_SZ_OFFSET 4

/*! \brief Size of the initial file header in bytes. */
#define MCITY_FILE_HEADER_SZ 12

/*! \brief Size of the largest specified chunk when uncompressed. */
#define MCITY_CHUNK_DATA_SZ_MAX 32768

/**
 * \addtogroup mcity2k_chunks Chunks
 *
 * \{
 */

/*! \brief Size of the header of each chunk in bytes. */
#define MCITY_CHUNK_HEADER_SZ 8
/*! \brief Offset of the chunk size within the chunk header. */
#define MCITY_CHUNK_SZ_OFFSET 4

/*! \} */

/*! \brief Swap the endianness of a 32-bit unsigned integer. */
#define mcityfile_endian_swap_32( num ) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

/*! \brief Swap the endianness of a 16-bit unsigned integer. */
#define mcityfile_endian_swap_16( num ) ((num>>8) | (num<<8));

/**
 * \addtogroup mcity2k_chunks 
 * \{
 */

/*! \brief Given the offset of a chunk header, return the chunk's size. */
#define mcityfile_chunk_sz( city_buf, offset ) (mcityfile_endian_swap_32( *(uint32_t*)&(city_buf[offset + MCITY_CHUNK_SZ_OFFSET]) ))

/*! \brief Given the offset of a chunk header, return the chunk's ID. */
#define mcityfile_chunk_id( city_buf, offset, id ) id[0] = city_buf[offset]; id[1] = city_buf[offset + 1]; id[2] = city_buf[offset + 2]; id[3] = city_buf[offset + 3];

/*! \} */

/**
 * \addtogroup mcity2k_chunks 
 * \{
 */

/**
 * \brief Given an offset of a chunk, find the next chunk after it.
 */
uint32_t mcityfile_next_chunk(
   const uint8_t* city_buf, uint32_t city_buf_sz, uint32_t prev_offset );

/**
 * \brief Given an offset of a chunk, find the next chunk after it with the
 *        given ID.
 */
uint32_t mcityfile_find_chunk(
   const uint8_t* city_buf, uint32_t city_buf_sz, char id[5] );

/**
 * \brief Copy the uncompressed chunk data from the chunk at the given offset
 *        into the given buffer.
 */
uint32_t mcityfile_chunk_data(
   const uint8_t* city_buf, uint32_t offset,
   uint8_t* buffer, uint32_t buffer_sz );

/**
 * \brief Decompress the chunk data from the chunk at the given offset into
 *        the given buffer.
 */
uint32_t mcityfile_chunk_data_rle(
   const uint8_t* city_buf, uint32_t offset,
   uint8_t* buffer, uint32_t buffer_sz );

/*! \} */

#endif /* !MCTYFILE_H */

