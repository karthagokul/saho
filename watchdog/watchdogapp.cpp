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


#include "watchdogapp.h"
#include<future>
#include <signal.h>
#include "logger.h"
using namespace Saho::Common;
//Dirty way


// sigquit() function definition
void sigquit(int signum)
{
  exit(0);
}

int exec_prog(const char **argv ,int &pid)
{
  pid_t   my_pid;
  int     status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

  if (0 == (my_pid = fork())) {
    // signal(SIGHUP, sighup);
    //signal(SIGINT, sigint);
    signal(SIGQUIT, sigquit);
    if (-1 == execve(argv[0], (char **)argv , NULL)) {
      perror("child process execve failed [%m]");
      return -1;
    }
  }
  // TO AVOID DEfunc child
  signal(SIGCHLD, SIG_IGN);

#ifdef WAIT_FOR_COMPLETION
  timeout = 1000;

  while (0 == waitpid(my_pid , &status , WNOHANG)) {
    if ( --timeout < 0 ) {
      perror("timeout");
      return -1;
    }
    sleep(1);
  }

  printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
         argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

  if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
    perror("%s failed, halt system");
    return -1;
  }

#endif
  pid=my_pid;
  return 0;
}


class WatchDogServer
{
  public:
    WatchDogServer();
    void start();
    void stop();
};


bool Runnable::start()
{
  LOG_FUNCTION_NAME;
  const char    *arg1[64] = {name.c_str(), NULL};
  exec_prog(arg1,pid);
  //std::cout<<"PID IS "<<pid<<std::endl;
  return true;
}


bool Runnable::stop()
{
  LOG_FUNCTION_NAME;
  kill(pid,SIGQUIT);
  return true;
}

Runnable::~Runnable()
{
  stop();
}


WatchDogApp::WatchDogApp()
{
  //create processes
  //start the server
}

bool WatchDogApp::start()
{
  LOG_FUNCTION_NAME;
  std::shared_ptr<Runnable> r1=std::make_shared<Runnable>();
  std::shared_ptr<Runnable> r2=std::make_shared<Runnable>();

  r1->name ="/home/gokul/workspace/saho-build/examples/examples-watchdog-1";
  r2->name ="/home/gokul/workspace/saho-build/examples/examples-watchdog-1";
  r1->start();
  r2->start();

  listofRunnable.push_back(r1);
  listofRunnable.push_back(r2);

  return true;
}

bool WatchDogApp::stop()
{
  LOG_FUNCTION_NAME;
  return true;
}

bool WatchDogApp::restart()
{
  LOG_FUNCTION_NAME;
  return true;
}
