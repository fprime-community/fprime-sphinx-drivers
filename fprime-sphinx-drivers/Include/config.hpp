#ifndef FPRIME_SPHINX_DRIVERS_CONFIG_HPP
#define FPRIME_SPHINX_DRIVERS_CONFIG_HPP

// This chunk size should be a multiple of
// actual chip size
#ifndef FSW_IMAGE_CHUNK_SIZE
#define FSW_IMAGE_CHUNK_SIZE (8*1024)
#endif

#ifndef FSW_MAX_BANK_SIZE
#define FSW_MAX_BANK_SIZE (8*1024*1024)
#endif

#endif //FPRIME_SPHINX_DRIVERS_CONFIG_HPP
