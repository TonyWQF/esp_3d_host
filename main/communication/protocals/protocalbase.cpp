#include "protocalbase.h"

/** @brief  Setup a package
  * @param  Data: Data to be packed up
  * @retval True if push success
  */
bool Protocal::PushOneByte(uint8_t Data) {
  uint16_t next_head = (head + 1) % sizeof(read_buffer);
  if(next_head != tail) {
    read_buffer[head] = Data;
    head = next_head;
    return true;
  }
  else {
    return false;
  }
}

/** @brief  Setup a package
  * @param  Index: 0 for left extruder, 1 for right extruder
  * @param  Percent: Data to be packed up
  * @retval None
  */
void Protocal::SetFan(uint8_t *pPackBuffer, uint8_t Index, uint8_t Percent) {
  // Log out undefine
}

/** @brief  Setup a package
  * @param  Index: 0 for left extruder, 1 for right extruder, 2 for heated bed
  * @param  Temperature: 
  * @retval None
  */
void Protocal::SetHeater(uint8_t *pPackBuffer, uint8_t Index, uint16_t Temperature) {
  // Log out undefine
}