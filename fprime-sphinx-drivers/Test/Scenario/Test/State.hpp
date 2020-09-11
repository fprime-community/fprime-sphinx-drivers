// ====================================================================== 
// \title  State.hpp
// \author bocchino
// \brief  State for scenario testing testing
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_State_HPP
#define Test_State_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"

#include "Fw/Types/BasicTypes.hpp"

namespace Test {

  struct State {

    State(void) :
      x(false)
    {

    }

    bool x;

  };

}

#endif
