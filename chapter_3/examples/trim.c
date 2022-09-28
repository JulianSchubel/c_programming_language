/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
        int n = strlen(s);
        for(int i = n-1; i >= 0; --n, --i)
        {
                if(s[i] != ' ' && s[i] !='\n' && s[i] != '\t')
                {
                        break;
                }
        }
        s[n] = '\0';
        return n;
}

