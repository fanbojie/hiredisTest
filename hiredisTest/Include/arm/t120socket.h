/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  t120socket.h                                                           */
/*  this utility is try to wrap the socket api so that up layer can be     */
/*  platform independent.                                                   */
/*                                                                         */
/*  History                                                                */
/*      08/20/2002     created by Jack Feng                                */
/*                                                                         */
/*  Copyright (C) 2002 by WebEx Communications Inc.                        */
/*  All rights reserved                                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __T120_SOCKET_H__
#define __T120_SOCKET_H__

#include "t120poller.h"
#include "t120buffer.h"

typedef int T120_SOCKET;
#define T120_INVALID_SOCKET -1

/*
Following constants are possible errorno used. they should be already defined
in each platform as ANSI standard

E2BIG     Argument list too long 7 
EACCES    Permission denied 13 
EAGAIN    No more processes or not enough memory or maximum nesting level reached 11 
EBADF     Bad file number 9 
ECHILD    No spawned processes 10 
EDEADLOCK Resource deadlock would occur 36 
EDOM      Math argument 33 
EEXIST    File exists 17 
EINVAL    Invalid argument 22 
EMFILE    Too many open files 24 
ENOENT    No such file or directory 2 
ENOEXEC   Exec format error 8 
ENOMEM    Not enough memory 12 
ENOSPC    No space left on device 28 
ERANGE    Result too large 34 
EXDEV     Cross-device link 18 

EWOULDBLOCK = EAGAIN
*/
#define T120_SOCKET_TCP		0
#define T120_SOCKET_HTTP	1

#define T120_SOCKET_OPTION_RESET	1


#define T120_SOCKET_IO_FLAG_RECV 0x1
#define T120_SOCKET_IO_FLAG_SEND 0x2

/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class T120_Socket_Event_Handler;
class T120_Socket;

/////////////////////////////////////////////////////////////////////////////
// T120_Socket_Event_Handler
//
class T120_Socket_Event_Handler
{
public :
	virtual void on_evt_accept_ready(T120_Socket* sock, int err_code) {}
	virtual void on_evt_connect_ready(T120_Socket* sock, int err_code)  {}
	virtual void on_evt_connection_broken(T120_Socket* sock, int err_code) {}
	virtual void on_evt_io_ready(T120_Socket* sock, int flag)  {}
    virtual char *on_evt_get_id() { return NULL; };

};

struct T120_Socket_Info
{
	T120_SOCKET fd;
	char		remote_address[64];
	char		remote_port;
	int			proto_type;
};

class T120_Socket_On_Event_Handler : public T120_Socket_Event_Handler
{
public :
	virtual void on_evt_accept_new(T120_Socket_Info *sock) {}
	
};


/////////////////////////////////////////////////////////////////////////////
// T120_Socket
//
class T120_Socket
{
public :
	T120_Socket(T120_Socket_Event_Handler* handler);
	T120_Socket(T120_SOCKET sock_fd, T120_Socket_Event_Handler* handler);
	virtual ~T120_Socket();

public :
	// On success, return socket fd. On error, return T120_INVALID_SOCKET
	virtual T120_SOCKET init();

	
	// None return
	virtual void shutdown();

	// On success, return 0. On error, return -1
	virtual int bind(char* addr, int port);

	// On success, return 0. On error, return -1
	virtual int listen(int backlog);

	// On success, return socket fd, remote addr, max_addr_len and port number. 
	// On error, return T120_INVALID_SOCKET
	virtual T120_SOCKET accept(char* addr, int max_addr_len, int& port);

	// On success, return 0. On error, return -1
	virtual int connect(char* addr, int port);

	// On success, return num of bytes sent. On error, return -1
	virtual int send(uint8* buffer, uint32 buffer_len);

	// On success, return num of bytes sent. On error, return -1
	virtual int writev(struct iovec* v, uint16 num_of_v);

	// On success, return num of bytes received. On error, return -1
	virtual int readv(struct iovec* v, uint16 num_of_v);

	// On success, return num of bytes sent. On error, return -1
	virtual int receive(uint8* buffer, uint32 buffer_len);

	// On success, return 0. On error, return -1
	virtual int set_none_blocking(boolean none_block);

	// On success, return 0. On error, return -1
	virtual int set_option(int opt_name, void *optval, int optlen, int level=SOL_SOCKET);//weixin, support nodelay option, 01102006
	
public :
	uint16 magic; 

	virtual void handle_event(short revents);
	virtual int attach_poller(T120_Poller* poller, uint32 id = 0);
	virtual int detach_poller(T120_Poller* poller);

