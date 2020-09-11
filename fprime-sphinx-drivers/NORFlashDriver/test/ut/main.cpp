// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/NORFlashDriver/test/ut/Rules/Read.hpp"
#include "fprime-sphinx-drivers/NORFlashDriver/test/ut/Rules/Write.hpp"

namespace Drv {
        
  TEST(Read, OK) {
    Read::Tester tester;
    tester.OK();
  }
  
  TEST(Read, ERROR) {
    Read::Tester tester;
    tester.ERROR();
  }

  TEST(Write, OK) {
    Write::Tester tester;
    tester.OK();
  }
  
  TEST(Write, ERROR) {
    Write::Tester tester;
    tester.ERROR();
  }

  TEST(Teardown, OK) {
    SphinxDrvReg::clearFiles();
  }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
