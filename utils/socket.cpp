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


#include "socket.h"


#include "socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

namespace Saho
{
  namespace Utils
  {
    Socket::Socket() :
      m_sock ( -1 )
    {

      memset ( &m_addr,
               0,
               sizeof ( m_addr ) );

    }

    Socket::~Socket()
    {
      if ( is_valid() )
        ::close ( m_sock );
    }

    bool Socket::create()
    {
      m_sock = socket ( AF_INET,
                        SOCK_STREAM,
                        0 );

      if ( ! is_valid() )
        return false;


      // TIME_WAIT - argh
      int on = 1;
      if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return false;


      return true;

    }



    bool Socket::bind ( const int port )
    {

      if ( ! is_valid() )
      {
        return false;
      }



      m_addr.sin_family = AF_INET;
      m_addr.sin_addr.s_addr = INADDR_ANY;
      m_addr.sin_port = htons ( port );

      int bind_return = ::bind ( m_sock,
                                 ( struct sockaddr * ) &m_addr,
                                 sizeof ( m_addr ) );


      if ( bind_return == -1 )
      {
        return false;
      }

      return true;
    }


    bool Socket::listen() const
    {
      if ( ! is_valid() )
      {
        return false;
      }

      int listen_return = ::listen ( m_sock, MAXCONNECTIONS );


      if ( listen_return == -1 )
      {
        return false;
      }

      return true;
    }


    bool Socket::accept ( Socket& new_socket ) const
    {
      int addr_length = sizeof ( m_addr );
      new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

      if ( new_socket.m_sock <= 0 )
        return false;
      else
        return true;
    }


    bool Socket::send ( const std::string s ) const
    {
      int status = ::send ( m_sock, s.c_str(), s.size(), MSG_NOSIGNAL );
      if ( status == -1 )
      {
        return false;
      }
      else
      {
        return true;
      }
    }


    int Socket::recv ( std::string& s ) const
    {
      char buf [ MAXRECV + 1 ];

      s = "";

      memset ( buf, 0, MAXRECV + 1 );

      int status = ::recv ( m_sock, buf, MAXRECV, 0 );

      if ( status == -1 )
      {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
      }
      else if ( status == 0 )
      {
        return 0;
      }
      else
      {
        s = buf;
        return status;
      }
    }



    bool Socket::connect ( const std::string host, const int port )
    {
      if ( ! is_valid() ) return false;

      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons ( port );

      int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

      if ( errno == EAFNOSUPPORT ) return false;

      status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

      if ( status == 0 )
        return true;
      else
        return false;
    }

    void Socket::set_non_blocking ( const bool b )
    {

      int opts;

      opts = fcntl ( m_sock,
                     F_GETFL );

      if ( opts < 0 )
      {
        return;
      }

      if ( b )
        opts = ( opts | O_NONBLOCK );
      else
        opts = ( opts & ~O_NONBLOCK );

      fcntl ( m_sock,
              F_SETFL,opts );

    }

  }

}
