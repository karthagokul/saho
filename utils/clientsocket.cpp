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


#include "clientsocket.h"
#include "socketexception.h"

namespace Saho
{
  namespace Utils
  {
    ClientSocket::ClientSocket ( std::string host, int port )
    {
      if ( ! Socket::create() )
      {
        throw SocketException ( "Could not create client socket." );
      }

      if ( ! Socket::connect ( host, port ) )
      {
        throw SocketException ( "Could not bind to port." );
      }

    }


    const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
    {
      if ( ! Socket::send ( s ) )
      {
        throw SocketException ( "Could not write to socket." );
      }

      return *this;

    }


    const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
    {
      if ( ! Socket::recv ( s ) )
      {
        throw SocketException ( "Could not read from socket." );
      }

      return *this;
    }
  }

}
