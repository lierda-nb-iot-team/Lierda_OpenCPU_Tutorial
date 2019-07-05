/******************************************************************************
 * @brief    Socket Functions for Hi21XX
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_SOCKET_H_
#define LIB_NEUL_SOCKET_H_

#include "neul_ip_addr.h"
#include "neul_socket_types.h"
#include "neul_error_types.h"
#include "neul_radio_types.h"

/** @defgroup libNEUL_SOCKET Hi21XX libNEUL Network Socket
 * Hi21XX libNeul Socket API
 * @ingroup LIBNEUL
 * @{
 * */

/** @brief socket recv notify callback type
 * @param socket that has received data
 * @param length amount of data to be read
 * @param addr passed into callback
 * @param addr_len length of sockaddr
*/
typedef void (*socket_recv_notify_fn)(int socket, ssize_t length, const struct sockaddr *addr, socklen_t addr_len);

/** @brief socket sent notify callback type
 * @param socket that has send data
 * @param seq_num data sequence number
 * @param status boolean indicating success or failure
*/
typedef void (*socket_sent_notify_fn)(int socket, uint8 seq_num, bool status);

/** @brief socket status notify callback type
 * @param socket that status need report
 * @param status to report
 * @param arg socket send/recv/drop data len, or errno
*/
typedef void (*socket_status_notify_fn)(int socket, SOCKET_STATUS status, int arg);

/** @brief initialise sockets
  */
void socket_init(void);

/**
 * @brief Create a socket. If all available sockets are in use, this will return an error
 * @param domain Protocol family. AF_INET for IPv4, AF_INET6 for IPv6
 * @param socket SOCKET_TYPE.
 * @param protocol protcol numbr. UDP/17, TCP/6 supported.
 * @return socket number or NEUL_SOCKET_RET_ERROR if a socket can't be allocated.
 */
int socket(PROTOCOL_FAMILY domain, SOCKET_TYPE type, PROTOCOL_TYPE protocol);

/** @brief Bind a socket to a port. The notify callback can be null, or a pointer to a callback
 * that will be called when there is data to receive.
 * @param socket socket number from socket()
 * @param sock_address   address structure, needs to set IP_ADDR_ANY and the local port
 * @param sock_len    lenght of socket address
 * @param socket_notify function to be called on packet receive, or null
 * @return NEUL_SOCKET_RET_OK or NEUL_SOCKET_RET_ERROR for error
 */
int neul_bind(int socket, const struct sockaddr *sock_address, socklen_t sock_len, socket_recv_notify_fn socket_notify);

/*
 * allow a BSD bind without callback
 */
#define bind(socket, sock_address, sock_len) neul_bind(socket, sock_address, sock_len, NULL)

/** @brief initiate a connection on a socket.
 * @param sock_num socket number from socket()
 * @param dest_addr remote ip address to connect
 * @param dest_addr_length The lenght of socket address
 * @return NEUL_SOCKET_RET_OK or NEUL_SOCKET_RET_ERROR for error
 */
ssize_t connect(int socket, const struct sockaddr *dest_addr, uint16 dest_addr_length);

