// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Rules/Owner.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Rules/Read.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Rules/Write.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Scenarios/Selected.hpp"

namespace Drv {

  TEST(Owner, ClaimOK) {
    Owner::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.ClaimOK();
  }
  
  TEST(Owner, ClaimERROR) {
    Owner::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.ClaimERROR();
  }

  TEST(Owner, UnclaimOK) {
    Owner::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.UnclaimOK();
  }
  
  TEST(Owner, UnclaimERROR) {
    Owner::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.UnclaimERROR();
  }

  TEST(Read, OK) {
    Read::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.OK();
  }
  
  TEST(Read, ERROR) {
    Read::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.ERROR();
  }

  TEST(Write, OK) {
    Write::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.OK();
  }
  
  TEST(Write, ERROR) {
    Write::Tester tester("GPTimerDriver", 0, 0, //prescaler
		     false, false, 0, 0, 0, //timer1
		     false, false, 0, 0, 0, //timer2
		     false, false, 0, 0, 0, //timer3
		     false, false, 0, 0, 0); //timer4
    tester.ERROR();
  }

  TEST(Selected, Random) {
    Selected::Tester tester("GPTimerDriver", 0, 0, //prescaler
		        false, false, 0, 0, 0, //timer1
		        false, false, 0, 0, 0, //timer2
		        false, false, 0, 0, 0, //timer3
		        false, false, 0, 0, 0); //timer4
    tester.Random();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
