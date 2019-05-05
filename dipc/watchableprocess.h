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


#ifndef WATCHABLEPROCESS_H
#define WATCHABLEPROCESS_H

#include <memory>
#include <iostream>
#include <map>
#include <functional>

/* The D variable is the exposed variable in the system between the nodes, we need to keep track of the data change */

template <class T>
class DVariable
{
  public:
    DVariable(T aData)
    {
      data=aData;
      std::cout<<"Data is "<<data<<std::endl;
    }

    DVariable& operator =(const T &aNewData)
    {
      data=aNewData;
      std::cout<<"== New Data is "<<data<<std::endl;
      return *this;
    }
  private:
    T data;

};

namespace Saho
{
  namespace Dipc
  {
    class WatchableProcessInternal;

    /* Variable which is distributed across the sessions  , Future plans*/
    class Variable
    {
        std::string name; //exposed name of the variable
        std::shared_ptr<void> data; //reference to the data
    };

    /* Remotely triggerable function*/
    /* Limitation : How could we pass arguments */

    struct Invokable
    {
        std::string name;
        virtual void execute()=0;
    };

    class WatchableProcess
    {
      public:
        WatchableProcess();
        bool addInvokable(std::shared_ptr<Invokable> aInvoker);
        std::shared_ptr<WatchableProcessInternal> d;
    };

  }
}

#endif // WATCHABLEPROCESS_H
