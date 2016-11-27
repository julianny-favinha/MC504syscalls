/* 
 * SYSTEM CALLS
 * 
 * Igor Gustavo Hitzschky Lema - 155758
 * João Vítor Buscatto Silva - 155951
 * Julianny Favinha Donda - 156059
 * Ronaldo Prata Amorim - 157228
 * 
 * 2º SEMESTRE DE 2016 - MC504 - Profa. Islene Calciolari Garcia
 * 
 * Teste das chamadas de sistema que armazenam e recuperam pares de 
 * chave/valor com tempo de vida determinado no momento da criação.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 380 = sys_settmpkey(int key, char* value, unsigned int lifespan) */
/* 381 = sys_gettmpkey(int key, int n, char* value) */

int main() {
   int sc;
   char *value = "teste";

   sc = syscall(380, 1, value, 10); 
   printf("Retorno da chamada sys_settmpkey: %d.\n", sc);

   sc = syscall(381, 1, 6, value);
   printf("Retorno da chamada sys_gettmpkey: %d.\n", sc);
   printf("%s\n", value);

   return sc;
}
