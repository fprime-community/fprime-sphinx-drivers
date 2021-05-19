// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Read.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Write.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Erase.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Misc.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Scenarios/Selected.hpp"

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

  TEST(Erase, OK) {
    Erase::Tester tester;
    tester.OK();
  }

  TEST(Misc, Cancel) {
    Misc::Tester tester;
    tester.Cancel();
  }
  
  TEST(Misc, Reset) {
    Misc::Tester tester;
    tester.Reset();
  }

  TEST(Misc, Verify) {
    Misc::Tester tester;
    tester.Verify();
  }

  TEST(Selected, Random) {
    Selected::Tester tester;
    tester.Random();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
