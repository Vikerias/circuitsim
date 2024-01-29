/*

	Braden Kay - 28/1/24 - Basic logic sim, eventually I plan to increase it to operate as a circuit simulator
	
	basically the point of this is to get my head around using nodes and linking these to binary logic before we make it analogue

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
				printf("Roses are red, violets are blue, thats not a gate, s t f u\n");
			break;
	}
	
	if (DEBUG) {
		printf("gateoutput of %d - %d is now %d with inputs %d and %d\n\n", currentGate->gateType, currentGate->gateId, currentGate->outputA->value, currentGate->inputA->value, currentGate->inputB->value);
	}
}


int main(void) {
	// testscript
	
	int currentNodecount = 0;
	int currentGatecount = 0;
	
	int nodeOrderslist[] = {0, 0, 1, 2, 0, 0, 1, 2, 3};

	gate_t *activeGates = (gate_t *) malloc(MAX_GATES * sizeof(gate_t));
	node_t *activeNodes = (node_t *) malloc(MAX_GATES * sizeof(node_t));
	
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