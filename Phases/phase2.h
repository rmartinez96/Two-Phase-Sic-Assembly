// Phase 2

#ifndef phase2_h
#define phase2_h
#include <unistd.h>
#include <stdlib.h>

void read_line(void);
void assemble(char *inFile);

struct optab{
    char code[10],objcode[10];
}
myoptab[25] = {
    {"ADD", "18"},
    {"AND", "58"},
    {"COMP", "28"},
    {"DIV", "24"},
    {"J", "3C"},
    {"JEQ", "30"},
    {"JGT", "34"},
    {"JLT", "38"},
    {"JSUB", "48"},
    {"LDA", "00"},
    {"LDCH", "50"},
    {"LDL", "08"},
    {"LDX", "20"},
    {"MUL", "20"},
    {"OR", "44"},
    {"RD", "D8"},
    {"RSUB", "4C"},
    {"STA", "0C"},
    {"STCH", "54"},
    {"STL", "14"},
    {"STX", "10"},
    {"SUB", "1C"},
    {"TD","E0"},
    {"TIX", "2C"},
    {"WD", "DC"},
};

struct SYMTAB
{
    char symbol[15];
    int addr;
}

mysymtab[20];

int startaddr;
int locctr;
int symcount=0;
int length;
char line[20],label[8],opcode[8],operand[8],programname[10];

int dupsym=0;
int nostart=0;
int noend=0;
int manybyte=0;
int noop=0;
int validop=0;
int memover=0;


void pass_one(char *inFile)
{
    int sym_there = 0;
    int sym_tracker = 0;
    int op_there = 0;
    
    FILE *input,*inter;
    input=fopen(inFile,"r");
    inter=fopen("inter.txt","w");
    
    fgets(line,20,input);
    read_line();
    
    if (strcmp(opcode, "START") == 0)
    {
        startaddr=atoi(operand);
        locctr=startaddr;
        strcpy(programname,label);
        fprintf(inter,"%d   %s",locctr, line);
        fgets(line,20,input);
        read_line();
    }
    else
    {
        programname[0]='\0';
        startaddr=0;
        locctr=0;
        nostart = 1;
    }
    
    while (strcmp(opcode,"END") != 0 )
    {
        if (strcmp(&line[0],".") != 0)
        {
            if (strcmp(label,"/0") != 0)
            {
                if (strcmp(mysymtab[0].symbol, "\0") == 0)
                {
                    //DO NOTHING
                }
                if (strcmp(mysymtab[0].symbol, label) == 0)
                {
                    sym_there = 1;
                }
                else
                {
                    for (int i = 0; strcmp(mysymtab[i].symbol, "\0") != 0; i++)
                    {
                        if (strcmp(label,mysymtab[i+1].symbol) == 0)
                        {
                            sym_there = 1;
                            break;
                        }
                    }
                }
                if (sym_there == 1)
                {
                    dupsym = 1;
                    sym_there = 0;
                }
                else
                {
                    for (int i = 0; i < 20; i++)
                    {
                        if (strcmp(mysymtab[i].symbol, "\0") != 0)
                        {
                            sym_tracker++;
                        }
                    }
                    memcpy(mysymtab[sym_tracker].symbol, label, 10);
                    mysymtab[sym_tracker].addr = locctr;
                    sym_tracker = 0;
                }
                
                for (int i = 1; i < 25; i++)
                {
                    if (strcmp(myoptab[i].code, opcode) == 0)
                    {
                        op_there = 1;
                        break;
                    }
                }
                
                if(op_there == 1)
                {
                    locctr += 3;
                    op_there = 0;
                }
                else if (strcmp(opcode, "WORD") == 0)
                {
                    locctr += 3;
                }
                else if (strcmp(opcode, "RESW") == 0)
                {
                    locctr += atoi(operand)*3;
                }
                else if (strcmp(opcode, "RESB") == 0)
                {
                    locctr += atoi(operand);
                }
                else if (strcmp(opcode, "BYTE") == 0)
                {
                    int j = 0;
                    for (int i = 2; strcmp(&operand[i], "\0") != 0; i++)
                    {
                        if (strcmp(&operand[i], "\'") != 0)
                        {
                            j++;
                        }
                    }
                    locctr += j;
                }
                else
                {
                    noop = 1;
                }
            }
        }
        fprintf(inter, "%s %d  ", line, locctr);
        fgets(line,20,input);
        read_line();
    }
    fprintf(inter, "%s %d  ", line, locctr);
    length = locctr - startaddr;
    
    fprintf(inter,"\n\nSymbol Table\n");
    fprintf(inter,"_____________________________________\n");
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(mysymtab[i].symbol, "\0") != 0)
        fprintf(inter, "%s  %d", mysymtab[i].symbol, mysymtab[i].addr);
        fprintf(inter, "\n");
    }
    /*
    fprintf(inter, "\n Op Table\n");
    fprintf(inter, "_____________________________________\n");
    for (int i = 0; strcmp(myoptab[i].code,"\0") != 0; i++)
    {
        fprintf(inter, "%s", myoptab[i].code);
        fprintf(inter, "\n");
    }
     */
    
    fclose(inter);
    fclose(input);
}

void read_line()
{
    char buff[8],word1[8],word2[8],word3[8];
    int i,j=0,count=0;
    label[0]=opcode[0]=operand[0]=word1[0]=word2[0]=word3[0]='\0';
    
    for(i=0;line[i]!='\0';i++)
    {
        if(line[i]!=' ')
            buff[j++]=line[i];
        else
        {
            buff[j]='\0';
            strcpy(word3,word2);
            strcpy(word2,word1);
            strcpy(word1,buff);
            j=0;
            count++;
        }
    }
    
    buff[j-1]='\0';
    
    strcpy(word3,word2);
    strcpy(word2,word1);
    strcpy(word1,buff);
    
    switch(count)
    {
        case 0:
            strcpy(opcode,word1);
            break;
        case 1:
        {
            strcpy(opcode,word2);
            strcpy(operand,word1);
            
        }
            break;
        case 2:{
            strcpy(label,word3);
            strcpy(opcode,word2);
            strcpy(operand,word1);
            
        }
            break;
    }
}

void assemble(char *inFile)
{
    pass_one(inFile);
}


#endif /* phase2_h */
