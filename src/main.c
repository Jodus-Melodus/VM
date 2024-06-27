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
	PSR,
	PTR,
	JNS,
	JSF,
	HLT
} InstructionSet;

typedef enum
{
	A, B, C, D, E, F, IP, SP, ZF, SF,
	NUM_OF_REGISTERS
} Registers;

const int program[] = {
	SET, C, 0,
	SET, A, 1,
	SET, B, 1,
	PSR, A,
	PSR, B,
	ADD,
	JSF, 38,
	PSR, C,	
	JZ, 20,
	JNZ, 28,
	POP,
	SET, C, 1,
	PTR, B,
	JMP, 9,
	POP,
	SET, C, 0,
	PTR, A,
	JMP, 9,
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
	case PTR:
		value1 = pop();
		value2 = fetch();
		registers[value2] = value1;
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
	case PSR:
		push(registers[fetch()]);
		break;
	case SET:
		value1 = fetch();
		value2 = fetch();
		registers[value1] = value2;
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
	case JSF:
		if (registers[SF] == 1)
		{
			registers[IP] = fetch();
		}
		break;
	case JNS:
		if (registers[SF] == 0)
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

	return 0;
}
