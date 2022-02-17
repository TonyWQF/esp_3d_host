
#include "CircleArray.h"


bool CircleArray::CirCleArrayisfull(){
  return head == (tail+1)%MAX_ARR_LEN;
}

bool CircleArray::CirCleArrayisempty(){
  return head == tail;
}

void CircleArray::CirCleArrayInput(uint8_t c){
  arrays[tail] = c;

  tail = (tail+1)%MAX_ARR_LEN;
}

uint8_t CircleArray::CirCleArrayOutput(void){
  uint8_t c = 0;
  c = arrays[head];

  head = (head+1)%MAX_ARR_LEN;
  return c;
}

uint8_t CircleArray::CirCleArrayNumLeft(void){
  if (head >= tail) {
    return MAX_ARR_LEN - 1 - head + tail;
  }
  return tail - head - 1;
}

uint8_t CircleArray::CirCleArrayNumUsed(void){
  return MAX_ARR_LEN - CirCleArrayNumLeft();
}


