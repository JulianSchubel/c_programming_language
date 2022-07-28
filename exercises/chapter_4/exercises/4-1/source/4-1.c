#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int _getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int str_rindex(char source[], char pattern[]);
int s_len_inclusive(char source[]);
char pattern[] = "ould"; /* pattern to search for */


/* find all lines matching pattern */
int main(int argc, char * argv[])
{
    char line[MAXLINE];
    int found = 0;

    while( _getline(line, MAXLINE) > 0 ) {
        if( strindex(line, pattern) >= 0 ) {
            printf("%s", line);
            found++;
        }
		printf("%d", str_rindex(line, pattern));
    }
    return found;
}

/* getline: get line into s, return length */
int _getline(char s[], int limit)
{
    int c, i;
    i = 0;

    while(--limit > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if( c == '\n' ) {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/* strindex: return index of start of pattern (t) in string (s), -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;
    for( i = 0; s[i] != '\0'; i++) {
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
            ;
        }
        if( k > 0 && t[k] == '\0') {
            return i+k;
        }
    }
    return -1;
}

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

/* pattern_end: return index of end of pattern (t) in string (s), -1 if none */
int pattern_end(char s[], char t[])
{
	int i, j, k;
	for(i = 0; s[i] != '\0'; ++i) {
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
			;
		}
		if(k > 0 && t[k] == '\0') {
			//count of k started at 0 therefore no duplicate between i and k
			//k set to index that terminated "for" loop, therefore k-1
			return (i + (k-1));
		}
	}
	return -1;
}

