
#ifndef inno_space_mach_data_h
#define inno_space_mach_data_h

#include <stdint.h>

#include "include/udef.h"

enum mlog_id_t {
  /** if the mtr contains only one log record for one page,
  i.e., write_initial_log_record has been called only once,
  this flag is ORed to the type of that first log record */
  MLOG_SINGLE_REC_FLAG = 128,

  /** one byte is written */
  MLOG_1BYTE = 1,

  /** 2 bytes ... */
  MLOG_2BYTES = 2,

  /** 4 bytes ... */
  MLOG_4BYTES = 4,

  /** 8 bytes ... */
  MLOG_8BYTES = 8,
};

/** The following function is used to fetch data from one byte.
@param[in]	b	pointer to a byte to read
@return ulint integer, >= 0, < 256 */
uint8_t mach_read_from_1(const byte *b);

uint16_t mach_read_from_2(const byte *b);

uint32_t mach_read_from_4(const byte *b);

uint64_t mach_read_from_6(const byte *b);

uint32_t mach_read_ulint(const byte *ptr, mlog_id_t type);

/** The following function is used to fetch data from 8 consecutive
 * bytes. The most significant byte is at the lowest address.
 * @param[in]  b pointer to 8 bytes from where read
 * @return 64-bit integer */
uint64_t mach_read_from_8(const byte *b);


/** The following function is used to store data in one byte.
@param[in]	b	pointer to byte where to store
@param[in]	n	ulint integer to be stored, >= 0, < 256 */
void mach_write_to_1(byte *b, ulint n);

/** The following function is used to store data in two consecutive
bytes. We store the most significant byte to the lower address.
@param[in]	b	pointer to 2 bytes where to store
@param[in]	n	2 byte integer to be stored, >= 0, < 64k */
void mach_write_to_2(byte *b, ulint n);


/** The following function is used to store data in 3 consecutive
bytes. We store the most significant byte to the lowest address.
@param[in]  b pointer to 3 bytes where to store
@param[in]  n 3 byte integer to be stored */
void mach_write_to_3(byte *b, ulint n);

/** The following function is used to store data in 4 consecutive
bytes. We store the most significant byte to the lowest address.
@param[in]  b pointer to 4 bytes where to store
@param[in]  n 4 byte integer to be stored */
void mach_write_to_4(byte *b, ulint n);

#endif
