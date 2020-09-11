// ====================================================================== 
// \title  InterleavedScenario.hpp
// \author bocchino
// \brief  Interleaved scenario interface
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_InterleavedScenario_HPP
#define Test_InterleavedScenario_HPP

#include <string.h>

#include "Fw/Types/Assert.hpp"
#include "fprime-sphinx-drivers/Test/Scenario/Scenario.hpp"

namespace Test {

  template<typename State> class InterleavedScenario :
    public Scenario<State>
  {

    public:

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      //! An array of scenarios
      class ScenarioArray {

        public:

          ScenarioArray(
              Scenario<State>** scenarios, //!< The scenarios in the array
              const U32 size //!< The number of scenarios in the array
          ) :
            scenarios(scenarios),
            size(size)
          {

          }
          
        public:

          //! Get a random index into the array
          //! \return The index
          U32 getRandomIndex(void) {
            const U32 randInt = rand();
            const F64 ratio = static_cast<F64>(randInt) / RAND_MAX;
            const F64 randFloat = ratio * this->size;
            const U32 result = static_cast<U32>(randFloat);
            FW_ASSERT(result < this->size);
            return result;
          }

        public:

          //! The scenarios in the array
          Scenario<State>** scenarios;

          //! The number of scenarios in the array
          const U32 size;

      };

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors 
      // ----------------------------------------------------------------------

      //! Construct object InterleavedScenario
      InterleavedScenario(
          const Fw::EightyCharString& name, //!< The name of the scenario
          State& state, //!< The system state
          ScenarioArray& scenarioArray //!< The scenario array
      ) :
        Scenario<State>(name, state),
        scenarioArray(scenarioArray)
      {

      }

      //! Destroy object InterleavedScenario
      ~InterleavedScenario(void) {

      }

    public:

      // ----------------------------------------------------------------------
      // Public instance methods 
      // ----------------------------------------------------------------------

      //! Get the next rule to apply
      //! \return The next rule, or NULL if none
      Rule<State>* getNextRule(void) {
        Rule<State>* rule = NULL;
        bool seen[scenarioArray.size];
        memset(seen, 0, sizeof(seen));
        U32 numSeen = 0;
        while (numSeen < this->scenarioArray.size) {
          const U32 i = this->scenarioArray.getRandomIndex();
          if (seen[i]) {
            continue;
          }
          rule = this->scenarioArray.scenarios[i]->getNextRule();
          if (rule != NULL) {
            break;
          }
          seen[i] = true;
          ++numSeen;
        }
        return rule;
      }

    private:

      // ----------------------------------------------------------------------
      // Private member variables 
      // ----------------------------------------------------------------------

      //! The scenario array
      ScenarioArray scenarioArray;

  };

}

#endif
