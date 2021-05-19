// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/Rules/Read.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/Rules/Write.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/Rules/Time.hpp"

namespace Drv {
        
  TEST(Read, OK) {
    Read::Tester tester;
    tester.OK();
  }
  
  TEST(Write, OK) {
    Write::Tester tester;
    tester.OK();
  }

  TEST(Time, OK) {
    Time::Tester tester;
    tester.OK();
  }

  TEST(Time, ERROR) {
    Time::Tester tester;
    tester.ERROR();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
