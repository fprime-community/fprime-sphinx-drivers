// ====================================================================== 
// \title  RandomScenario.hpp
// \author bocchino
// \brief  Random scenario interface
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_RandomScenario_HPP
#define Test_RandomScenario_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "Fw/Types/Assert.hpp"
#include "fprime-sphinx-drivers/Test/Scenario/Scenario.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"

namespace Test {

  template<typename State> class RandomScenario :
    public Scenario<State>
  {

    public:

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      //! An array of rules
      class RuleArray {

        public:

          RuleArray(
              Rule<State>** rules, //!< The rules in the array
              const U32 size //!< The number of rules in the array
          ) :
            rules(rules),
            size(size)
          {

          }
          
        public:

          //! Get a random index into the array
          //! \return The index
          U32 getRandomIndex(void) {
            const U32 result = Utils::Random::inRange(0, this->size);
            FW_ASSERT(result < this->size);
            return result;
          }

        public:

          //! The rules in the array
          Rule<State>** rules;

          //! The number of rules in the array
          const U32 size;

      };

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors 
      // ----------------------------------------------------------------------

      //! Construct object RandomScenario
      RandomScenario(
          const Fw::EightyCharString& name, //!< The name of the scenario
          State& state, //!< The system state
          RuleArray& ruleArray //!< The rule array
      ) :
        Scenario<State>(name, state),
        ruleArray(ruleArray)
      {
        U32 seedValue = 0;
        bool seedValueOK = false;
        const int status = system("test -f seed");
        if (status == 0) {
          seedValueOK = getSeedValueFromFile("seed", seedValue);
        }
        if (!seedValueOK) {
          seedValue = Utils::Random::GetSeedValue::fromTime();
        }
        (void) appendSeedValueToFile("seed-history", seedValue);
        Utils::Random::seed(seedValue);
      }

      //! Destroy object RandomScenario
      ~RandomScenario(void) {

      }

    public:

      // ----------------------------------------------------------------------
      // Public instance methods 
      // ----------------------------------------------------------------------

      //! Get the next rule to apply
      //! \return The next rule, or NULL if none
      Rule<State>* getNextRule(void) {
        bool seen[ruleArray.size];
        memset(seen, 0, sizeof(seen));
        U32 numSeen = 0;
        Rule<State>* rule = NULL;
        while (numSeen < this->ruleArray.size) {
          const U32 i = this->ruleArray.getRandomIndex();
          if (seen[i]) {
            continue;
          }
          Rule<State>* candidateRule = this->ruleArray.rules[i];
          if (candidateRule->precondition(this->state)) {
            rule = candidateRule;
            break;
          }
          seen[i] = true;
          ++numSeen;
        }
        return rule;
      }

    private:

      // ----------------------------------------------------------------------
      // Private helper functions 
      // ----------------------------------------------------------------------

      //! Get a seed value from file
      //! \return true on success, false on failure
      bool getSeedValueFromFile(
          const char *const fileName, //!< The file name
          U32& seedValue //!< The seed value
      ) {
        bool result = true;
        FILE *fp = fopen(fileName, "r");
        if (fp != NULL) {
          result = (fscanf(fp, "%u", &seedValue) == 1);
          (void) fclose(fp);
        }
        else {
          result = false;
        }
        return result;
      }

      //! Get a seed value from the system time
      //! \return true on success, false on failure
      bool getSeedValueFromTime(
          U32& seedValue //!< The seed value
      ) {
        bool result = true;
        struct timeval tv;
        result = (gettimeofday(&tv, NULL) == 0);
        if (result) {
          seedValue = tv.tv_usec;
        }
        return result;
      }

      //! Append a seed value to a file
      bool appendSeedValueToFile(
          const char *const fileName, //!< The file name
          const U32 seedValue //!< The seed value
      ) {
        bool result = true;
        FILE *fp = fopen(fileName, "a");
        if (fp != NULL) {
          int status = fprintf(
              fp, 
              "[Scenario.%s] %u\n", 
              this->name.toChar(),
              seedValue
          );
          result = (status > 0);
          (void) fclose(fp);
        }
        else {
          result = false;
        }
        return result;
      }

    private:

      // ----------------------------------------------------------------------
      // Private member variables 
      // ----------------------------------------------------------------------

      //! The rule array
      RuleArray ruleArray;

  };

}

#endif
