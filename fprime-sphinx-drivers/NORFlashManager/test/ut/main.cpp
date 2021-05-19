// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Write.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Read.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Erase.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Size.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Worker.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Misc.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Cmd.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Scenarios/Selected.hpp"

namespace Drv {
        
  TEST(Write, OK) {
    Write::Tester tester("NORFlashManager", (U32) 1000);
    tester.OK();
  }
  
  TEST(Write, ERROR) {
    Write::Tester tester("NORFlashManager", (U32) 1000);
    tester.ERROR();
  }

  TEST(Read, OK) {
    Read::Tester tester("NORFlashManager", (U32) 1000);
    tester.OK();
  }
  
  TEST(Read, ERROR) {
    Read::Tester tester("NORFlashManager", (U32) 1000);
    tester.ERROR();
  }

  TEST(Erase, OK) {
    Erase::Tester tester("NORFlashManager", (U32) 1000);
    tester.OK();
  }
  
  TEST(Erase, ERROR) {
    Erase::Tester tester("NORFlashManager", (U32) 1000);
    tester.ERROR();
  }

  TEST(Size, Block) {
    Size::Tester tester("NORFlashManager", (U32) 1000);
    tester.Block();
  }
  
  TEST(Size, FSW) {
    Size::Tester tester("NORFlashManager", (U32) 1000);
    tester.FSW();
  }
  
  TEST(Worker, Read) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Read();
  }
  
  TEST(Worker, Write) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Write();
  }
  
  TEST(Worker, Erase) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Erase();
  }

  TEST(Worker, Reset) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Reset();
  }

  TEST(Worker, Verify) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Verify();
  }

  TEST(Worker, Error) {
    Worker::Tester tester("NORFlashManager", (U32) 1000);
    tester.Error();
  }

  TEST(Misc, SchedIn) {
    Misc::Tester tester("NORFlashManager", (U32) 1000);
    tester.SchedIn();
  }

  TEST(Misc, Ping) {
    Misc::Tester tester("NORFlashManager", (U32) 1000);
    tester.Ping();
  }

  TEST(Misc, Verify) {
    Misc::Tester tester("NORFlashManager", (U32) 1000);
    tester.Verify();
  }

  TEST(Cmd, Reset) {
    Cmd::Tester tester("NORFlashManager", (U32) 1000);
    tester.Reset();
  }

  TEST(Cmd, Timeout) {
    Cmd::Tester tester("NORFlashManager", (U32) 1000);
    tester.Timeout();
  }

  TEST(Selected, Random) {
    Selected::Tester tester("NORFlashManager", (U32) 1000);
    tester.Random();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
