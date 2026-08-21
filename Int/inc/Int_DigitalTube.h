#ifndef __INT_DIGITALTUBE_H__
#define __INT_DIGITALTUBE_H__

#include "STC89C5xRC.H"
#include "Com_Util.h"

void Int_DigitalTube_DisplaySingle(uint8_t position, uint8_t seg_code);
void Int_DigitalTube_DisplayNumber(uint32_t number);

#endif /* __INT_DIGITALTUBE_H__ */