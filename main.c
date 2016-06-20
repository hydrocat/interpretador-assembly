#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "cpu.h"

#define QTD_INSTRUCAO 16

enum instrucao {
    NOP  , LOAD , STOR, ADD, 
    SUB  , MUL  , DIV , MOD,
    OR   , AND  , JUMP, JUMPZ,
    JUMPN, JUMPP, INC , END
};

const char* instrucao_string[] = {
    "NOP"  , "LOAD" , "STOR", "ADD", 
    "SUB"  , "MUL"  , "DIV" , "MOD",
    "OR"   , "AND"  , "JUMP", "JUMPZ",
    "JUMPN", "JUMPP", "INC" , "END"
};

const uint16_t instrucao_hex[] ={
    0x0000, 0x1000,0x2000,0x3000,
    0x4000, 0x5000,0x6000,0x7000,
    0x8000, 0x9000,0xa000,0xb000,
    0xc000, 0xd000,0xe000,0xf000
};

//Definicao de funcoes
void setmem( uint16_t *memoria, char* instrucao, uint16_t endereco);
void writeProg( FILE *f , uint16_t* memoria);
void printmem( uint16_t *memoria );
void writeMem( FILE *f, uint16_t* memoria );


int main(int argc, char* argv[])
{
    //checa por parametros errados
    if ( argc != 2 ){
        printf("Uso: .\\%s Arquivo_de_entrada\n", argv[0]);
        exit(1);
    }

    /*
        Agora comeca o processo de ler o programa na memoria 
        principal do simulador
    */
    FILE *f = fopen( argv[1] , "r");

    //escreve o programa na memoria
    writeProg( f, memoria );

    //escreve a memoria do programa na memoria
    //( aquela parde deopis da instrucao "end" )
    writeMem( f, memoria );

    printf("Estado Inicial\n");
    printmem( memoria );
    /* 
        Roda a simulação
    */
    pc = 0;
    while ( cpu( memoria[pc] ) )
    {
        //printf("ac[%hd]\tpc[%hu]\n",ac,pc);
        pc++;
    }

    printf("Pós simulação\n");
    printmem( memoria );
    
}

void writeProg( FILE *f , uint16_t* memoria)
{
    //as instrucoes do simulador sao formatadas em duas partes:
    uint16_t ir = 0;
    char instrucao[5] = "ASDFG";
    uint16_t endereco;
    while( fscanf(f,"%s", instrucao) )
    {
        if ( strcmp( instrucao, "INC") == 0 )
        {
            setmem( &memoria[ir++], instrucao, 0 );
        }
        else 
        if ( strcmp( instrucao, "END") == 0 )
        {
            setmem( &memoria[ir++], instrucao, 0 );
            break;
        }
        else
        {
            fscanf(f, "%hd\n",&endereco );
            setmem( &memoria[ir++], instrucao, endereco );
        }
    }

}

void writeMem( FILE *f, uint16_t* memoria )
{
    uint16_t posicao = 0;
    int16_t  valor = 0;
    while ( fscanf(f, "%hu %hd\n", &posicao, &valor) != EOF )
    {
        memoria[posicao] = valor;
    }
}

void printmem( uint16_t *memoria )
{
    int i = 0;
    for (; i < MEM_SIZE; i+=2) 
    {
        printf("%d:%hx\t%d:%hx\n",i,memoria[i], i+1, memoria[i+1] );
    }

}

void setmem( uint16_t *memoria, char* instrucao, uint16_t endereco)
{
    //decobre qual é a instrucao 
    uint16_t i = 0;
    for(; i < QTD_INSTRUCAO; i++)
    {
        if( strcmp( instrucao,instrucao_string[i] ) == 0 )
        {
            *memoria = instrucao_hex[i] | endereco;
            break;
        }
   }
}
