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
	HLT
} InstructionSet;

typedef enum
{
	A, B, C, D, E, F, IP, SP, ZF, SF,
	NUM_OF_REGISTERS
} Registers;

const int program[] = {
	SET, C, 0,	// 0
	SET, A, 1,	// 1
	SET, B, 1,	// 2
			//
	PSR, A,		// 3
	PSR, B,		// 4
	ADD,		// 5
	PSR, C,		// 6
	JZ, 9,		// 7
	JNZ, 13,	// 8
			//
	POP,		// 9
	SET, C, 1,	// 10
	PTR, B,		// 11
	JMP, 3,		// 12
			//
	POP,		// 13
	SET, C, 0,	// 14
	PTR, A,		// 15
	JMP, 3,		// 16
			//
	HLT		// 17
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

	printf("A : %d\n", registers[A]);
	printf("B : %d\n", registers[B]);
	printf("C : %d\n", registers[C]);

	return 0;
}
