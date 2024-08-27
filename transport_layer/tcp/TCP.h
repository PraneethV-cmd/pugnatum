#ifndef TCP_DEFS
#define TCP_DEFS

#include <stdint.h>
#include <netinet/in.h>

// definitions
#define TCP_HEADER_LENGTH 20
#define TCP_HEADER_WORDS 5

// custom TCP Header
#pragma pack(push, 1)
typedef struct TCP_Header
{
    uint16_t source_port;
    uint16_t destination_port;
    uint32_t seq_no;
    uint32_t ack_no;
    __u_char reserved : 4, data_offset : 4; // little endian. that's why all that trouble with the flags
    // flags
    // __u_char flags;
    __u_char fin : 1,
        syn : 1,
        rst : 1,
        psh : 1,
        ack : 1,
        urg : 1,
        ece : 1,
        cwr : 1;
    // __u_char cwr : 1,
    //     ece : 1,
    //     urg : 1,
    //     ack : 1,
    //     psh : 1,
    //     rst : 1,
    //     syn : 1,
    //     fin : 1;
    uint16_t recv_window;
    uint16_t internet_checksum;
    uint16_t urgent_data_ptr;
    // options field, variable length.
    // data, variable length.
} TCP_Header;
#pragma pack(pop)

// typedef for socket fd
typedef int socket_t;

// socket plus destination address struct
typedef struct boundSocket
{
    socket_t socket_fd;
    struct sockaddr_in destination; // add connection request queue
} boundSocket;

// function declarations

// client side

/// @brief Does a TCP 3 way handshake.
/// @param dest_ip_address
/// @param dest_port
/// @param src_port
/// @return boundSocket pointer with socket information. NULL on failure.
boundSocket *TCP_Connect(char *dest_ip_address, int dest_port, int src_port); // NULL on failure

// server side
boundSocket *TCP_ListenAndAccept(int port);

#endif