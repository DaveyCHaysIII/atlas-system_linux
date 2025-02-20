#include <sys/sockets.h> /* for base socket api & syscalls */
#include <arpa/inet.h> /* for htonl() and ntohl() */
#include <netinet/in.h> /* for sockaddr_in data struct */

socket example

sock_fd = socket(AF_INET, SOCK_STREAM, 0);

sockaddr_in serv_addr;

/*The <netinet/in.h> header shall define the sockaddr_in structure, which shall include at least the following members:

sa_family_t     sin_family   AF_INET.
in_port_t       sin_port     Port number.
struct in_addr  sin_addr     IP address.

The sin_port and sin_addr members shall be in network byte order. If the sin_port value passed to bind() is zero, the port number bound to the socket shall be one chosen by the implementation from an implementation-defined port range to produce an unused local address.

The sockaddr_in structure is used to store addresses for the Internet address family. Pointers to this type shall be cast by applications to struct sockaddr * for use with socket functions.

*/

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htonl(whatever the port is);
serv_addr.sin_addr = htonl(whatever the addy is);

bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr);

listen(sock_fd, 10) /* 10 is max length */




///////////////////////////////////////////////////////////
int socket(int domain, int type, int protocol);


socket() creates an endpoint for communication and returns a file
       descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file
       descriptor not currently open for the process.

       The domain argument specifies a communication domain; this selects
       the protocol family which will be used for communication.  These
       families are defined in <sys/socket.h>.


///////////////////////////////////////
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);

When a socket is created with socket(2), it exists in a name space
       (address family) but has no address assigned to it.  bind()
       assigns the address specified by addr to the socket referred to by
       the file descriptor sockfd.  addrlen specifies the size, in bytes,
       of the address structure pointed to by addr.  Traditionally, this
       operation is called “assigning a name to a socket”.

       It is normally necessary to assign a local address using bind()
       before a SOCK_STREAM socket may receive connections (see
       accept(2)).


The actual structure passed for the addr argument will depend on
       the address family.  The sockaddr structure is defined as
       something like:

           struct sockaddr {
               sa_family_t sa_family;
               char        sa_data[14];
           }

       The only purpose of this structure is to cast the structure
       pointer passed in addr in order to avoid compiler warnings.  See
       EXAMPLES below.

///////////////////////////////////////////////
int listen(int sockfd, int backlog);

listen() marks the socket referred to by sockfd as a passive
       socket, that is, as a socket that will be used to accept incoming
       connection requests using accept(2).

/////////////////////////////////////////////////
int accept(int sockfd, struct sockaddr *_Nullable restrict addr,
                  socklen_t *_Nullable restrict addrlen);

The accept() system call is used with connection-based socket
       types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first
       connection request on the queue of pending connections for the
       listening socket, sockfd, creates a new connected socket, and
       returns a new file descriptor referring to that socket.  The newly
       created socket is not in the listening state.  The original socket
       sockfd is unaffected by this call.

       The argument sockfd is a socket that has been created with
       socket(2), bound to a local address with bind(2), and is listening
       for connections after a listen(2).

       The argument addr is a pointer to a sockaddr structure.  This
       structure is filled in with the address of the peer socket, as
       known to the communications layer.  The exact format of the
       address returned addr is determined by the socket's address family
       (see socket(2) and the respective protocol man pages).  When addr
       is NULL, nothing is filled in; in this case, addrlen is not used,
       and should also be NULL.

       The addrlen argument is a value-result argument: the caller must
       initialize it to contain the size (in bytes) of the structure
       pointed to by addr; on return it will contain the actual size of
       the peer address.

       The returned address is truncated if the buffer provided is too
       small; in this case, addrlen will return a value greater than was
       supplied to the call.

       If no pending connections are present on the queue, and the socket
       is not marked as nonblocking, accept() blocks the caller until a
       connection is present.  If the socket is marked nonblocking and no
       pending connections are present on the queue, accept() fails with
       the error EAGAIN or EWOULDBLOCK.

/////////////////////////////////////////////

