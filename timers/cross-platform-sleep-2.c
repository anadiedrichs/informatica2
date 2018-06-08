#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void inactive(int secs)
{
  #ifdef _WIN32
  Sleep(secs);
  #else
  sleep(secs); /*sleep in seconds*/
  #endif
}


int main()
{
  int pollingDelay = 5;
  //do stuff

  //sleep:
  inactive(pollingDelay);

  //do stuff again
  return 0;
}


