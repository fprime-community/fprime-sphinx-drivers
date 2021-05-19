// File: AtomicBitTwiddleTester.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 26 June, 2018
//
// Implementation of test for the atomic bit-twiddling functions actually
// twiddling bits. It runs the bit pattern 11 leftwards through a full
// NATIVE_UINT_TYPE both with the setBit() and clearBit() methods and with
// leftshift.

#include "AtomicBitTwiddleTester.hpp"

#include <cstdio>

#define SET_BIT_OFFSET 2

namespace Drv {

    AtomicBitTwiddleTester::AtomicBitTwiddleTester(void) {};
    AtomicBitTwiddleTester::~AtomicBitTwiddleTester(void) {};

    void AtomicBitTwiddleTester::testAllBits(void)
    {
        U32 word = 0x00000000;
        NATIVE_UINT_TYPE rightWord = 3;

        Drv::setBit(word, 0);
        ASSERT_EQ(1, Drv::readReg(word));

        Drv::setBit(word, 1);
        ASSERT_EQ(3, Drv::readReg(word));

        for (NATIVE_UINT_TYPE i = 0; i < sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE; ++i) {

            if (i < sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE - SET_BIT_OFFSET) {
                Drv::setBit(word, i + SET_BIT_OFFSET);
                ASSERT_EQ(rightWord | (rightWord << 1), Drv::readReg(word));
            }
            Drv::clearBit(word, i);

            rightWord <<= 1;
        }
        ASSERT_EQ(rightWord, Drv::readReg(word));
    }

    void AtomicBitTwiddleTester::testAllBitsAtomic(void)
    {
        U32 word = 0x00000000;
        NATIVE_UINT_TYPE rightWord = 3;

        Drv::setBitAtomic(word, 0);
        ASSERT_EQ(1, Drv::readReg(word));

        Drv::setBitAtomic(word, 1);
        ASSERT_EQ(3, Drv::readReg(word));

        for (NATIVE_UINT_TYPE i = 0; i < sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE; ++i) {

            if (i < sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE - SET_BIT_OFFSET) {
                Drv::setBitAtomic(word, i + SET_BIT_OFFSET);
                ASSERT_EQ(rightWord | (rightWord << 1), Drv::readReg(word));
            }
            Drv::clearBitAtomic(word, i);

            rightWord <<= 1;
        }
        ASSERT_EQ(rightWord, Drv::readReg(word));
    }


    void AtomicBitTwiddleTester::testOutOfRangeSet(void)
    {
        EXPECT_DEATH(Drv::setBit(0, sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE), "");
    }

    void AtomicBitTwiddleTester::testOutOfRangeClear(void)
    {
        EXPECT_DEATH(Drv::setBit(0, sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE), "");
    }

}
