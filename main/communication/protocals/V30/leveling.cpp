#include "../protocal_v30.h"
// #include "Arduino.h"


void ProtocalV30::ManualLeveling(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_ADJUST, SCMD_ADJ_MANUAL_LEVELING, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::ManualLevelingMove(uint8_t *pPackBuffer, uint8_t PointIndex) {
  uint8_t send_buffer[] = {CMD_ADJUST, SCMD_ADJ_MANUAL_LEVELING_MOVE, 0x00, PointIndex};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::ManualLevelingLeave(uint8_t *pPackBuffer, bool Save) {
  uint8_t true_false = 0;

  if(Save!=0){
    true_false = 1;
  }else true_false = 0;

  uint8_t send_buffer[] = {CMD_ADJUST, SCMD_ADJ_MANUAL_LEVELING_SAVE, 0x00, true_false};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}


void ProtocalV30::Autoleveling(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_ADJUST, SCMD_ADJ_AUTO_LEVELING, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::AutoLevelingLeave(uint8_t *pPackBuffer, bool Save) {
  uint8_t true_false = 0;

  if(Save!=0){
    true_false = 1;
  }else true_false = 0;

  uint8_t send_buffer[] = {CMD_ADJUST, SCMD_ADJ_AUTO_LEVELING_SAVE, 0x00, true_false};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}