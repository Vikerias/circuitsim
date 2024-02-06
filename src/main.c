/*

	Braden Kay - 28/1/24 - Basic logic sim, eventually I plan to increase it to operate as a circuit simulator
	
	basically the point of this is to get my head around using nodes and linking these to binary logic before we make it analogue
	
	end goal is to have these all as C functions, but call from a python front end, makes it easier for people to play with but keeps the fun stuff in c
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// debug mode
#define DEBUG 1

//max gates for early testing
#define MAX_GATES 64

// Defines for different gate/symbols
#define NOT  	0
#define OR		1
#define NOR  	2
#define AND  	3
#define NAND 	4
#define XOR  	5

// constants for comparisons and conversions when reading files
#define N_KWD	"NODE"
#define G_KWD	"GATE"
#define A_0_OFF	'0'
#define A_9_OFF '9'

typedef struct {
	int nodeId;
	int value;
	int nodeOrder;
} node_t;


typedef struct {
	//just assume a two input, one output structure
	int gateId;
	int gateType;
	node_t *inputA;
	node_t *inputB;
	node_t *outputA;
	int gateOrder;
}gate_t;


int updateGate(gate_t *currentGate) {
	
	if (DEBUG) {
		printf("gateoutput of %d - %d was %d with inputs %d and %d\n", currentGate->gateType, currentGate->gateId, currentGate->outputA->value, currentGate->inputA->value, currentGate->inputB->value);
	}
	
	switch (currentGate->gateType) {
		
		case NOT:
			currentGate->outputA->value = (!(currentGate->inputA->value));
			break;
		case OR:
			currentGate->outputA->value = (currentGate->inputA->value | currentGate->inputB->value);
			break;
		case NOR:
			currentGate->outputA->value = (!(currentGate->inputA->value | currentGate->inputB->value));
			break;
		case AND:
			currentGate->outputA->value = (currentGate->inputA->value & currentGate->inputB->value);
			break;
		case NAND:
			currentGate->outputA->value = (!(currentGate->inputA->value & currentGate->inputB->value));
			break;
		case XOR:
			currentGate->outputA->value = (currentGate->inputA->value ^ currentGate->inputB->value);
			break;
		default:
				printf("Roses are red, violets are blue, thats not a gate, now go home my bru\n");
			break;
	}
	
	if (DEBUG) {
		printf("gateoutput of %d - %d is now %d with inputs %d and %d\n\n", currentGate->gateType, currentGate->gateId, currentGate->outputA->value, currentGate->inputA->value, currentGate->inputB->value);
	}
}

int stoi(const char *str) {
	//converts a string of number characters to a single integer
	//requires some preprocessing (one integer at a time)
	
	int i=0;
	int stoiInt = 0;
	
	char currChar = str[i];
	
	while (currChar != '\0') {
		if ((currChar >= A_0_OFF) && (currChar <= A_9_OFF)) {
			stoiInt = stoiInt * 10 + (currChar - A_0_OFF);
			i++;
			currChar = str[i];
		} else {
			//some kind of issue, wrong character detected, abort	
			stoiInt = 0;
			currChar = '\0';
		}
	}
	
	return stoiInt;
}


int readNetworkfile() {
	//reads from a text network file, and creates nodes and gates from it
	//currently hardcoded to open "netfile.txt" from current directory
	
	int success = 0;
	
	ssize_t read;
	size_t len = 0;
	char *line = NULL;
	
	FILE *ptr;
	ptr = fopen("netfile.txt", "r");
	
	if (ptr == NULL) {
		printf("Failed to open netfile, aborting\n");
		success = 1;
	} else {
		int i = 0;
		while((read = getline(&line, &len, ptr)) != -1) {
			printf("Raw dump line %d: %s : length %d\n", i, line, read);
			i++;
		}
	}
	
	if (ptr) {
		fclose(ptr);
	}
	
	
	return success;
}

int setup(gate_t **activeGates, node_t **activeNodes) {
	
	// holding function to keep environment setups separate
	
	*activeGates = (gate_t *) malloc(MAX_GATES * sizeof(gate_t));
	*activeNodes = (node_t *) malloc(MAX_GATES * sizeof(node_t));
	
	if (DEBUG) {
		printf("Setup Completed succesfully\n");
	}
	
	
	return 0;
}



int main(void) {
	// testscript
	
	int currentNodecount = 0;
	int currentGatecount = 0;
	
	int nodeOrderslist[] = {0, 0, 1, 2, 0, 0, 1, 2, 3};

	
	readNetworkfile();
	
	char testString[] = "1250\0";
	
	printf("Test with %s -> %d\n", testString, stoi(testString));
	
	gate_t *activeGates;
	node_t *activeNodes;
	
	setup(&activeGates, &activeNodes);
	
	for (int i=0; i<9; i++) {
		//create nodes for use later
		node_t tempNode = {i, 0, nodeOrderslist[i]};
		activeNodes[i] = tempNode;
		currentNodecount++;
	}
	
	
	if (DEBUG) {
		for (int j=0; j<currentNodecount; j++) {
			//check the nodes look right
			printf("node ID: %d, Value: %d of order: %d\n", activeNodes[j].nodeId, activeNodes[j].value, activeNodes[j].nodeOrder);
		}
	}
	
	
	
	gate_t myAndgate = {0, AND, &activeNodes[0], &activeNodes[1], &activeNodes[2], 0};
	activeGates[0] = myAndgate;
	currentGatecount++;
	
	gate_t myAndgate2 = {1, AND, &activeNodes[4], &activeNodes[5], &activeNodes[6], 0};
	activeGates[1] = myAndgate2;
	currentGatecount++;	
	
	gate_t myNotgate = {2, NOT, &activeNodes[2], &activeNodes[2], &activeNodes[3], 1};
	activeGates[2] = myNotgate;
	currentGatecount++;

	gate_t myNotgate2 = {3, NOT, &activeNodes[6], &activeNodes[6], &activeNodes[7], 1};
	activeGates[3] = myNotgate2;
	currentGatecount++;
	
	gate_t myAndgate3 = {4, AND, &activeNodes[7], &activeNodes[3], &activeNodes[8], 2};
	activeGates[4] = myAndgate3;
	currentGatecount++;
	
	for (int i=0; i<currentGatecount; i++) {
		updateGate(&activeGates[i]);
	}
	
	free(activeGates);
	free(activeNodes);
	
	return 0;
}