/* strcpy: copy t to s; array subscript version */
void strcpy_array(char * s, char * t)
{
    int i;
    i = 0;
    while((s[i] = t[i]) != '\0') {
        ++i;
    }
}
