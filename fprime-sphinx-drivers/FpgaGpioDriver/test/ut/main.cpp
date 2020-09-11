// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"

TEST(Test, BasicReadWrite) {
    Drv::Tester tester;
    tester.testBasicReadWrite();
}

TEST(Teardown, OK) {
  Drv::SphinxDrvReg::clearFiles();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