/** @brief send data to a specified remote host/port
 * @param socket socket number from socket()
 * @param message data to be sent
 * @param length length of data to be sent
 * @param dest_addr   address to send datagram
 * @param dest_len    length of destination socket
 * @param flags       controls aspects of operation. no flags specified so far
 * @return number of bytes of data transmitted in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
 ssize_t sendto_with_indication(int socket, uint8 seq_num, const void *message, size_t length, SOCK_MSG_FLAG flags, const struct sockaddr *dest_addr, socklen_t dest_len);


/** @brief send data to a specified remote host/port
 * @param socket socket number from socket()
 * @param length length of data to be sent
 * @param dest_addr   address to send datagram
 * @param dest_len    length of destination socket
 * @param flags       controls aspects of operation. no flags specified so far
 * @return number of bytes of data transmitted in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
 ssize_t sendto(int socket, const void *message, size_t length, SOCK_MSG_FLAG flags, const struct sockaddr *dest_addr, socklen_t dest_len);

/** @brief send data on a socket with indication, it indicates if the message reach base station.
 * @param socket socket number from socket()
 * @param seq_num data sequence number
 * @param message data to be sent
 * @param length length of data to be sent
 * @param flags       controls aspects of operation. no flags specified so far
 * @return number of bytes of data transmitted in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
ssize_t send_with_indication(int socket, uint8 seq_num, const void *message, size_t length, SOCK_MSG_FLAG flags);

/** @brief send data on a socket
 * @param socket socket number from socket()
 * @param message data to be sent
 * @param length length of data to be sent
 * @param flags       controls aspects of operation. no flags specified so far
 * @return number of bytes of data transmitted in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
ssize_t send(int socket, const void *message, size_t length, SOCK_MSG_FLAG flags);

/** @brief Receive data. Can be called in blocking or non-blocking mode. Notify callback will trigger
 * when recvfrom() would return data.
 * @param socket socket number from socket()
 * @param buffer buffer of length length
 * @param length length of buffer
 * @param flags  controls aspects of operation. e.g. Block/Non-Block operation
 * @param src_addr  address datagram recevied from, can be NULL
 * @param src_len   length of destination socket. Needs to be set to size of buffer passed in to dest_addr, returns with actual length.
 * @return number of bytes of data returned in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
ssize_t recvfrom(int socket, void *buffer, size_t length, SOCK_MSG_FLAG flags, struct sockaddr *src_addr, socklen_t src_len);

/** @brief Receive data from socket
 * @param socket socket number from socket()
 * @param buffer buffer of length length
 * @param length length of buffer
 * @param flags  controls aspects of operation. e.g. Block/Non-Block operation
 * @return number of bytes of data returned in buffer, NEUL_SOCKET_RET_OK if no data is available, and NEUL_SOCKET_RET_ERROR if there is an error
 */
ssize_t recv(int socket, void *buffer, size_t length, SOCK_MSG_FLAG flags);

 /** @brief Close a socket.
  * @param socket socket number from socket()
  * @return NEUL_SOCKET_RET_OK or NEUL_SOCKET_RET_ERROR for error
  */
int close_socket(int socket);

 /** @brief remaining data to be read from a socket.
  * @param socket socket number from socket()
  * @return length >= 0 or NEUL_SOCKET_RET_ERROR if there is an error.
  */
int socklen(int socket);

/**
 * set callbacks for socket
 * @param sock_num Socket been set callbacks
 * @param socket_sent_notify_callback Function to call to return sent result
 * @param socket_status_notify_callback Function to call to report socket status
 */
NEUL_RET sock_callback_set(int sock_num, socket_sent_notify_fn socket_sent_notify_callback, socket_status_notify_fn socket_status_notify_callback);

/**
 * get SOCKET_TYPE
 * @param sock_num Socket number from socket()
 * @return socket type(SOCK_NONE=0,SOCK_STREAM=1,SOCK_DGRAM=2,SOCK_RAW=3).
 */
SOCKET_TYPE get_sock_type(uint8 sock_num);

/**
 * get tcp pending data seqs
 * @param sock_num Socket number from socket()
 * @param data_seqs Sequence number
 * @return true, or false if there is an error.
 */
bool get_tcp_pending_data_seqs(uint8 sock_num, uint8* data_seqs);

/**
 * @brief get socket status
 * @param socketid Socket id
 * @param status socket status
 * @param backoff remaining backoff time value, uint : s, valid only when status is SOCKET_OR_CID_STATUS_BACK_OFF
 * @return NUEL_RET
 */
NEUL_RET get_socket_status(uint8 socketid, SOCKET_OR_CID_STATUS *status, uint16 *backoff);

/** @} end of group libNEUL_SOCKET */

#endif /* LIB_NEUL_SOCKET_H_ */
