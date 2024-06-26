#include <stdio.h>

typedef enum
{
	PSH,
	ADD,
	DIV,
	MUL,
	MIN,
	MOD,
	POP,
	SET,
	JMP,
	JZ,
	JNZ,
	INC,
	DEC,
	HLT
} InstructionSet;

typedef enum
{
	A, B, C, D, E, F, IP, SP, ZF, SF,
	NUM_OF_REGISTERS
} Registers;

const int program[] = {
	PSH, 2,
	PSH, 3,
	SET, A, 5,
	INC, A,
	POP,
	HLT
};

int running = 1;
int stack[256];				// stack
int registers[NUM_OF_REGISTERS];	// Registers

void push(int value)
{
	stack[registers[SP]++] = value;
}

int pop()
{
	return stack[--registers[SP]];
}

int fetch()
{
	return program[registers[IP]++];
}

void evaluate(int instruction)
{
	int value1, value2;

	switch (instruction)
	{
	case HLT:
		running = 0;
		break;
	case PSH:
		push(fetch());
		break;
	case POP:
		printf("Popped %d\n", pop());
		break;
	case ADD:
		value1 = pop();
		value2 = pop();
		push(value1 + value2);
		break;
	case MIN:
		value1 = pop();
		value2 = pop();
		push(value2 - value1);
		break;
	case DIV:
		value1 = pop();
		value2 = pop();
		push(value2 / value1);
		break;
	case MUL:
		value1 = pop();
		value2 = pop();
		push(value1 * value2);
		break;
	case MOD:
		value1 = pop();
		value2 = pop();
		push(value2 % value1);
		break;
	case SET:
		registers[fetch()] = fetch();
		break;
	case INC:
		registers[fetch()]++;
		break;
	case DEC:
		registers[fetch()]--;
		break;
	case JMP:
		registers[IP] = fetch();
		break;
	case JZ:
		if (registers[ZF] == 1)
		{
			registers[IP] = fetch();
		}
		break;
	case JNZ:
		if (registers[ZF] == 0)
		{
			registers[IP] = fetch();
		}
		break;
	}

	registers[ZF] = (stack[registers[SP] - 1] == 0) ? 1 : 0;
	registers[SF] = (stack[registers[SP] - 1] < 0) ? 1 : 0;
}

int main()
{
	registers[IP] = 0;
	registers[SP] = 0;
	registers[ZF] = 0;
	registers[SF] = 0;

	while (running)
	{
		evaluate(fetch());
	}

	printf("%d\n", registers[A]);

	return 0;
}
