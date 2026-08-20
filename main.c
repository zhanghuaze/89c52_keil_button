#include <STC89C5xRC.H>
#include "Com_Util.h"


void main(void)
{
    while (1)
    {
        P00 = 0;
        Com_Util_Delay(500);
        P00 = 1;
        Com_Util_Delay(500);
    }
}
