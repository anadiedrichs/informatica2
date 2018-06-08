#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{
  int pollingDelay = 10;
  //do stuff

  //sleep:
  #ifdef _WIN32
  Sleep(pollingDelay);
  #else
  usleep(pollingDelay*1000);  /* sleep  milliSeconds */
  sleep(pollingDelay); /*sleep in seconds*/
  #endif

  //do stuff again
  return 0;
}


