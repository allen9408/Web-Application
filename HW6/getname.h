// #include 		/* standard I/O, NULL, etc.	   */
// #include 		/* string manipulation functions   */

#include <stdio.h>/* perror(), fprintf(), sprintf() */
#include <stdlib.h>/* for atoi() */
#include <string.h>/* for memset() */
#include <sys/socket.h> /* socket(), bind(), listen(), accept(),
                           recv(), send(), htonl(), htons() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <unistd.h>     /* for close() */
#include <netdb.h>      /* for hostent, gethostbyname() */

#if !defined(WIN16) && !defined(WIN32)
#  define	FAR
   typedef struct in_addr IN_ADDR;
   typedef struct in_addr FAR* LPIN_ADDR;
   typedef struct hostent FAR* LPHOSTENT;
#endif
#ifndef MAXHOSTNAMELEN
#  define MAXHOSTNAMELEN	256
#endif

/* ------------------------------------------------------------------------- *
 *	Function name:  parse_IPaddr
 *	Description: Checks whether given address string is proper
 *		     (in dotted-decimal notation) and if so,
 *		     returns the address in network byte order.
 *	Arguments: str	- (INPUT) Internet address string
 *		   addr	- (OUTPUT) pointer to the network byte order address
 *	Returns:   0, if the input address is in dotted-decimal notation
 *		  -1, if not
 *	Functions called: gethostbyname(), inet_ntoa(), htonl(), inet_addr()
 * _________________________________________________________________________ */

#if defined(__STDC__) || defined(__cplusplus) || defined(WIN16)||defined(WIN32)
int parse_IPaddr( char FAR* str, unsigned long FAR* addr )
#else
int parse_IPaddr( str, addr )
     char*		str;
     unsigned long*	addr;
#endif
{
	int	b1, b2, b3, b4;

	/*
	**  First try to convert the host name as a dotted-decimal number.
	**  Only if that fails do we call gethostbyname().
	*/
	if ( sscanf( str, "%d.%d.%d.%d", &b1, &b2, &b3, &b4 ) != 4 )
	  {			/* 4 is the length of an INET address */
	    LPHOSTENT		hp;
	    LPIN_ADDR		ptr;

	    if ( (hp = gethostbyname( str )) == NULL )
	      {
		return -1;	/* Bad address error: Not an INET host! */
	      }

	    /* Check the address type for an Internet host. */
	    if (hp->h_addrtype != AF_INET)
	      {
		return -1;	/* Bad address error: Not an INET host! */
	      }

	    /* extract dotted-decimal address as the 1st from the list */
	    ptr = (LPIN_ADDR) hp->h_addr;
	    str = inet_ntoa( *ptr );
	    if ( sscanf( str, "%d.%d.%d.%d", &b1, &b2, &b3, &b4 ) != 4 )
	      {
		return -1;	/* Bad address error. */
	      }
	  }
	*addr = inet_addr( str );
	return 0;
}

/* ------------------------------------------------------------------------- *
 *	Function Name:  get_hostIPaddr
 *	Description:  Finds and returns the IP address of the machine
 *			we are running on.
 *	Arguments:  ipaddrstr - (INPUT) pointer to the host address in
 *				dotted-decimal notation
 *	Returns:  On success,	host IP address in network byte order
 *		  On error,	0
 *	Functions called:  gethostname(), gethostbyname(), inet_ntoa(),
 *			   inet_addr()
 *
 *	Notes:  Error is returned as 0, since an Internet address of 0
 *		is not possible for any host ( 0 refers to `this' host
 *		in the INET context ).
 * _________________________________________________________________________ */

#if defined(__STDC__) || defined(__cplusplus) || defined(WIN16)||defined(WIN32)
unsigned long get_hostIPaddr( char FAR* ipaddrstr )
#else
unsigned long get_hostIPaddr( ipaddrstr )
     char*	ipaddrstr;
#endif
{
	char		hostname[MAXHOSTNAMELEN];
	LPHOSTENT	host_ptr;

	/* get host name */

	if ( gethostname( hostname, sizeof hostname ) < 0 )
	  {
	    return 0;	/* Error: That hostname is not found/bad */
	  }

	/* lookup host's address by name */

	if ( ( host_ptr = gethostbyname( hostname ) ) == NULL )
	  {
	    return 0;	/* Error: Cannot get the host! */
	  }

	/* Check the address type for an Internet host. */
	if ( host_ptr->h_addrtype != AF_INET )
	  {
	    return 0;	/* Error: Not an INET host! */
	  }

	/* extract dotted-decimal address as the 1st from the list */
	{
	  IN_ADDR	inaddr;

	  inaddr = *( (LPIN_ADDR)( host_ptr->h_addr_list[ 0 ]) );
	  strcpy( ipaddrstr, inet_ntoa( inaddr ));
	}

	return  inet_addr( ipaddrstr  );  
}

// int main(int argc, char const *argv[])
// {
// 	unsigned long h,*ip;
// 	char hostname[1024];
// 	char IPADD[1024];
// 	int isIP;
// 	char buffer [50];
// 	hostname[1023] = '\0';
// 	gethostname(hostname, 1023);
// 	printf("Hostname: %s\n", hostname);
// 	h = get_hostIPaddr(hostname);
// 	printf("%lu\n", h);

//     sprintf (buffer, "%lu" , h);
// 	isIP = parse_IPaddr(buffer, ip);
// 	printf("%lu\n", *ip);
// 	return 0;
// }
