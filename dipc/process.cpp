/*****************************************************************************
 *
 *
 * Created: 05-05-2019 2019 by gokul
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


#include "process.h"

#include <vector>
#include <unistd.h>
#include <future>
#include <atomic>
#include "watchableprocess.h"
class ProcessInternal;

class ProcessHeartBeat
{
  public:
    std::atomic<bool> isrunning;
    std::future<void> result;

    void tick()
    {
      HeartBeatClient c;
      while(isrunning)
      {
        if(c.send())
          std::cout<<"Tick: "<<std::endl;
        else
          std::cout<<"Failed to send Heartbeat"<<std::endl;
        sleep(10);
      }
      return;
    }

    ProcessHeartBeat()
    {

    }

    void start()
    {
      isrunning=true;
      result=std::async(std::launch::async, std::bind(&ProcessHeartBeat::tick, this));
      return;
    }
    void stop()
    {
      isrunning=false;
      result.wait();
    }
};

class ProcessInternal
{
  private:
  public:
    ProcessInternal();
    ~ProcessInternal();
    void eventloop();
    void send(const char *data); //to be changed the data type
    void recive(const char *data); //to be changed the data type
  protected:
    std::unique_ptr<ProcessHeartBeat> ticker;
};

ProcessInternal::ProcessInternal()
  :ticker(std::make_unique<ProcessHeartBeat>())
{
  //could be called by user ?
  eventloop();
}

ProcessInternal::~ProcessInternal()
{
  ticker->stop();
}

void ProcessInternal::send(const char *data)
{

}

void ProcessInternal::recive(const char *data)
{

}

void ProcessInternal::eventloop()
{
  ticker->start();
}


Process::Process()
  : d(std::make_unique<ProcessInternal>())
{

}

Process::~Process()
{

}

void Process::send(const char *data)
{
  return d->send(data);
}

void Process::recive(const char *data)
{
  return d->recive(data);
}

void Process::eventloop()
{
  return d->eventloop();
}
