// ======================================================================
// \title  NORFlashManager/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashManager component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashManager_GTEST_BASE_HPP
#define NORFlashManager_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for command history assertions
// ----------------------------------------------------------------------

#define ASSERT_CMD_RESPONSE_SIZE(size) \
  this->assertCmdResponse_size(__FILE__, __LINE__, size)

#define ASSERT_CMD_RESPONSE(index, opCode, cmdSeq, response) \
  this->assertCmdResponse(__FILE__, __LINE__, index, opCode, cmdSeq, response)

// ----------------------------------------------------------------------
// Macros for event history assertions 
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ERASE_BUSY_SIZE(size) \
  this->assertEvents_NOR_ERASE_BUSY_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ERASE_BUSY(index, _actual_state, _expected_state, _error_status) \
  this->assertEvents_NOR_ERASE_BUSY(__FILE__, __LINE__, index, _actual_state, _expected_state, _error_status)

#define ASSERT_EVENTS_NOR_ERASE_FAIL_SIZE(size) \
  this->assertEvents_NOR_ERASE_FAIL_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ERASE_FAIL(index, _error_status) \
  this->assertEvents_NOR_ERASE_FAIL(__FILE__, __LINE__, index, _error_status)

#define ASSERT_EVENTS_NOR_ERASING_SIZE(size) \
  this->assertEvents_NOR_ERASING_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ERASE_TIMEOUT_SIZE(size) \
  this->assertEvents_NOR_ERASE_TIMEOUT_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ERASE_DONE_SIZE(size) \
  this->assertEvents_NOR_ERASE_DONE_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_RESET_FAIL_SIZE(size) \
  this->assertEvents_NOR_RESET_FAIL_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_RESET_FAIL(index, _actual_state, _expected_state) \
  this->assertEvents_NOR_RESET_FAIL(__FILE__, __LINE__, index, _actual_state, _expected_state)

#define ASSERT_EVENTS_NOR_RESETTING_SIZE(size) \
  this->assertEvents_NOR_RESETTING_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_UNLOCK_BYPASS_FAILED_SIZE(size) \
  this->assertEvents_NOR_UNLOCK_BYPASS_FAILED_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_SIZE(size) \
  this->assertEvents_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_UNLOCK_BYPASS_RESET_FAILED_SIZE(size) \
  this->assertEvents_NOR_UNLOCK_BYPASS_RESET_FAILED_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA_SIZE(size) \
  this->assertEvents_NOR_FAILED_TO_VERIFY_DATA_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA(index, _dest_addr, _source) \
  this->assertEvents_NOR_FAILED_TO_VERIFY_DATA(__FILE__, __LINE__, index, _dest_addr, _source)

#define ASSERT_EVENTS_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE_SIZE(size) \
  this->assertEvents_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(size) \
  this->assertEvents_NOR_FAILED_TO_RESET_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_WRITE_TIMEOUT_SIZE(size) \
  this->assertEvents_NOR_WRITE_TIMEOUT_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_CHECKSUM_SIZE(size) \
  this->assertEvents_NOR_FAILED_TO_VERIFY_CHECKSUM_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_CHECKSUM_VERIFY_DONE_SIZE(size) \
  this->assertEvents_NOR_CHECKSUM_VERIFY_DONE_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_VERIFY_BUSY_SIZE(size) \
  this->assertEvents_NOR_VERIFY_BUSY_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_VERIFY_BUSY(index, _actual_state, _expected_state) \
  this->assertEvents_NOR_VERIFY_BUSY(__FILE__, __LINE__, index, _actual_state, _expected_state)

#define ASSERT_EVENTS_NOR_FAILED_TO_READ_DATA_SIZE(size) \
  this->assertEvents_NOR_FAILED_TO_READ_DATA_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_FAILED_TO_READ_DATA(index, _nor_addr, _dest) \
  this->assertEvents_NOR_FAILED_TO_READ_DATA(__FILE__, __LINE__, index, _nor_addr, _dest)

