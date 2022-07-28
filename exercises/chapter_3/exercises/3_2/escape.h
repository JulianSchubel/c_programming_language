#if !defined(ESCAPE_H)
#define ESCAPE_H
/*Converts escape characters to visible escape sequences. Copies t to s. Assumes s is large enough to hold t.*/
void escape(char * s, char * t);
#endif
