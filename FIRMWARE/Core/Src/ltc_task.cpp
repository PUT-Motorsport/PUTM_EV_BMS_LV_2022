#include "main.h"
#include "cmsis_os.h"

extern "C" void start_ltc_function(void *argument){
  for(;;)
  {
	osDelay(100);
  }
}