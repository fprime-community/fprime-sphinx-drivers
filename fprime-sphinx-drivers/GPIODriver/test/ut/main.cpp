// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Rules/ReadWrite.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Rules/Init.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Rules/Interrupt.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Scenarios/Selected.hpp"

namespace Drv {
        
  TEST(ReadWrite, DIRIN) {
    ReadWrite::Tester tester;
    tester.DIRIN();
  }

  TEST(ReadWrite, DIROUT) {
    ReadWrite::Tester tester;
    tester.DIROUT();
  }

  TEST(ReadWrite, READIN) {
    ReadWrite::Tester tester;
    tester.READIN();
  }

  TEST(ReadWrite, READOUT) {
    ReadWrite::Tester tester;
    tester.READOUT();
  }

  TEST(ReadWrite, SETOUT) {
    ReadWrite::Tester tester;
    tester.SETOUT();
  }

  TEST(ReadWrite, CLEAROUT) {
    ReadWrite::Tester tester;
    tester.CLEAROUT();
  }

  TEST(ReadWrite, ERROR) {
    ReadWrite::Tester tester;
    tester.ERROR();
  }

  TEST(Init, OK) {
    Init::Tester tester;
    tester.OK();
  }

  TEST(Init, ERROR) {
    Init::Tester tester;
    tester.ERROR();
  }
  
  TEST(Interrupt, OK) {
    Interrupt::Tester tester;
    tester.OK();
  }
  
  TEST(Selected, Random) {
    Selected::Tester tester;
    tester.Random();
  }
  
  TEST(Teardown, OK) {
    SphinxDrvReg::clearFiles();
  }
  
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
