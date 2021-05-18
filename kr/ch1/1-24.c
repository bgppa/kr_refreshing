/* Exercise 1.24 from the KR:
 * Write a program to check a C program for rudimentary syntax errors like
 * unbalanced parenthesis, brackets and braces. Don't forget about quotes,
 * both single and double, escape sequences and comments */

/* REMARK: the programs displays in output the characters that are
 * not processed during the check. In particular, since comments are processed,
 * they are removed. It solved the issue that I forgot in ex. 1.23 */
#include <stdio.h>

/* Global flag to keep track if the previous char was a slash / */
int prev_slsh = 0;

/* frequent action: print a slash if one pending. Reset the flag */
void slsh_buffer (void) {
    if (prev_slsh == 1) {
        putchar('/');
    }
    prev_slsh = 0;
}


int check_escape_sequence (char q)
{
    if (q != 't' && q != '\\' && q != 'a' && q != 'n') {
       /* list here all the possible C escape sequences...(skipped for brevity)
        */
    return 0;
    }
    return 1;    
}

int main (void) {
    int into_string = 0;    /* flag to monitor if into a string " " */
    int c = 0;              /* character in input */
    int graffe = 0;         /* counter for { */
    int quadre = 0;         /* counter for [ */
    int tonde = 0;          /* counter for ( */
    int nlines = 1;         /* number of lines */
    int no_error = 1;       /* flag to monitor if worth to continue */
    int into_comment = 0;   /* flag to monitor if into a comment */

    while (no_error && (c = getchar()) != EOF) {
        if (!into_comment) {
            if (!into_string) {
                switch (c) {
                    /* Check if a comment is going to start !*/
                    case ('/') :
                        /* If the first slash, set the flag */
                        if (prev_slsh == 0) {
                            prev_slsh = 1;
                        } else {
                            /* If slashes before, print */
                            putchar(c);
                        }
                    break;
                        
                    case ('*') :
                        /* in case of a previous slash, go into comment mode */
                        if (prev_slsh) {
                            into_comment = 1;
                            } else {
                            putchar(c);
                        }
                        /* in any case, reset the slash counter */
                        prev_slsh = 0;
                    break;

                    /* in ALL the following cases, i.e. not / or *, 
                     * the inserted char does not relate to comments.
                     * If exists pending /, print it via slsh_buffer().
                     * (e.g. in the case of int a = 4 // 2; */ 
                    case ('\n'):
                        slsh_buffer();
                        ++nlines;
                        putchar(c);
                    break;
                    /* This is for the case of single apex ', ascii is 39 */
                    case (39):
                        slsh_buffer();
                        /* ...then read another character:
                         * manage the escape sequence case as well as the
                         * closing apex */
                        c = getchar();
                        if (c == '\\') { 
                            if(!check_escape_sequence(c = getchar())) {
                            printf("\nERR: Invalid esc_seq, ln %d\n", nlines); 
                                no_error = 0;
                            }
                        }
                        if ((c = getchar()) != 39) {
                            printf("\n\nERR: unbalanced apex, ln %d\n", nlines);
                            no_error = 0;
                        }
                    break;
                    case ('{'):
                        slsh_buffer();
                        ++graffe;
                    break;
                    case ('}'):
                        slsh_buffer();
                        --graffe;
                    break;
                    case ('"'):
                        slsh_buffer();
                        into_string = 1;
                    break;
                    case ('['):
                        slsh_buffer();
                        ++quadre;
                    break;
                    case (']'):
                        slsh_buffer();
                        --quadre;
                    break;
                    case ('('):
                        slsh_buffer();
                        ++tonde;
                    break;
                    case (')'):
                        slsh_buffer();
                        --tonde;
                    break;
                    default:
                        slsh_buffer();
                        putchar(c);
                    break;
                }
            } else { /* If I am into a string */
                if (c == '"') {
                    into_string = 0;
                }
            }
        } else { /* In this case, I am into a comment */
            if (c == '*' && (c = getchar() == '/')) {
                into_comment = 0;
            }
        }
    }

    printf("Read %d lines (comments are ignored)\n", nlines);
    if (graffe != 0) {
        printf("ERR: { unbalanced\n");
    }
    if (quadre != 0) {
        printf("ERR: [ unbalanced\n");
    }
    if (tonde != 0) {
        printf("ERR: ( unbalanced\n");
    }
    
    if (no_error) {
        printf(" - no errors! :-)\n");
    }
    return 0;
}
