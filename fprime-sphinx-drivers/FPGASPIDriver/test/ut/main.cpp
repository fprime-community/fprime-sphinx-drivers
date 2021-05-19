// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/FPGASPIDriver/test/ut/Rules/ReadWrite.hpp"

namespace Drv {
        
  TEST(ReadWrite, OK) {
    ReadWrite::Tester tester("FPGASPIDriver", 
		         (U32) FPGA_SPI_1_NUMBER, 
		         (U32) FPGA_SPI_WIDTH_8);
    tester.OK();
  }
  
  TEST(ReadWrite, ERROR) {
    ReadWrite::Tester tester("FPGASPIDriver", 
		         (U32) FPGA_SPI_2_NUMBER, 
		         (U32) FPGA_SPI_WIDTH_16);
    tester.ERROR();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
