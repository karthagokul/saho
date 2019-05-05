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
#include "watchdogapp.h"
#include <unistd.h>
#include "watchableprocess.h"
using namespace std;
using namespace Saho::Common;
structlog Saho::Common::LoggerConfig = {};
static WatchDogApp watchdog_app;

void sig_handler(int signum)
{
  Logger(WARN)<<"Exiting app";
  watchdog_app.stop();
  exit(0);
}

int main()
{
  signal(SIGTERM, sig_handler);
  signal(SIGINT, sig_handler);

  std::shared_ptr<LogInterface> l=std::make_shared<BasicLogger>();
  LoggerConfig.headers = true;
  LoggerConfig.level = ALL_LOG_LEVEL;
  LoggerConfig.logInterface=l;

  watchdog_app.start();
  HeartBeatServer s;
  if(!s.recive())
  {
    Logger(ERROR)<<"Failed to recive hert beat";
  }

  while(1) //Watchdog event loop
  {
    sleep(1);
  }

  return 0;
}

