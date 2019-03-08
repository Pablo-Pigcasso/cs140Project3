/* cidrtranslate: given a cidr notation input, output all network info
 *
 * Usage is ./<nameOfFile>.c ip/#
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Data structures
typedef struct network{
	char *dotquad; //xxx.xxx.xxx.xxx
	int	bits;
	uint32_t ip;
	uint32_t mask;
}

network_struct;

// Function prototypes
network_struct *parse(char *netstring);
uint32_t dotquad2int(char *dotq);
char *int2dotquad(uint32_t ip);
uint32_t cidr2mask(int bits);

// Main function
int main(int argc,char *argv[]){

	network_struct *net ;
	
	if (argc < 2) {
		fprintf(stderr, "usage: cidrtranslate xxx.xxx.xxx.xxx/x\n");
		return(1);
	}
	//parse the arguments
	net = parse( argv[1] );

	//set ip and mask
	net->ip = dotquad2int(net->dotquad);
	net->mask = cidr2mask(net->bits);

	//print out formatted results
	printf("\nFor network %s,\n \n",argv[1]);
	printf("Network       = \n");
	printf("Broadcast     = \n");
	printf("First Node    = \n");
	printf("Last Node     = \n");
	printf("Number of IPs = \n");
	printf("net->dotquad  = %s\n", net->dotquad);
	printf("net->bits     = %d\n", net->bits);
	printf("net->ip       = %d\n", net->ip);
	printf("net->mask     = %d\n \n", net->mask);
}

// network_struct is populating the values called in main
network_struct *parse(char *netstring){
	network_struct *mynet=malloc(sizeof(network_struct));
	mynet->dotquad = strtok(netstring,"/");
    mynet->bits = atoi(strtok(NULL,"/"));
	mynet->ip = 0;
	mynet->mask = 0;
	return mynet;
}

// dotquad2int change the dotquad info into int
uint32_t dotquad2int(char *dotq){
	char * pch;
	int i;
	int digits[4]; // store tokens
	uint32_t sum = 0 ; // for checking invalid input

	// split string to tokens
	pch = strtok (dotq, ".");
	for(i=3; (pch != NULL) && (i >= 0) ; i--){
		digits[i] = atoi(pch);
		pch = strtok (NULL, " ,.-");
	}
	if (i > 0){
		return 0;
	} else {
		for (i=0; i < 4; i++)
			sum += digits[i]*pow(2, 8*i);
		return (sum);
	}
}

// change int into dotquad format
char *int2dotquad(uint32_t ip){
	return "0.0.0.0";
}

// change cidr into mask
uint32_t cidr2mask(int bits){
    uint32_t result;
    result = pow(2,31);
    result = result >> (bits-1);
	return result;
}
