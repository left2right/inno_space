#include "include/fsp0fsp.h"
#include "include/fsp0types.h"


uint32_t File_segment_inode::read_not_full_n_used() const {
  uint32_t n_used =
      mach_read_from_4(m_fseg_inode + FSEG_NOT_FULL_N_USED);
  return (n_used);
}

bool ut_bit_get_nth(ulint a, ulint n) {
  ut_a(n < 8 * sizeof(ulint));
  return (1 & (a >> n));
}

/** Gets a descriptor bit of a page.
 @return true if free */
static inline bool xdes_get_bit(
    const xdes_t *descr, /*!< in: descriptor */
    ulint bit,           /*!< in: XDES_FREE_BIT or XDES_CLEAN_BIT */
    page_no_t offset)    /*!< in: page offset within extent:
                         0 ... FSP_EXTENT_SIZE - 1 */
{

  ulint index = bit + XDES_BITS_PER_PAGE * offset;

  ulint bit_index = index % 8;
  ulint byte_index = index / 8;

  return (ut_bit_get_nth(
      mach_read_ulint(descr + XDES_BITMAP + byte_index, MLOG_1BYTE),
      bit_index));
}

page_no_t xdes_find_bit(
    xdes_t *descr,  /*!< in: descriptor */
    ulint bit,      /*!< in: XDES_FREE_BIT or XDES_CLEAN_BIT */
    bool val)       /*!< in: desired bit value */
{
  page_no_t i;

  for (i = 0; i < FSP_EXTENT_SIZE; i++) {
    if (val == xdes_get_bit(descr, bit, i)) {
      return (i);
    }
  }

  return (FIL_NULL);
}