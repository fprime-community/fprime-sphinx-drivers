// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/RWOwner.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/SPIMutex.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Pointer.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Reset.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Scenarios/Selected.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/RWReverse.hpp"

namespace Drv {
  
  TEST(Test, TestClaimUnclaimOK) {
    Tester tester;
    tester.testClaimUnclaimOK();
  }

  TEST(Test, TestDoubleClaim) {
    Tester tester;
    tester.testDoubleClaim();
  }

  TEST(Test, TestDoubleUnclaim) {
    Tester tester;
    tester.testDoubleUnclaim();
  }

  TEST(Test, TestConfigureOK) {
    Tester tester;
    tester.testConfigureOK();
  }

  TEST(Test, TestConfigureNotOwner) {
    Tester tester;
    tester.testConfigureNotOwner();
  }

  TEST(Test, TestInitOK) {
    Tester tester;
    tester.testInitOK();
  }

  TEST(Test, TestRWNotOwner) {
    Tester tester;
    tester.testRWNotOwner();
  }

  TEST(Test, TestConstructor) {
    Tester tester( "SPIDriverGeneric",
      (U8) 0, //loopback_mode
      (U8) 0, //clock_polarity                                                                                                    
      (U8) 0, //clock_phase                                                                                                       
      (U8) 0, //div_clock_16                                                                                                      
      (U8) 1, //reverse_mode                                                                                                      
      (U8) 8, //word_len                                                                                                          
      (U8) 12, //prescale modulus                                                                                                 
      (U8) 0,  //prescale modulus factor                                                                                          
      (U8) 0);
    tester.testConstructor();
  }
    
  TEST(SPIMutex, UnclaimOK) {                                  
    SPIMutex::Tester tester;
    tester.UnclaimOK();
  }  

  TEST(SPIMutex, UnclaimDouble) {
    SPIMutex::Tester tester;
    tester.UnclaimDouble();
  }

  TEST(SPIMutex, ClaimOK) {
    SPIMutex::Tester tester;
    tester.ClaimOK();
  }

  TEST(SPIMutex, ClaimDouble) {
    SPIMutex::Tester tester;
    tester.ClaimDouble();
  }
        
  TEST(RWOwner, ERROR) {
    RWOwner::Tester tester;
    tester.ERROR();
  }

  TEST(RWOwner, TIMEOUT) {
    RWOwner::Tester tester;
    tester.TIMEOUT();
  }
    
  TEST(RWOwner, SUCCESS8) {
    RWOwner::Tester tester;
    tester.SUCCESS8();
  }
    
  TEST(RWOwner, SUCCESS16) {
    RWOwner::Tester tester;
    tester.SUCCESS16();
  }

  TEST(RWOwner, SUCCESS32) {
    RWOwner::Tester tester;
    tester.SUCCESS32();
  }

  TEST(RWReverse, SUCCESS8) {
    RWReverse::Tester tester;
    tester.SUCCESS8();
  }

  TEST(RWReverse, SUCCESS16) {
    RWReverse::Tester tester;
    tester.SUCCESS16();
  }

  TEST(RWReverse, SUCCESS32) {
    RWReverse::Tester tester;
    tester.SUCCESS32();
  }  
    
  TEST(Pointer, Invalid) {
    Pointer::Tester tester;
    tester.Invalid();
  }
      
  TEST(Selected, Random) {
    Selected::Tester tester;
    tester.Random();
  }
      
  TEST(Reset, OK) {
    Reset::Tester tester;
    tester.OK();
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
