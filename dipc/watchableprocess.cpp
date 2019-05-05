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


#include "watchableprocess.h"
#include "logger.h"

using namespace Saho::Common;

namespace Saho
{
  namespace Dipc
  {

    class WatchableProcessInternal
    {
      public :
        WatchableProcessInternal();
        bool addInvokable(std::shared_ptr<Invokable> aInvoker);
      private:
        //list of the Variables in the current node
        std::map<std::string,std::unique_ptr<Invokable> > sharedVariables;
    };

    WatchableProcessInternal::WatchableProcessInternal()
    {
      Logger(DEBUG) << "Hello WatchableProcessInternal!";
    }

    bool WatchableProcessInternal::addInvokable(std::shared_ptr<Invokable> aInvoker)
    {
      aInvoker->execute();
      return true;
    }


    WatchableProcess::WatchableProcess()
      :d(std::make_shared<WatchableProcessInternal>())
    {

    }

     bool WatchableProcess::addInvokable(std::shared_ptr<Invokable> aInvoker)
    {
      return d->addInvokable(aInvoker);
    }

  }
}
