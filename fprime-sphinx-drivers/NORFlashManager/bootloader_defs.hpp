#ifndef SPHINX_BOOTLOADER_DEFS
#define SPHINX_BOOTLOADER_DEFS

#include <fprime-sphinx-drivers/NOR/nor.hpp>

namespace Drv
{
  // **** NOTE: The prom MUST be set to 8 bit mode
#if defined(BUILD_SPHINX)
  const static U32 NOR_FSW_IMAGE_START_LOCATION = 0x00010000;
#else
  const static U32 NOR_FSW_IMAGE_START_LOCATION = 0x00010000;
#endif

  // Max FSW image size
  const static U32 NOR_FSW_MAX_IMG_SIZE = NOR_MAX_BANK_SIZE;

  // Checksum is a 32 bit end-around-carry initialized to this seed. 16 bits
  // would be enough but why not use 32? Means the accumulation needs to be done
  // in a long long.
  const static U32 NOR_FSW_CHECKSUM_SEED = 0x55AA55AA;

  const static U32 NOR_HW_PROM_BASE = NOR_FLASH_BASE_ADDR;

  // The header is expected to be stored as big endian.
  struct __attribute__ ((__packed__)) bl_headers
  {
    uint16_t		blc_major_version;
    uint16_t		blc_minor_version;
    uint32_t		blc_num_bytes;
    uint32_t		blc_checksum;
    uint16_t		fsw_major_version;
    uint16_t		fsw_minor_version;
    uint32_t		fsw_num_bytes;
    uint32_t		fsw_checksum;
  };

};
#endif
