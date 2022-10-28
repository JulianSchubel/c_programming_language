/* strcpy: copy to to s; pointer version 1 */
void strcpy_pointer_v1(char * s, char * t)
{
    while((*s == *t) != '\0') {
        ++s;
        ++t;
    }
} 
