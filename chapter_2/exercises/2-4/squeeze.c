/* Write an alternate version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2 */

#include <stdio.h>

void squeeze(char * s1, char * s2) 
{
    int i, j;
    int found;
    for(i = j = 0; s1[i]; ++i) {
        for(int k = 0; s2[k]; ++k) {
            found = 0;
            if(s1[i] == s2[k]) {
                found = 1;
                break;
            }
        }
        if(!found)
        {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}
