/*****************************************************************************
 *
 *
 * Created: 04-05-2019 2019 by gokul
 *
 * Copyright 2019 gokul. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/



#ifndef GOLOGGER_H
#define GOLOGGER_H

#include <iostream>
#include <ostream>
#include <memory>

using namespace std;
namespace Saho
{
  namespace Common
  {
    enum typelog
    {
      INFO = 0x1,
      ERROR = 0x2,
      WARN = 0x4,
      DEBUG = 0x8,
      DEFAULT_LOG_LEVEL =  INFO | ERROR | WARN,
      ALL_LOG_LEVEL = INFO | ERROR | WARN | DEBUG
    };

    class LogInterface
    {
      public:
        virtual void log(const string &msg)=0;
    };

    struct structlog
    {
        bool headers = false;
        bool timestamp=false;
        typelog level = WARN;
        int debug_depth=1;
        std::shared_ptr<LogInterface> logInterface;
    };
    extern structlog LoggerConfig;


    struct LoggerConfiguration
    {
        bool headers = false;
        bool timestamp=false;
        typelog level = WARN;
        int debug_depth=1;
    };

    class Logger
    {
      public:
        Logger(typelog type);

        ~Logger();
        template<class T>
        Logger &operator<<(const T &msg)
        {
          if(LoggerConfig.logInterface)
          {
            LoggerConfig.logInterface->log(msg);
          }
          opened = true;
          return *this;
        }
      private:
        bool opened = false;
        int depth=0;
        typelog msglevel = DEBUG;
        inline string getLabel(typelog type) {
          string label;
          switch(type) {
            case DEBUG: label = "DEBUG"; break;
            case INFO:  label = "INFO "; break;
            case WARN:  label = "WARN "; break;
            case ERROR: label = "ERROR"; break;
          }
          return label;
        }
    };


    class BasicLogger:public LogInterface
    {
        virtual void log(const string &msg)
        {
          std::cout<<msg;
        }
    };

  }
}

#define DEBUG_LEVEL_1 1
#define DEBUG_LEVEL_2 2
#define DEBUG_LEVEL_3 3
//#define LOG_FUNCTION_NAME { LOG(DEBUG,DEBUG_LEVEL_3) << __PRETTY_FUNCTION__;}

#endif  /* GOLOGGER_H */
