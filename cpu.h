#ifndef CPU_HEADER
#define CPU_HEADER

#include <stdint.h>
#define MEM_SIZE 50

extern int16_t ac; //Acumulador
extern uint16_t pc; //Program Counter
extern uint16_t memoria[];

void ula ( uint8_t opcode, uint16_t valor);
int  cpu ( uint16_t instrucao );

#endif
