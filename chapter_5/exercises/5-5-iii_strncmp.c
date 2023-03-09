/* Implement strncmp(cs, ct, n): compare at most n characters of string cs to string ct; return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct */ 

#include <stdio.h>
#include <stdlib.h>

/* str_cmp_n: Compares n characters of cs to ct. Assumes n <= one of cs or ct. 
 * Returns 0 if all n chars match, else the number of matched chars; positive if cs>ct, negative if cs<ct */
int str_cmp_n(char * cs, char * ct, unsigned int n) {
    for(int i = 0; i < n; ++i) {
        if (*cs == *ct) {
           ++cs;
           ++ct;
        } else if (*cs == '\0') {
            return 0 - i;
        } else {
            return 0 + i;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char s[] = "Hello";
    char t[] = "Helios";
    printf("%d\n", str_cmp_n(s, t, 6));
    return EXIT_SUCCESS;
}
