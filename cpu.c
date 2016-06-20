#include <stdint.h>
#include "cpu.h"

#define OPCODE_MASK 0xf000
#define ENDERECO_MASK 0x0fff

int16_t ac = 0;
uint16_t pc = 0;
uint16_t memoria[MEM_SIZE] = {0};

void ula ( uint8_t opcode, uint16_t valor)
{
    switch (opcode)
    {
        case 3: //add
            ac += valor;
            break;
        case 4: //sub
            ac -= valor;
            break;
        case 5: //mul
            ac *= valor;
            break;
        case 6: //div
            ac /= valor;
            break;
        case 7: //mod
            ac %= valor;
            break;
        case 8: //or
            ac |= valor;
            break;
        case 9: //and
            ac &= valor;
            break;
        case 14: //inc
            ac++;
            break;
    }
}

int cpu ( uint16_t instrucao )
{
    //colocar os 4 bits na porção menos significativa
    uint16_t opcode = (instrucao & OPCODE_MASK) >> 12;
    //zeros na esquerda nao importam
    uint16_t endereco = instrucao & ENDERECO_MASK;
    switch (opcode)
    {
        case 1: //load
            ac = memoria[endereco];
            break;
        case 2: //stor
            memoria[endereco] = ac;
            break;
        case 10://jump
            pc = endereco;
            break;
        case 11://jumpz
            pc = (ac == 0) ? endereco-2 : pc;
            break;
        case 12://jumpn
            pc = (ac <  0) ? endereco-2 : pc;
            break;
        case 13://jumpp
            pc = (ac >  0) ? endereco-2 : pc;
            break;
        case 15: //end
            return 0;
            break;
        default:
            ula( opcode, memoria[endereco] );
    }
    return 1;
}

