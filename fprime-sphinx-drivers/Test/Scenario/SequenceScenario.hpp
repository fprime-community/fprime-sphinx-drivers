// ====================================================================== 
// \title  SequenceScenario.hpp
// \author bocchino
// \brief  Sequence scenario interface
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_SequenceScenario_HPP
#define Test_SequenceScenario_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Scenario.hpp"

namespace Test {

  template<typename State> class SequenceScenario :
    public Scenario<State>
  {

    public:

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      //! A scenario sequence
      class Sequence {

        public:

          Sequence(
              Rule<State>** rules, //!< The rules in the sequence
              const U32 size //!< The number of rules in the sequence
          ) :
            rules(rules),
            size(size),
            index(0)
          {

          }

        public:

          //! Get the next rule in the sequence
          Rule<State>* getNextRule(void) {
            Rule<State>* rule = NULL;
            if (index < size) {
              rule = rules[index];
              ++index;
            }
            return rule;
          }

        private:

          //! The rules in the sequence
          Rule<State>** rules;

          //! The number of rules in the sequence
          const U32 size;

          //! The index into the rule array
          U32 index;

      };

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors 
      // ----------------------------------------------------------------------

      //! Construct object SequenceScenario
      SequenceScenario(
          const Fw::EightyCharString& name, //!< The name of the scenario
          State& state, //!< The system state
          Sequence& sequence //!< The rule sequence
      ) :
        Scenario<State>(name, state),
        sequence(sequence)
      {

      }

      //! Destroy object SequenceScenario
      ~SequenceScenario(void) {

      }

    public:

      // ----------------------------------------------------------------------
      // Public instance methods 
      // ----------------------------------------------------------------------

      //! Get the next rule to apply
      //! \return The next rule, or NULL if none
      Rule<State>* getNextRule(void) {
        return this->sequence.getNextRule();
      }

    private:

      // ----------------------------------------------------------------------
      // Private member variables 
      // ----------------------------------------------------------------------

      //! The rule sequence
      Sequence sequence;

  };

}

#endif
