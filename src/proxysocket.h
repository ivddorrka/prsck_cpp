
#ifndef __INCLUDED_PROXYSOCKET_H
#define __INCLUDED_PROXYSOCKET_H


//#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netdb.h>
//#include <unistd.h>
//#include <cerrno>
//#include <iostream>
//#include <cstdlib>
#include <string>
//#include <cctype>
//#include <cstdarg>

#define SOCKET int
#ifndef INVALID_SOCKET
    #define INVALID_SOCKET -1
#endif


#define PROXYSOCKET_VERSION_MAJOR 0
/*! \brief minor version number */
#define PROXYSOCKET_VERSION_MINOR 1
/*! \brief micro version number */
#define PROXYSOCKET_VERSION_MICRO 10



#define PROXYSOCKET_TYPE_NONE           0x00
/*! \brief SOCKS4 proxy */
#define PROXYSOCKET_TYPE_SOCKS4         0x04
/*! \brief SOCKS5 proxy */
#define PROXYSOCKET_TYPE_SOCKS5         0x05
/*! \brief HTTP proxy */
#define PROXYSOCKET_TYPE_WEB_CONNECT    0x20
/*! \brief invalid proxy type */
#define PROXYSOCKET_TYPE_INVALID        -1


#define PROXYSOCKET_LOG_ERROR   0
#define PROXYSOCKET_LOG_WARNING 1
#define PROXYSOCKET_LOG_INFO    2
#define PROXYSOCKET_LOG_DEBUG   3

void proxysocket_get_version (int* pmajor, int* pminor, int* pmicro);

const std::string proxysocket_get_version_string ();

const std::string proxysocketconfig_get_type_name (int proxytype);

int proxysocketconfig_get_name_type (const char* proxytypename);

int proxysocket_initialize ();


typedef struct proxysocketconfig_struct* proxysocketconfig;

proxysocketconfig proxysocketconfig_create_direct ();


proxysocketconfig proxysocketconfig_create (int proxytype, const char* proxyhost, uint16_t proxyport, const char* proxyuser, const char* proxypass);

int proxysocketconfig_add_proxy (proxysocketconfig proxy, int proxytype, const char* proxyhost, uint16_t proxyport, const char* proxyuser, const char* proxypass);

typedef void (*proxysocketconfig_log_fn)(int level, const char* message, void* userdata);

std::string proxysocketconfig_get_description (proxysocketconfig proxy);

void proxysocketconfig_set_logging (proxysocketconfig proxy, proxysocketconfig_log_fn log_fn, void* userdata);

void proxysocketconfig_set_timeout (proxysocketconfig proxy, uint32_t sendtimeout, uint32_t recvtimeout);

void proxysocketconfig_use_proxy_dns (proxysocketconfig proxy, int proxy_dns);

void proxysocketconfig_free (proxysocketconfig proxy);

SOCKET proxysocket_connect (proxysocketconfig proxy, const char* dsthost, uint16_t dstport, char** errmsg);

void proxysocket_disconnect (proxysocketconfig proxy, SOCKET sock);

void socket_set_timeouts_milliseconds (SOCKET sock, uint32_t sendtimeout, uint32_t recvtimeout);

std::string socket_receiveline (SOCKET sock);

std::string socket_get_error_message ();

#endif
