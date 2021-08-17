// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/BytesUsed.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Writer.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Reader.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Scenarios/Selected.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Init.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Interrupt.hpp"

namespace Drv {
          
  TEST(BytesUsed, OK) {
    BytesUsed::Tester tester;
    tester.OK(); 
  }
  
  TEST(Init, OK) {
    Init::Tester tester;
    tester.OK(); 
  }

  TEST(Init, HWOK) {
    Init::Tester tester;
    tester.HWOK(); 
  }
  
  TEST(Writer, TIMEOUT) {
    Writer::Tester tester;
    tester.TIMEOUT(); 
  } 
  
  TEST(Writer, OK) {
    Writer::Tester tester;
    tester.OK(); 
  } 
  
  TEST(Writer, NBYTES) {
    Writer::Tester tester;
    tester.NBYTES(); 
  } 
  
  TEST(Writer, NULLPTR) {
    Writer::Tester tester;
    tester.NULLPTR(); 
  } 
  
  TEST(Reader, TIMEOUT) {
    Reader::Tester tester;
    tester.TIMEOUT(); 
  } 
   
  TEST(Reader, OK) {
    Reader::Tester tester;
    tester.OK(); 
  } 
 
  TEST(Reader, NBYTES) {
    Reader::Tester tester;
    tester.NBYTES(); 
  } 

  TEST(Reader, NULLPTR) {
    Reader::Tester tester;
    tester.NULLPTR(); 
  } 

  TEST(Reader, DATA) {
    Reader::Tester tester;
    tester.DATA(); 
  } 
    
  TEST(Reader, ERROR) {
    Reader::Tester tester;
    tester.ERROR(); 
  } 

  TEST(Reader, EMPTY) {
    Reader::Tester tester;
    tester.EMPTY(); 
  } 

  TEST(Reader, FWOK) {
    Reader::Tester tester;
    tester.FWOK(); 
  } 
  
  TEST(Interrupt, OK) {
    Interrupt::Tester tester;
    tester.OK(); 
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
