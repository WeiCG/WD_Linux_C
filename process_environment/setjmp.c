#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TOK_ADD 5
#define MAXLINE 4096

static void do_line(char *);
static void cmd_add(void);
static int get_token(void);

static jmp_buf jmpbuffer;

int main(int argc, char const *argv[])
{
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0) {  // 注册一个跳转的地方
        puts("error");
    } else {
        puts("已注册\n");
    }

    while (fgets(line, MAXLINE, stdin) != NULL)
        do_line(line);

    return 0;
}

static char *tok_ptr = NULL;

static void do_line(char *ptr)
{
    int cmd;
    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch (cmd) {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }
}

static void cmd_add(void)
{
    int token = get_token();
    if (token < 0)
        longjmp(jmpbuffer, 1);
}

static int get_token(void)
{
    static size_t i = 0;
    i++;
    return i == 1 ? 5 : -1;
}