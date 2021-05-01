#include "../lib/errorCheck.h"

void check_getLine(ssize_t nRead)
{
    if(nRead == -1)
    {
      perror("Problema na leitura do arquivo");
      exit(errno);
    }
}


void check_fscanf(int nItensRead)
{
    if(nItensRead == EOF)
    {
      perror("Erro na leitura do arquivo (função fscanf)");
      exit(errno);
    }
}