	virtual T120_SOCKET get_sock_fd();

	virtual void set_sock_fd(T120_SOCKET fd);
	
	virtual void set_handler(T120_Socket_Event_Handler* handler);
	
	virtual void set_suspend_mode( boolean cur_mode);
	virtual void set_open_state(boolean cur_open_state);

	virtual int get_error_code();

	virtual int   available();	virtual bool is_valid(){return (magic == 18207);}

	T120_Socket_Event_Handler *get_handler() { return handler; }

protected :
	typedef enum {
		T120_SOCKET_STATE_NULL = 0,
		T120_SOCKET_STATE_LISTEN,
		T120_SOCKET_STATE_CONNECT,
		T120_SOCKET_STATE_OPEN,
		T120_SOCKET_STATE_CLOSED,
	} T120_SOCKET_STATE;

	T120_SOCKET_STATE          state;
	T120_SOCKET                sock_fd;
	T120_Socket_Event_Handler* handler;
	boolean					   suspend_mode;

	 char                     *p_ref_object_id;
};

/////////////////////////////////////////////////////////////////////////////
// T120_Socket
//
#define SOCKET_IP_ADDRESS_LEN 15

class T120_Socket_Ex : public  T120_Socket
{
public:
	T120_Socket_Ex(T120_Socket_Event_Handler* handler);
	T120_Socket_Ex(T120_SOCKET sock_fd, T120_Socket_Event_Handler* handler);
	virtual ~T120_Socket_Ex();

	virtual int   connect(char* addr, int port);

	virtual char *get_local_ip() { return local_ip; }
	virtual void  set_local_ip(const char *cur_ip) 
                     {  
                        memset_s(local_ip, SOCKET_IP_ADDRESS_LEN + 1, 0);
                        strncpy_s(local_ip, SOCKET_IP_ADDRESS_LEN+1,cur_ip, SOCKET_IP_ADDRESS_LEN); 
                     } 
	virtual int   get_local_port() { return local_port; }
	virtual void  set_local_port(int cur_port) { local_port = cur_port;  } 

	virtual char *get_remote_ip() { return remote_ip; }
	virtual void  set_remote_ip(const char *cur_ip) 
                { 
                   memset_s(remote_ip, SOCKET_IP_ADDRESS_LEN + 1, 0);
                   strncpy_s(remote_ip,SOCKET_IP_ADDRESS_LEN+1, cur_ip, SOCKET_IP_ADDRESS_LEN); 
                } 
	virtual int   get_remote_port() { return remote_port; }
	virtual void  set_remote_port(int cur_port) { remote_port = cur_port;  } 

	virtual int   get_type() { return type; }
	virtual void  set_type ( int cur_type ) { this->type = cur_type; }

	virtual bool  get_remote_address( char *p_address, int p_address_len );
	virtual bool  get_local_address( char *p_address, int p_address_len);
	
protected:

	char local_ip[SOCKET_IP_ADDRESS_LEN + 1];
	int  local_port;

	char remote_ip[SOCKET_IP_ADDRESS_LEN + 1];
	int  remote_port;

	int  type;
};

/////////////////////////////////////////////////////////////////////
// T120_Socket_SSL
//
#ifdef USE_OPENSSL_LIB

#include "openssl/ssl.h"

#define SSL_VERSION_TLSv1     "TLSv1"
#define SSL_VERSION_SSLv2     "SSLv2"
#define SSL_VERSION_SSLv3     "SSLv3"

#define SSL_DEFAULT_METHOD      SSLv23_client_method()

class T120_Socket_SSL : public T120_Socket
{
public:
    T120_Socket_SSL(T120_Socket_Event_Handler* handler);
    virtual ~T120_Socket_SSL();
	virtual T120_SOCKET init();
    virtual T120_SOCKET init(int is_verify, char *cipher_list, char *ssl_version, char *ca_location);
    virtual int connect(char* addr, int port);
    virtual void handle_event(short revents);
    virtual int receive(uint8* buffer, uint32 buffer_len);
    virtual int writev(struct iovec* v, uint16 num_of_v);
    virtual int readv(struct iovec* v, uint16 num_of_v);
    virtual void shutdown();


    T120_SOCKET init(SSL_CTX* ssl_ctx);
    int init_ssl(int is_verify, char *cipher_list, char *ssl_version, char *ca_location);
    int send(uint8* buffer, uint32 buffer_len);
    int ssl_connect(void);
	

private:
    SSL *m_ssl;
    SSL_CTX *m_ssl_ctx;

	int premature_closed;
};

#endif	//USE_OPENSSL_LIB

#endif
