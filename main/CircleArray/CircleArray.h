#pragma once

#include <stdint.h>

#define MAX_ARR_LEN 64
class CircleArray{
  private :
    static uint8_t head; 
    static uint8_t tail;
    static uint8_t arrays[MAX_ARR_LEN];     
  public:

    bool CirCleArrayisfull();
    bool CirCleArrayisempty();
    void CirCleArrayInput(uint8_t c);
    uint8_t CirCleArrayOutput(void);
    uint8_t CirCleArrayNumLeft(void);
    uint8_t CirCleArrayNumUsed(void);

};

