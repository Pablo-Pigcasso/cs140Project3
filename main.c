/* cidrtranslate: given a cidr notation input, output all network info
 *
 * Usage is ./<nameOfFile>.c ip/#
 *
 * Authors: Matthew Miller, Matthew Beall, Drew Austin, Sam Amundson
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Data structures
typedef struct network {
	char *dotquad; //xxx.xxx.xxx.xxx
	int	bits;
	uint32_t ip;
	uint32_t mask;
}		network_struct;

// Function prototypes
network_struct *parse(char *netstring );
uint32_t dotquad2int(char *dotq );
char *int2dotquad(uint32_t ip );
uint32_t cidr2mask(int bits );

int main(int argc,char *argv[]) {

	network_struct *net ;
	
	if ( argc < 2 ) {
		fprintf(stderr, "usage: cidrtranslate xxx.xxx.xxx.xxx/x\n");
		return(1);
	}
	//parse the arguments
	net = parse( argv[1] );

	//set ip and mask
	net->ip = dotquad2int( net->dotquad );
	net->mask = cidr2mask( net->bits );

	//print out formatted results
	printf("For network %s,\n",argv[1]);
	printf("Network       =\n");
	printf("Broadcast     =\n");
	printf("First Node    =\n");
	printf("Last Node     =\n");
	printf("Number of IPs =\n");
	printf("net->dotquad  =%s\n",net->dotquad);
	printf("net->bits     =%d\n",net->bits);
	printf("net->ip       =%d\n",net->ip);
	printf("net->mask     =%d\n",net->mask);
}

network_struct *parse( char *netstring ){
	network_struct *mynet=malloc(sizeof(network_struct));
	mynet->dotquad="unset";
	mynet->ip=0;
	mynet->bits=0;
	mynet->mask=0;
	return mynet;
}
uint32_t dotquad2int( char *dotq ){

	char * pch;
	int i;
	int digits[4]; // store tokens
	uint32_t sum = 0 ; // for checking invalid input

	// split string to tokens
	pch = strtok (dotq,".");
	for(i=3; (pch != NULL) && (i >= 0) ; i--) {
		digits[i] = atoi(pch); 
		pch = strtok (NULL, " ,.-");
	}
	if ( i > 0 ) {
		return 0;
	} else {
		for ( i=0 ; i < 4 ; i++ ) 
			sum += digits[i]*pow(16,i);
		return (sum);
	}
}
char *int2dotquad( uint32_t ip ){
	return "0.0.0.0";
}
uint32_t cidr2mask( int bits ){
	return 0;
}
