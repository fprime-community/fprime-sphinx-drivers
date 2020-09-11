// ----------------------------------------------------------------------
// Main.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"

TEST(Test, TestSetRate) {
    Drv::Tester tester;
    tester.testSetRate();
}

TEST(Test, TestSetRun) {
    Drv::Tester tester;
    tester.testSetRun();
}

TEST(Test, TestSetPwrCtrl) {
    Drv::Tester tester;
    tester.testSetPwrCtrl();
}

TEST(Test, TestTelemetry) {
    Drv::Tester tester;
    tester.testTelemetry();
}

TEST(Test, TestTimeOut) {
    Drv::Tester tester;
    tester.testTimeOut();
}

TEST(Test, TestSetTimeOut) {
    Drv::Tester tester;
    tester.testSetTimeOut();
}

TEST(Test, pingTest){
    Drv::Tester tester;
    tester.pingTest();
}

TEST(Teardown, OK) {
  Drv::SphinxDrvReg::clearFiles();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
