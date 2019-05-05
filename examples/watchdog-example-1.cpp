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


#include <iostream>
#include "logger.h"
#include "watchableprocess.h"
#include "process.h"
#include <unistd.h>
using namespace Saho::Common;
using namespace Saho::Dipc;
structlog Saho::Common::LoggerConfig = {};

class IpcInvoker1:public Invokable
{
    //cannot use templates due to virtual , how about arglist
    virtual void execute()
    {
      Logger(WARN)<<"IpcInvoker";
    }
};


int main()
{
  std::shared_ptr<LogInterface> l=std::make_shared<BasicLogger>();
  LoggerConfig.headers = true;
  LoggerConfig.level = ALL_LOG_LEVEL;
  LoggerConfig.logInterface=l;

  while(1)
  {
    //Process p;
    sleep(3);
  }


  // DVariable<int> var(10);
  // var=11;


  /*  WatchableProcess w;

  std::string name="hello";
  std::shared_ptr<IpcInvoker1> invo1=std::make_shared<IpcInvoker1>();
  w.addInvokable(invo1);
  //w.hello();
*/
  return 0;
}

