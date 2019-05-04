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


#ifndef SOCKET_H
#define SOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

namespace Saho
{
  namespace Utils
  {
    class Socket
    {
      public:
        Socket();
        virtual ~Socket();

        // Server initialization
        bool create();
        bool bind ( const int port );
        bool listen() const;
        bool accept ( Socket& ) const;

        // Client initialization
        bool connect ( const std::string host, const int port );

        // Data Transimission
        bool send ( const std::string ) const;
        int recv ( std::string& ) const;


        void set_non_blocking ( const bool );

        bool is_valid() const { return m_sock != -1; }

      private:

        int m_sock;
        sockaddr_in m_addr;

    };

  }
}


#endif // SOCKET_H
