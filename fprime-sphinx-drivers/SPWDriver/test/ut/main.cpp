// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"

TEST(Test, TestRandomRMAPCommandHeaders) {
    Drv::Tester tester;
    tester.testRandomRMAPCommandHeaders(100000);
}

TEST(Test, TestRandomRMAPReplyHeaders) {
    Drv::Tester tester;
    tester.testRandomRMAPReplyHeaders(100000);
}

TEST(Test, TestWriteRMAP) {
    Drv::Tester tester;
    tester.testWriteRMAP();
}

TEST(Test, TestReadRMAP) {
    Drv::Tester tester;
    tester.testReadRMAP();
}

TEST(Test, TestRMAPErrors) {
    Drv::Tester tester;
    tester.testRMAPErrors();
}

TEST(Test, TestSPWConnectionErrors) {
    Drv::Tester tester;
    tester.testSPWConnectionErrors();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
