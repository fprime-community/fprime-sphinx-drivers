// ======================================================================
// \title  LinuxDrvReg/SphinxDrvReg.cpp
// \author ciankc
// \brief  cpp file for Sphinx Linux Registers
//          
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================   

#include <fprime-sphinx-drivers/Util/SphinxDrvReg.hpp>
#include <stdlib.h>

#define MAX_NUM_REGISTERS 50

namespace Drv{

  SphinxDrvReg ::
  SphinxDrvReg(fileEntry* msg, U32 length)
  {
    FW_ASSERT(msg != NULL);
    this->regPair = msg;
    this->regLength = length;
  }

  SphinxDrvReg ::
  ~SphinxDrvReg(void) 
  {

  }

  void SphinxDrvReg::writeFile(void)
  {
    FW_ASSERT(regLength < MAX_NUM_REGISTERS);
    
    //get path
    I8* env = (I8*) getenv("REGISTER_FILE_PATH");
    if(env == NULL)
    {
        return;
    }

    Os::File file;
    fileEntry* regWrite = this->regPair;

    I8 dirname[100] = "";
    I32 env_size = strnlen((const char*)env, sizeof(dirname));
    (void)strncpy((char *)dirname, (char *)env, env_size);
    (void)strncat((char *)dirname, "/fprime-sphinx-drivers/Util/0x", 30);
    for(U32 i = 0; i < this->regLength; i++)
    {
      //create filename
      I8 filename[150] = "";
      I8 regFile[20] = "";
      strncpy((char *)filename, (char *)dirname, sizeof(filename));
      I32 stat = snprintf((char *)regFile, 20, "%X", regWrite->reg);
      FW_ASSERT(stat > 0, stat);
      (void)strncat((char *)filename, (char *)regFile, 20);
      (void)strncat((char *)filename, "_reg.bin", 8);

      //open file
      Os::File::Status ret = file.open((char *) filename, Os::File::OPEN_WRITE);
      FW_ASSERT(Os::File::OP_OK == ret, ret);

      //prepare data 
      NATIVE_INT_TYPE fileSize = 4;
      U32 initValue = regWrite->init;
      U32* data = &initValue;

      //write file
      ret = file.write(data, fileSize);
      FW_ASSERT(Os::File::OP_OK == ret);
      FW_ASSERT(fileSize == (NATIVE_INT_TYPE) sizeof(initValue));
     
      Os::Log::logMsg("Init Value 0x%X Written to: 0x%s\n", (U64) initValue, (U64) &regFile, 0,0,0,0);
      file.close();
      regWrite++;
    }

  }

  void SphinxDrvReg::clearFiles(void)
  {
    //get path
    I8* env = (I8*) getenv("REGISTER_FILE_PATH");
    if(env == NULL)
    {
        return;
    }
    
    //cd into correct dir
    I8 cd[100] = "";
    I32 env_size = strnlen((const char *)env, sizeof(cd));
    (void)strncat((char *)cd, (const char *)env, env_size);
    (void)strncat((char *)cd, "/fprime-sphinx-drivers/Util/*.bin", 33);
    
    //remove bin files
    I8 cmd[100] = "rm -rf ";
    I32 cmd_size = strnlen((const char*)cmd, sizeof(cmd));
    I32 cd_size = strnlen((const char*)cd, sizeof(cd));
    I32 total_size = cmd_size + cd_size;
    FW_ASSERT(total_size <= (I32)sizeof(cmd), total_size, sizeof(cmd));
    (void)strncat((char *)cmd, (const char *)cd, cd_size);
    
    //execute command
    I32 ret = system((char *) cmd);
    FW_ASSERT(ret == 0, ret);
  }

}
