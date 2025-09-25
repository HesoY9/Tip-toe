#include <stdio.h>
#include <time.h>
#include "hdr.h"

char timestamp[32];
void getTime(){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
}// get time for logging



