#include "skip_whitespace.h"

/* classification */
enum classification {
    CLS_WS=0,
    CLS_COMMENT_BEGIN,
    CLS_COMMENT_END,
    CLS_IN_COMMENT,
    CLS_OTHER
};

/* skip_whitespace: skips whitespacea and comments read from stdin */
int skip_whitespace(void) {
    int c; 
    enum classification cls;

}
