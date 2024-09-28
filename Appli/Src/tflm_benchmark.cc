#include "tflm_benchmark.h"

#include <stdio.h>

extern int keyword_benchmark_main(int argc, char** argv);
extern int person_detection_benchmark_main(int argc, char** argv);

void tflm_benchmark()
{
    puts("======================================================================");
    puts("             TensorFlow Lite for Microcontrollers");
    puts("                   library and benchmarks porting");
    puts("                                for STM32H7S78-DK");
    puts("                                   by xusiwei1236");
    puts("---------------------------------------------------------------------");
    
#ifdef KEYWORD_BENCHMARK
    printf(" keyword benchmark ...\n");
    puts("---------------------------------------------------------------------");
    keyword_benchmark_main(0, nullptr);
#endif

#ifdef PERSON_DETECTION_BENCHMARK
    puts(" person detection benchmark ...");
    puts("---------------------------------------------------------------------");
    person_detection_benchmark_main(0, nullptr);
#endif
    puts("======================================================================");
}
