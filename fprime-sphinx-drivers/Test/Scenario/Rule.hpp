// ====================================================================== 
// \title  Rule.hpp
// \author bocchino
// \brief  Rule interface for scenario testing
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_Rule_HPP
#define Test_Rule_HPP

#include "gtest/gtest.h"

#include "Fw/Types/EightyCharString.hpp"

namespace Test {

  template<typename State> class Rule {

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors 
      // ----------------------------------------------------------------------

      //! Construct object Rule
      Rule(
          const Fw::EightyCharString& name //!< The name of the rule
      ) :
        name(name)
      {

      }

      //! Destroy object Rule
      virtual ~Rule(void) {

      }

    public:

      // ----------------------------------------------------------------------
      // Public instance methods 
      // ----------------------------------------------------------------------

      //! Apply the rule
    void apply(
	       State& state //!< The system state
	       ) {
      ASSERT_TRUE(this->precondition(state)) 
	<< "Precondition failed applying rule " << this->name.toChar();
      this->action(state);
    }

      //! Evaluate the precondition associated with the rule
      //! \return Whether the condition holds
      virtual bool precondition(
          const State& state //!< The system state
      ) = 0;

      //! Perform the action associated with the rule
      virtual void action(
          State& state //!< The system state
      ) = 0;

    public:

      // ----------------------------------------------------------------------
      // Protected member variables 
      // ----------------------------------------------------------------------

      //! The name of the rule
      const Fw::EightyCharString name;

  };

}

#endif
