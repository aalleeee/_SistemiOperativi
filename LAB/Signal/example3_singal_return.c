// Basic example of singal() return value

#include <signal.h>
#include <stdio.h>

void myHandler(int sigNum) {}

int main()
{
  printf("DFL: %p\n", signal(SIGINT, SIG_IGN));
  printf("IGN: %p\n", signal(SIGINT, myHandler));
  printf("Custom: %p == %p\n", signal(SIGINT, SIG_DFL), myHandler);
}

// first singal return NULL : previous handler was a default one
// second signal return 1 : previous handler was SIG_IGN : signal(SIGINT, -> SIG_IGN)
// third signal return 0x55850ef45169 : previous handler was myHandler : printf("IGN: %p\n", signal(SIGINT, -> myHandler));
//    0x55850ef45169 == 0x55850ef45169