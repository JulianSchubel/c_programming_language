/* strlenp: return the length of string s */
int strlenp(char * s) 
{
    char * p = s;
    while(*p != '\0') {
        ++p;
    }
    return p - s;
}
