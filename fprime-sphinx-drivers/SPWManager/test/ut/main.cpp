// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"

TEST(Test, TestPing) {
    Drv::Tester tester;
    tester.testPing();
}

TEST(Test, TestSyncReadWrite) {
    Drv::Tester tester;
    tester.testSyncReadWrite();
}

TEST(Test, TestAsyncReadWrite) {
    Drv::Tester tester;
    tester.testAsyncReadWrite();
}

TEST(Test, TestAsyncDmaRead) {
    Drv::Tester tester;
    tester.testAsyncDmaRead();
}

TEST(Test, TestHugeWrite) {
    Drv::Tester tester;
    tester.testHugeWrite();
}

TEST(Test, TestHugeRead) {
    Drv::Tester tester;
    tester.testHugeRead();
}

TEST(Test, TestMiscRmapSettings) {
    Drv::Tester tester;
    tester.testMiscRmapSettings();
}

TEST(Test, TestMiscErrors) {
    Drv::Tester tester;
    tester.testMiscErrors();
}

TEST(Test, TestSPWErrors) {
    Drv::Tester tester;
    tester.testSPWErrors();
}

TEST(Test, TestRmapCommands) {
    Drv::Tester tester;
    tester.testRmapCommands();
}

TEST(Test, TestRmapSetParamCommand) {
    Drv::Tester tester;
    tester.testRmapSetParamCommand();
}

TEST(Test, TestRmapSetParamCommandErrors) {
    Drv::Tester tester;
    tester.testRmapSetParamCommandErrors();
}

TEST(Test, TestResetLinkCommand) {
    Drv::Tester tester;
    tester.testResetLinkCommand();
}

TEST(Test, TestResetLinkPort) {
    Drv::Tester tester;
    tester.testResetLinkPort();
}

TEST(Teardown, OK) {
  Drv::SphinxDrvReg::clearFiles();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