#define ASSERT_EVENTS_NOR_READ_TIMEOUT_SIZE(size) \
  this->assertEvents_NOR_READ_TIMEOUT_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_NOR_ALREADY_ERASING_SIZE(size) \
  this->assertEvents_NOR_ALREADY_ERASING_size(__FILE__, __LINE__, size)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingResponse_SIZE(size) \
  this->assert_from_PingResponse_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingResponse(index, _key) \
  { \
    ASSERT_GT(this->fromPortHistory_PingResponse->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_PingResponse\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_PingResponse->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_PingResponse& _e = \
      this->fromPortHistory_PingResponse->at(index); \
    ASSERT_EQ(_key, _e.key) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument key at index " \
    << index \
    << " in history of from_PingResponse\n" \
    << "  Expected: " << _key << "\n" \
    << "  Actual:   " << _e.key << "\n"; \
  }

#define ASSERT_from_verification_done_SIZE(size) \
  this->assert_from_verification_done_size(__FILE__, __LINE__, size)

#define ASSERT_from_verification_done(index, _valid_nor, _read_blc_checksum, _read_fsw_checksum, _cptd_blc_checksum, _cptd_fsw_checksum) \
  { \
    ASSERT_GT(this->fromPortHistory_verification_done->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_verification_done\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_verification_done->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_verification_done& _e = \
      this->fromPortHistory_verification_done->at(index); \
    ASSERT_EQ(_valid_nor, _e.valid_nor) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument valid_nor at index " \
    << index \
    << " in history of from_verification_done\n" \
    << "  Expected: " << _valid_nor << "\n" \
    << "  Actual:   " << _e.valid_nor << "\n"; \
    ASSERT_EQ(_read_blc_checksum, _e.read_blc_checksum) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument read_blc_checksum at index " \
    << index \
    << " in history of from_verification_done\n" \
    << "  Expected: " << _read_blc_checksum << "\n" \
    << "  Actual:   " << _e.read_blc_checksum << "\n"; \
    ASSERT_EQ(_read_fsw_checksum, _e.read_fsw_checksum) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument read_fsw_checksum at index " \
    << index \
    << " in history of from_verification_done\n" \
    << "  Expected: " << _read_fsw_checksum << "\n" \
    << "  Actual:   " << _e.read_fsw_checksum << "\n"; \
    ASSERT_EQ(_cptd_blc_checksum, _e.cptd_blc_checksum) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument cptd_blc_checksum at index " \
    << index \
    << " in history of from_verification_done\n" \
    << "  Expected: " << _cptd_blc_checksum << "\n" \
    << "  Actual:   " << _e.cptd_blc_checksum << "\n"; \
    ASSERT_EQ(_cptd_fsw_checksum, _e.cptd_fsw_checksum) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument cptd_fsw_checksum at index " \
    << index \
    << " in history of from_verification_done\n" \
    << "  Expected: " << _cptd_fsw_checksum << "\n" \
    << "  Actual:   " << _e.cptd_fsw_checksum << "\n"; \
  }

#define ASSERT_from_erase_done_SIZE(size) \
  this->assert_from_erase_done_size(__FILE__, __LINE__, size)

#define ASSERT_from_erase_done(index, _done, _context1, _context2) \
  { \
    ASSERT_GT(this->fromPortHistory_erase_done->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_erase_done\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_erase_done->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_erase_done& _e = \
      this->fromPortHistory_erase_done->at(index); \
    ASSERT_EQ(_done, _e.done) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument done at index " \
    << index \
    << " in history of from_erase_done\n" \
    << "  Expected: " << _done << "\n" \
    << "  Actual:   " << _e.done << "\n"; \
    ASSERT_EQ(_context1, _e.context1) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context1 at index " \
    << index \
    << " in history of from_erase_done\n" \
    << "  Expected: " << _context1 << "\n" \
    << "  Actual:   " << _e.context1 << "\n"; \
    ASSERT_EQ(_context2, _e.context2) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context2 at index " \
    << index \
    << " in history of from_erase_done\n" \
    << "  Expected: " << _context2 << "\n" \
    << "  Actual:   " << _e.context2 << "\n"; \
  }

#define ASSERT_from_read_done_SIZE(size) \
  this->assert_from_read_done_size(__FILE__, __LINE__, size)

#define ASSERT_from_read_done(index, _done, _context1, _context2) \
  { \
    ASSERT_GT(this->fromPortHistory_read_done->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_read_done\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_read_done->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_read_done& _e = \
      this->fromPortHistory_read_done->at(index); \
    ASSERT_EQ(_done, _e.done) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument done at index " \
    << index \
    << " in history of from_read_done\n" \
    << "  Expected: " << _done << "\n" \
    << "  Actual:   " << _e.done << "\n"; \
    ASSERT_EQ(_context1, _e.context1) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context1 at index " \
    << index \
    << " in history of from_read_done\n" \
    << "  Expected: " << _context1 << "\n" \
    << "  Actual:   " << _e.context1 << "\n"; \
    ASSERT_EQ(_context2, _e.context2) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context2 at index " \
    << index \
    << " in history of from_read_done\n" \
    << "  Expected: " << _context2 << "\n" \
    << "  Actual:   " << _e.context2 << "\n"; \
  }

#define ASSERT_from_worker_verify_SIZE(size) \
  this->assert_from_worker_verify_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_verify(index, _blc_filesize, _fsw_filesize) \
  { \
    ASSERT_GT(this->fromPortHistory_worker_verify->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_worker_verify\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_worker_verify->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_worker_verify& _e = \
      this->fromPortHistory_worker_verify->at(index); \
    ASSERT_EQ(_blc_filesize, _e.blc_filesize) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument blc_filesize at index " \
    << index \
    << " in history of from_worker_verify\n" \
    << "  Expected: " << _blc_filesize << "\n" \
    << "  Actual:   " << _e.blc_filesize << "\n"; \
    ASSERT_EQ(_fsw_filesize, _e.fsw_filesize) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument fsw_filesize at index " \
    << index \
    << " in history of from_worker_verify\n" \
    << "  Expected: " << _fsw_filesize << "\n" \
    << "  Actual:   " << _e.fsw_filesize << "\n"; \
  }

#define ASSERT_from_worker_write_SIZE(size) \
  this->assert_from_worker_write_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_write(index, _dest, _src, _count, _bank) \
  { \
    ASSERT_GT(this->fromPortHistory_worker_write->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_worker_write\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_worker_write->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_worker_write& _e = \
      this->fromPortHistory_worker_write->at(index); \
    ASSERT_EQ(_dest, _e.dest) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest at index " \
    << index \
    << " in history of from_worker_write\n" \
    << "  Expected: " << _dest << "\n" \
    << "  Actual:   " << _e.dest << "\n"; \
    ASSERT_EQ(_src, _e.src) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument src at index " \
    << index \
    << " in history of from_worker_write\n" \
    << "  Expected: " << _src << "\n" \
    << "  Actual:   " << _e.src << "\n"; \
    ASSERT_EQ(_count, _e.count) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument count at index " \
    << index \
    << " in history of from_worker_write\n" \
    << "  Expected: " << _count << "\n" \
    << "  Actual:   " << _e.count << "\n"; \
    ASSERT_EQ(_bank, _e.bank) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument bank at index " \
    << index \
    << " in history of from_worker_write\n" \
    << "  Expected: " << _bank << "\n" \
    << "  Actual:   " << _e.bank << "\n"; \
  }

#define ASSERT_from_write_done_SIZE(size) \
  this->assert_from_write_done_size(__FILE__, __LINE__, size)

#define ASSERT_from_write_done(index, _done, _context1, _context2) \
  { \
    ASSERT_GT(this->fromPortHistory_write_done->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_write_done\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_write_done->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_write_done& _e = \
      this->fromPortHistory_write_done->at(index); \
    ASSERT_EQ(_done, _e.done) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument done at index " \
    << index \
    << " in history of from_write_done\n" \
    << "  Expected: " << _done << "\n" \
    << "  Actual:   " << _e.done << "\n"; \
    ASSERT_EQ(_context1, _e.context1) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context1 at index " \
    << index \
    << " in history of from_write_done\n" \
    << "  Expected: " << _context1 << "\n" \
    << "  Actual:   " << _e.context1 << "\n"; \
    ASSERT_EQ(_context2, _e.context2) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context2 at index " \
    << index \
    << " in history of from_write_done\n" \
    << "  Expected: " << _context2 << "\n" \
    << "  Actual:   " << _e.context2 << "\n"; \
  }

#define ASSERT_from_worker_erase_SIZE(size) \
  this->assert_from_worker_erase_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_erase(index, _bank_addr) \
  { \
    ASSERT_GT(this->fromPortHistory_worker_erase->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_worker_erase\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_worker_erase->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_worker_erase& _e = \
      this->fromPortHistory_worker_erase->at(index); \
    ASSERT_EQ(_bank_addr, _e.bank_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument bank_addr at index " \
    << index \
    << " in history of from_worker_erase\n" \
    << "  Expected: " << _bank_addr << "\n" \
    << "  Actual:   " << _e.bank_addr << "\n"; \
  }

#define ASSERT_from_worker_cancel_SIZE(size) \
  this->assert_from_worker_cancel_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_reset_SIZE(size) \
  this->assert_from_worker_reset_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_reset(index, _dontcare_addr) \
  { \
    ASSERT_GT(this->fromPortHistory_worker_reset->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_worker_reset\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_worker_reset->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_worker_reset& _e = \
      this->fromPortHistory_worker_reset->at(index); \
    ASSERT_EQ(_dontcare_addr, _e.dontcare_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dontcare_addr at index " \
    << index \
    << " in history of from_worker_reset\n" \
    << "  Expected: " << _dontcare_addr << "\n" \
    << "  Actual:   " << _e.dontcare_addr << "\n"; \
  }

#define ASSERT_from_worker_read_SIZE(size) \
  this->assert_from_worker_read_size(__FILE__, __LINE__, size)

#define ASSERT_from_worker_read(index, _dest, _src, _count, _bank) \
  { \
    ASSERT_GT(this->fromPortHistory_worker_read->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_worker_read\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_worker_read->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_worker_read& _e = \
      this->fromPortHistory_worker_read->at(index); \
    ASSERT_EQ(_dest, _e.dest) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest at index " \
    << index \
    << " in history of from_worker_read\n" \
    << "  Expected: " << _dest << "\n" \
    << "  Actual:   " << _e.dest << "\n"; \
    ASSERT_EQ(_src, _e.src) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument src at index " \
    << index \
    << " in history of from_worker_read\n" \
    << "  Expected: " << _src << "\n" \
    << "  Actual:   " << _e.src << "\n"; \
    ASSERT_EQ(_count, _e.count) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument count at index " \
    << index \
    << " in history of from_worker_read\n" \
    << "  Expected: " << _count << "\n" \
    << "  Actual:   " << _e.count << "\n"; \
    ASSERT_EQ(_bank, _e.bank) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument bank at index " \
    << index \
    << " in history of from_worker_read\n" \
    << "  Expected: " << _bank << "\n" \
    << "  Actual:   " << _e.bank << "\n"; \
  }

namespace Drv {

  //! \class NORFlashManagerGTestBase
  //! \brief Auto-generated base class for NORFlashManager component Google Test harness
  //!
  class NORFlashManagerGTestBase :
    public NORFlashManagerTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashManagerGTestBase
      //!
      NORFlashManagerGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashManagerGTestBase
      //!
      virtual ~NORFlashManagerGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Commands
      // ----------------------------------------------------------------------

      //! Assert size of command response history
      //!
      void assertCmdResponse_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      //! Assert command response in history at index
      //!
      void assertCmdResponse(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Events
      // ----------------------------------------------------------------------

      void assertEvents_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_BUSY
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ERASE_BUSY_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_ERASE_BUSY(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 actual_state, /*!< The state of the NOR Manager*/
          const U32 expected_state, /*!< The expected state of the NOR Manager*/
          const U32 error_status /*!< The error status*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_FAIL
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ERASE_FAIL_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_ERASE_FAIL(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 error_status /*!< The error status*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASING
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ERASING_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_TIMEOUT
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ERASE_TIMEOUT_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_DONE
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ERASE_DONE_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_RESET_FAIL
      // ----------------------------------------------------------------------

      void assertEvents_NOR_RESET_FAIL_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_RESET_FAIL(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 actual_state, /*!< The state of the NOR Manager*/
          const U32 expected_state /*!< The expected state of the NOR Manager*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_RESETTING
      // ----------------------------------------------------------------------

      void assertEvents_NOR_RESETTING_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_FAILED
      // ----------------------------------------------------------------------

      void assertEvents_NOR_UNLOCK_BYPASS_FAILED_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_PROGRAM_FAILED
      // ----------------------------------------------------------------------

      void assertEvents_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_RESET_FAILED
      // ----------------------------------------------------------------------

      void assertEvents_NOR_UNLOCK_BYPASS_RESET_FAILED_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_VERIFY_DATA
      // ----------------------------------------------------------------------

      void assertEvents_NOR_FAILED_TO_VERIFY_DATA_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_FAILED_TO_VERIFY_DATA(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 dest_addr, /*!< The destination address*/
          const U8 source /*!< The data to be written*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_RESET_DURING_ERASE
      // ----------------------------------------------------------------------

      void assertEvents_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_RESET
      // ----------------------------------------------------------------------

      void assertEvents_NOR_FAILED_TO_RESET_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_WRITE_TIMEOUT
      // ----------------------------------------------------------------------

      void assertEvents_NOR_WRITE_TIMEOUT_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_VERIFY_CHECKSUM
      // ----------------------------------------------------------------------

      void assertEvents_NOR_FAILED_TO_VERIFY_CHECKSUM_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_CHECKSUM_VERIFY_DONE
      // ----------------------------------------------------------------------

      void assertEvents_NOR_CHECKSUM_VERIFY_DONE_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_VERIFY_BUSY
      // ----------------------------------------------------------------------

      void assertEvents_NOR_VERIFY_BUSY_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_VERIFY_BUSY(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 actual_state, /*!< The state of the NOR Manager*/
          const U32 expected_state /*!< The expected state of the NOR Manager*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_READ_DATA
      // ----------------------------------------------------------------------

      void assertEvents_NOR_FAILED_TO_READ_DATA_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_NOR_FAILED_TO_READ_DATA(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 nor_addr, /*!< The address in NOR to read from*/
          const U32 dest /*!< The memory buffer address use to store the value of nor_addr*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_READ_TIMEOUT
      // ----------------------------------------------------------------------

      void assertEvents_NOR_READ_TIMEOUT_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ALREADY_ERASING
      // ----------------------------------------------------------------------

      void assertEvents_NOR_ALREADY_ERASING_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From ports 
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: PingResponse 
      // ----------------------------------------------------------------------

      void assert_from_PingResponse_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: verification_done 
      // ----------------------------------------------------------------------

      void assert_from_verification_done_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: erase_done 
      // ----------------------------------------------------------------------

      void assert_from_erase_done_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: read_done 
      // ----------------------------------------------------------------------

      void assert_from_read_done_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_verify 
      // ----------------------------------------------------------------------

      void assert_from_worker_verify_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_write 
      // ----------------------------------------------------------------------

      void assert_from_worker_write_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: write_done 
      // ----------------------------------------------------------------------

      void assert_from_write_done_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_erase 
      // ----------------------------------------------------------------------

      void assert_from_worker_erase_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_cancel 
      // ----------------------------------------------------------------------

      void assert_from_worker_cancel_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_reset 
      // ----------------------------------------------------------------------

      void assert_from_worker_reset_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: worker_read 
      // ----------------------------------------------------------------------

      void assert_from_worker_read_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
