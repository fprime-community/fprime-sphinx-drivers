// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing SPIDriverGeneric
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Rules {
    
    namespace SPIMutex {
    
      struct ClaimOK :
        public Test::Rule<TestState>
      {
      
        ClaimOK(void) :
          Rule<TestState>("Claim.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Claim__OK();
        }
    
        void action(TestState& state) {
          state.action__Claim__OK();
        }
      
      };
    
    }
    
    namespace SPIMutex {    
     
      struct ClaimDouble :
        public Test::Rule<TestState>
      {
      
        ClaimDouble(void) :
          Rule<TestState>("Claim.Double")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Claim__Double();
        }
    
        void action(TestState& state) {
          state.action__Claim__Double();
        }
      
      };
    
    }

    namespace RWOwner {
      struct ERROR :
	public Test::Rule<TestState>
      {
	ERROR(void) :
	  Rule<TestState>("RWOwner.ERROR")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWOwner__ERROR();
	}

	void action(TestState& state) {
	  state.action__RWOwner__ERROR();
	}

      };
	
    }

    namespace RWOwner {
      struct TIMEOUT :
	public Test::Rule<TestState>
      {
	TIMEOUT(void) :
	  Rule<TestState>("RWOwner.TIMEOUT")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWOwner__TIMEOUT();
	}

	void action(TestState& state) {
	  state.action__RWOwner__TIMEOUT();
	}

      };
	
    }

    namespace RWOwner {
      struct SUCCESS8 :
	public Test::Rule<TestState>
      {
	SUCCESS8(void) :
	  Rule<TestState>("RWOwner.SUCCESS8")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWOwner__SUCCESS8();
	}

	void action(TestState& state) {
	  state.action__RWOwner__SUCCESS8();
	}

      };
	
    }

    namespace RWOwner {
      struct SUCCESS16 :
	public Test::Rule<TestState>
      {
	SUCCESS16(void) :
	  Rule<TestState>("RWOwner.SUCCESS16")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWOwner__SUCCESS16();
	}

	void action(TestState& state) {
	  state.action__RWOwner__SUCCESS16();
	}

      };
	
    }

    namespace RWOwner {
      struct SUCCESS32 :
	public Test::Rule<TestState>
      {
	SUCCESS32(void) :
	  Rule<TestState>("RWOwner.SUCCESS32")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWOwner__SUCCESS32();
	}

	void action(TestState& state) {
	  state.action__RWOwner__SUCCESS32();
	}

      };
	
    }

    namespace RWReverse {
      struct SUCCESS8 :
	public Test::Rule<TestState>
      {
	SUCCESS8(void) :
	  Rule<TestState>("RWReverse.SUCCESS8")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWReverse__SUCCESS8();
	}

	void action(TestState& state) {
	  state.action__RWReverse__SUCCESS8();
	}

      };
	
    }

    namespace RWReverse {
      struct SUCCESS16 :
	public Test::Rule<TestState>
      {
	SUCCESS16(void) :
	  Rule<TestState>("RWReverse.SUCCESS16")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWReverse__SUCCESS16();
	}

	void action(TestState& state) {
	  state.action__RWReverse__SUCCESS16();
	}

      };
	
    }

    namespace RWReverse {
      struct SUCCESS32 :
	public Test::Rule<TestState>
      {
	SUCCESS32(void) :
	  Rule<TestState>("RWReverse.SUCCESS32")
	{

	}
	
	bool precondition(const TestState& state) {
	  return state.precondition__RWReverse__SUCCESS32();
	}

	void action(TestState& state) {
	  state.action__RWReverse__SUCCESS32();
	}

      };
	
    }


    namespace SPIMutex {    
      struct UnclaimOK :
        public Test::Rule<TestState>
      {
      
        UnclaimOK(void) :
          Rule<TestState>("Unclaim.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Unclaim__OK();
        }
    
        void action(TestState& state) {
          state.action__Unclaim__OK();
        }
      
      };
    
    }

    namespace SPIMutex {    
      struct UnclaimDouble :
        public Test::Rule<TestState>
      {
      
        UnclaimDouble(void) :
          Rule<TestState>("Unclaim.Double")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Unclaim__Double();
        }
    
        void action(TestState& state) {
          state.action__Unclaim__Double();
        }
      
      };
    
    }

    namespace Pointer {    
      struct Invalid :
        public Test::Rule<TestState>
      {
      
        Invalid(void) :
          Rule<TestState>("Pointer.Invalid")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Pointer__Invalid();
        }
    
        void action(TestState& state) {
          state.action__Pointer__Invalid();
        }
      
      };
    
    }

    namespace Reset {    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Reset.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reset__OK();
        }
    
        void action(TestState& state) {
          state.action__Reset__OK();
        }
      
      };
    
    }

  }
}

#endif
