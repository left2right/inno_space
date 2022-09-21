
#include "include/mach_data.h"

/*******************************************************//**
Creates a 64-bit integer out of two 32-bit integers.
@return	created integer */
uint64_t ut_ull_create(
  ulint	high,	/*!< in: high-order 32 bits */
  ulint	low)	/*!< in: low-order 32 bits */
{
  return(((uint64_t) high) << 32 | low);
}

/** The following function is used to fetch data from one byte.
@param[in]	b	pointer to a byte to read
@return ulint integer, >= 0, < 256 */
uint8_t mach_read_from_1(const byte *b) {
  ut_ad(b);
  return ((uint8_t)(b[0]));
}

uint16_t mach_read_from_2(const byte *b) {
  return (((ulint)(b[0]) << 8) | (ulint)(b[1]));
}

uint32_t mach_read_from_4(const byte *b) {
  return ((static_cast<uint32_t>(b[0]) << 24) |
      (static_cast<uint32_t>(b[1]) << 16) |
      (static_cast<uint32_t>(b[2]) << 8) | static_cast<uint32_t>(b[3]));
}

uint64_t mach_read_from_6(const byte*	b) {
  return(ut_ull_create(mach_read_from_2(b), mach_read_from_4(b + 2)));
}

/** The following function is used to fetch data from 8 consecutive
 * bytes. The most significant byte is at the lowest address.
 * @param[in]  b pointer to 8 bytes from where read
 * @return 64-bit integer */
uint64_t mach_read_from_8(const byte *b) {
  uint64_t u64;

  u64 = mach_read_from_4(b);
  u64 <<= 32;
  u64 |= mach_read_from_4(b + 4);

  return (u64);
}

/** Read 1 to 4 bytes from a file page buffered in the buffer pool.
@param[in]      ptr     pointer where to read
@param[in]      type    MLOG_1BYTE, MLOG_2BYTES, or MLOG_4BYTES
@return value read */
uint32_t mach_read_ulint(const byte *ptr, mlog_id_t type) {
  switch (type) {
    case MLOG_1BYTE:
      return (mach_read_from_1(ptr));
    case MLOG_2BYTES:
      return (mach_read_from_2(ptr));
    case MLOG_4BYTES:
      return (mach_read_from_4(ptr));
    default:
      break;
  }

  ut_a(false);
}

/** The following function is used to store data in one byte.
@param[in]	b	pointer to byte where to store
@param[in]	n	ulint integer to be stored, >= 0, < 256 */
void mach_write_to_1(byte *b, ulint n) {
  ut_ad(b);
  ut_ad((n | 0xFFUL) <= 0xFFUL);

  b[0] = (byte)n;
}

/** The following function is used to store data in two consecutive
bytes. We store the most significant byte to the lower address.
@param[in]	b	pointer to 2 bytes where to store
@param[in]	n	2 byte integer to be stored, >= 0, < 64k */
void mach_write_to_2(byte *b, ulint n) {
  ut_ad(b);
  ut_ad((n | 0xFFFFUL) <= 0xFFFFUL);

  b[0] = (byte)(n >> 8);
  b[1] = (byte)(n);
}


/** The following function is used to store data in 3 consecutive
bytes. We store the most significant byte to the lowest address.
@param[in]  b pointer to 3 bytes where to store
@param[in]  n 3 byte integer to be stored */
void mach_write_to_3(byte *b, ulint n) {
  ut_ad(b);
  ut_ad((n | 0xFFFFFFUL) <= 0xFFFFFFUL);

  b[0] = (byte)(n >> 16);
  b[1] = (byte)(n >> 8);
  b[2] = (byte)(n);
}

/** The following function is used to store data in 4 consecutive
bytes. We store the most significant byte to the lowest address.
@param[in]  b pointer to 4 bytes where to store
@param[in]  n 4 byte integer to be stored */
void mach_write_to_4(byte *b, ulint n) {
  ut_ad(b);

  b[0] = static_cast<byte>(n >> 24);
  b[1] = static_cast<byte>(n >> 16);
  b[2] = static_cast<byte>(n >> 8);
  b[3] = static_cast<byte>(n);
}

