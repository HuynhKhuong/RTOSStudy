Initial commit

*Reference list*
[1]: https://www.freertos.org/Documentation 


sysmem.c which handles heap managemant will not be used within this project 
--> portable/MemMang will handle them instead 
--> as they are designed to allocate RTOS threads on heap

Check datatype defined by FreeRTOS Kernel, check size
  configSTACK_DEPTH_TYPE --> uint16_t

REMEMBER to config PRIORITIES: [0 -> (configMAX_PRIORITIES - 1)]
configMAX_PRIORITIES locates in FreeRTOSConfig.h

### EXERCISE 1
Creates 2 tasks: 
Task-1
Task-2
with equal priorities --> print msg "Hello world from task-x"
