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

//Heartbeat
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>

#define HEARTBEAT_PORT 5555
#define HEARTBEAT_SERVER "127.0.0.1"

struct HeartBeatClient
{
    HeartBeatClient()
    {

    }
    bool send()
    {
      int sock;
      size_t length, n;
      struct sockaddr_in server, from; // IP Addressing(ip, port, type) Stuff
      struct hostent *hp; // DNS stuff
      char buffer[256];
      sock= socket(AF_INET, SOCK_DGRAM, 0);
      if (sock < 0) return false;
      server.sin_family = AF_INET;
      hp = gethostbyname(HEARTBEAT_SERVER);
      if (hp==0) return false;
      bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
      server.sin_port = htons(HEARTBEAT_PORT);
      length=sizeof(struct sockaddr_in);
      bzero(buffer,256);
      strcpy(buffer,"HELLO");
      n=sendto(sock,buffer,strlen(buffer),0, (struct sockaddr*)&server,length);
      if (n < 0) return false;
      return true;

      //if return false, then something wrong with watch dog , exit from process itself.
    }
};


struct HeartBeatServer
{
    HeartBeatServer()
    {

    }
    bool recive()
    {
     unsigned  int sock, length, fromlen, n;
      struct sockaddr_in server;
      struct sockaddr_in from;
      char buf[1024];
      sock=socket(AF_INET, SOCK_DGRAM, 0);
      if (sock < 0)return false;
      length = sizeof(server);
      bzero(&server,length);
      server.sin_family=AF_INET;
      server.sin_addr.s_addr=INADDR_ANY;
      server.sin_port=htons(HEARTBEAT_PORT);
      if (bind(sock,(struct sockaddr *)&server,length)<0)
        return false;
      fromlen = sizeof(struct sockaddr_in);
      while (1) {
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        if (n < 0) return false;
        printf("Recived %s\n",buf);
        bzero(&buf,0);
      }
      return true;
    }
};

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
