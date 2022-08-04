#include <readline/readline.h>
#include <stdlib.h>

int main(void)
{
    char *str;
    
    int i=0;
    while (i < 1)
    {
        str = readline("hello_world");
        printf("%s\n", str);
        free(str);
        i++;
    }
    system("leaks $PPID");
    return (0);
}

// readline 한번 보고오기 , 이해해보기 >_< 다들 너무고생많아따리~