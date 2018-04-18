
#ifndef __QKC_INNER_FSOCKET_H
#define __QKC_INNER_FSOCKET_H 1

#include <quark_compile.h>
#include <stdint.h>
#include <windows.h>
#include <winsock2.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
    Ϊ��ʵ��epoll���ԣ���Ҫ��ԭ����socket��Щ���죬���Ӹ�����Ϣ������ֱ��ʹ�á�
*/
#define SOCKET_STAGE_VOID       0 
#define SOCKET_STAGE_BIND       1
#define SOCKET_STAGE_LISTEN     2
#define SOCKET_STAGE_CONNECT    3
#define SOCKET_STAGE_DESROTY    -1

typedef struct __st_socket_ovlp     socket_ovlp_t ;
typedef struct __st_send_result     send_result_t ;
typedef struct __st_recv_result     recv_result_t ;
typedef struct __st_accept_result   accept_result_t;

typedef struct __st_socket{
    SOCKET socket ;
    int8_t type ;                  //SOCK_STREAM��SOCK_DGRAM
    int8_t stage ;  
    int8_t noblock :1;            //Ĭ����������һ������Ҫ�ı�ʶ!!!������ò��û�б�Ҫ��

    accept_result_t * acceptor ;
    send_result_t   * sender ;
    recv_result_t   * receiver ;
} socket_t;

typedef enum{
    OVLP_VOID   =   0 ,
    OVLP_ACCEPT =   1 ,
    OVLP_INPUT  =   2 ,
    OVLP_OUTPUT =   3 
} ovlp_type_t ;

struct __st_socket_ovlp
{
    OVERLAPPED          ovlp ;
    int                 status ;
    ovlp_type_t         type ;
    socket_t    *       owner ;
} ;

struct __st_send_result{
    socket_ovlp_t   link ;

    WSABUF data ;
    int bufsize ;               //�׽��ֱ����������Ĵ�С
    int sending_bytes ;         //�������ڷ����е��ֽ���
    size_t to_bytes ;           //�����͵����ֽ���
    size_t completed_bytes ;    //��ɷ��͵����ֽ���
};

struct __st_recv_result{
    socket_ovlp_t   link ;

    WSABUF data ;
    size_t from_bytes ;
    size_t complete_bytes ;
};

#define ACCEPT_ADDRESS_SIZE 256
struct __st_accept_result{
    socket_ovlp_t   link ;

    SOCKET insocket ;           //���յ��ͻ�������������׽���   
    char address[ACCEPT_ADDRESS_SIZE] ;
};

void update_contex_acceptex(SOCKET& new_socket , SOCKET& listen_socket) ;

bool sockopt_get_keepalive(SOCKET& s , bool &optval) ;
bool sockopt_set_keepalive(SOCKET& s , bool optval) ;

bool sockopt_get_recv_buffer_size(SOCKET& s , int& optval) ;
bool sockopt_set_recv_buffer_size(SOCKET& s , int optval) ;

bool sockopt_get_send_buffer_size(SOCKET& s , int& optval) ;
bool sockopt_set_send_buffer_size(SOCKET& s , int optval) ;

bool sockopt_get_recv_timeout(SOCKET& s , DWORD& optval) ;
bool sockopt_set_recv_timeout(SOCKET& s , DWORD optval) ;

bool sockopt_get_send_timeout(SOCKET& s , DWORD& optval) ;
bool sockopt_set_send_timeout(SOCKET& s , DWORD optval) ;

#ifdef	__cplusplus
}
#endif

#endif /** __QKC_INNER_FSOCKET_H */