#ifndef SPHINX_DRV_NOR_HPP
#define SPHINX_DRV_NOR_HPP

namespace Drv
{
  const static U32 NOR_FLASH_MAX_BYTES_RW = 65536;

  const static U32 NOR_FLASH_BASE_ADDR = 0x00000000;
  const static U32 NOR_FLASH_HIGH_ADDR = 0x20000000;

  const static U32 NOR_FLASH_BASE_ADDR_0 = 0x00000000;

  const static U32 NOR_FLASH_BASE_ADDR_1 = 0x00000000;

  const static U32 NOR_FLASH_BASE_ADDR_2 = 0x00000000;

  const static U32 NOR_FLASH_BASE_ADDR_3 = 0x00000000;

  const static U32 NOR_MAX_BANK_SIZE = 8*1024*1024; // 8MB

  inline static bool isInNorAddrSpace(U32 bank_addr)
  {
    volatile U32 base_addr = NOR_FLASH_BASE_ADDR;
    return (bank_addr < NOR_FLASH_HIGH_ADDR) && (bank_addr >= base_addr);
  }
};

#endif
