/* Write  the function strrindex(s,t), which returns the position of the rightmost occurrence of t in s, or -1 if there is none. */

#include <stdio.h>

/* s_len_inclusive: counts the length of a string including the null terminator '\0' */
int s_len_inclusive(char s[])
{
    int s_len = 0;
    /* Count length of s including all escape characters*/
    while(s[s_len++] != '\0') {
        ;
    }
    return s_len;
}

/*str_rindex: returns the index of the first character of the rightmost occurence of t in s, -1 if none*/
int str_rindex(char s[], char t[])
{
    signed int i;
    unsigned int j, k;
    int s_len =  s_len_inclusive(s);
    int t_len = s_len_inclusive(t);

    /* if the source string is too short to contain the pattern, return -1 */
    if(s_len < t_len)
    {
        return -1;
    }

    /* i must be of type signed integer, else potential infinite loop via underflow */
    for(i = s_len - t_len; i >= 0; --i)
    {
        for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
            ;
        }
        if( k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

int main(int argc, char * * argv)
{
    printf("%d\n", (argc > 2) ? str_rindex(argv[1],argv[2]) : -1);
    return 0;
}
