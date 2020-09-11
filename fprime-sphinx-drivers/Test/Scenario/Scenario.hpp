// ====================================================================== 
// \title  Scenario.hpp
// \author bocchino
// \brief  Scenario interface for scenario testing
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_Scenario_HPP
#define Test_Scenario_HPP

#include <stdlib.h>

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"

namespace Test {

  template<typename State> class Scenario {

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors 
      // ----------------------------------------------------------------------

      //! Construct object Scenario
      Scenario(
          const Fw::EightyCharString& name, //!< The name of the scenario
          State& state //!< The system state
      ) :
        name(name),
        state(state),
        showRules(false)
      {
        const int status = system("test -f show-rules");
        if (status == 0) {
          showRules = true;
        }
      }

      //! Destroy object Scenario
      virtual ~Scenario(void) {

      }

    public:

      // ----------------------------------------------------------------------
      // Public instance methods 
      // ----------------------------------------------------------------------

      //! Get the next rule to apply
      //! \return The next rule, or NULL if none
      virtual Rule<State>* getNextRule(void) = 0;

      //! Run the scenario
      void run(void) {
        Rule<State>* rule = this->getNextRule();
        while (rule != NULL) {
          this->apply(*rule, this->state);
          rule = this->getNextRule();
        }
      }

      //! Run the scenario with a bound
      void runWithBound(
          const U32 maxSteps //!< The max number of steps
      ) {
        Rule<State>* rule = this->getNextRule();
        U32 numSteps = 0;
        while (rule != NULL && numSteps < maxSteps) {
          this->apply(*rule, this->state);
          rule = this->getNextRule();
          ++numSteps;
        }
      }

    protected:

      // ----------------------------------------------------------------------
      // Protected helper functions 
      // ----------------------------------------------------------------------

      //! Apply a rule
      void apply(
          Rule<State>& rule, //!< The rule
          State& state //!< The state
      ) {
        if (this->showRules) {
          printf(
              "[Scenario %s] Applying rule %s\n",
              this->name.toChar(),
              rule.name.toChar()
          );
        }
        rule.apply(state);
      }

    public:

      // ----------------------------------------------------------------------
      // Public member variables 
      // ----------------------------------------------------------------------
      
      //! The name of the scenario
      const Fw::EightyCharString name;

    protected:

      // ----------------------------------------------------------------------
      // Protected member variables 
      // ----------------------------------------------------------------------

      //! The system state
      State& state;

      // ----------------------------------------------------------------------
      // Private member variables 
      // ----------------------------------------------------------------------

    private:

      //! Whether to report rule applications
      bool showRules;

  };

}

#endif
