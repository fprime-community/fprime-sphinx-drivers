// ====================================================================== 
// \title  Rules/SPIMutex.cpp
// \author ciankc
// \brief  Rules/SPIMutex class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "SPIMutex.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Claim__OK(void) const
  {
    bool result = true;
    result &= !(this->component.m_isOwned);
    //printf("Precondition for Claim OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Claim__OK(void)
  {
    I32 status;
    //printf("Action for claims OK\n");
    // Initialize test state
    this->clearHistory();

    //claim
    ASSERT_EQ(this->component.m_isOwned, false);
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);
  }  

  bool TestState ::
    precondition__Claim__Double(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for Claim Double result is: %d\n", result);
    return result;
  }
  
  void TestState ::
    action__Claim__Double(void)
  {
    I32 status;
    //printf("Action for claims Double\n");
    // Initialize test state
    this->clearHistory();

    //double claim
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, SPI_CLAIM_ALREADY_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, true);
  }

  bool TestState ::
  precondition__Unclaim__OK(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for Unclaim OK result is: %d\n", result);
    return result;
  }

  void TestState ::
  action__Unclaim__OK(void)
  {
    //printf("Action for unclaims OK\n");
    // Initialize test state
    this->clearHistory();
    //unclaim
    I32 status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, false);
  }

  bool TestState ::
  precondition__Unclaim__Double(void) const
  {
    bool result = true;
    result &= !(this->component.m_isOwned);
    //printf("Precondition for Unclaim Double result is: %d\n", result);
    return result;
  }

  void TestState ::
  action__Unclaim__Double(void)
  {
    //printf("Action for unclaims Double\n");
    // Initialize test state                                                                           
    this->clearHistory();

    //unclaim double
    I32 status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, SPI_UNCLAIM_NOT_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, false);
  }


  namespace SPIMutex {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      ClaimOK(void)
    {
      this->ruleClaimOK.apply(this->testState);
    }

    void Tester ::
    ClaimDouble(void)
    {
      this->ruleClaimOK.apply(this->testState);
      this->ruleClaimDouble.apply(this->testState);
    }

    void Tester ::UnclaimOK(void)
    {
      //apply rule
      this->ruleClaimOK.apply(this->testState);
      this->ruleUnclaimOK.apply(this->testState);
    }

    void Tester ::UnclaimDouble(void)
    {
      this->ruleClaimOK.apply(this->testState);
      this->ruleUnclaimOK.apply(this->testState);
      this->ruleUnclaimDouble.apply(this->testState);
    }

  }

}
