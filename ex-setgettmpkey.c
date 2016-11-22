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

int main() {
   int sc;
   
   sc = syscall(380); 
   printf("Retorno da chamada sys_settmpkey: %d.\n", sc);
   sc = syscall(381);
   printf("Retorno da chamada sys_gettmpkey: %d.\n", sc);
   return sc;
}
