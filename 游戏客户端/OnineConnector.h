

#ifndef __ONLINECONNECTOR_H
#define __ONLINECONNECTOR_H
#pragma warning(disable : 4996)


#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <process.h>





bool connectserver(SOCKET& Csock, SOCKADDR_IN& Server_adr);




#endif // !__ONLINECONNECTOR_H

