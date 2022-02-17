#include "../protocal_v30.h"
// #include "Arduino.h"

void ProtocalV30::RestoreSetting(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_LOAD_SETTING, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::DefaultSetting(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_DEFAULT_SETTING, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetMachineInfo(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_GET_MACHINE_INFO, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetMachineDefination(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_GET_MACHINE_DEF, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));  
}

void ProtocalV30::SetFilamentSensorDetection(uint8_t *pPackBuffer, bool NewState) {
  uint8_t true_false = 0;

  if(NewState!=0){
    true_false = 1;
  }else true_false = 0;

  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_SET_FIL_SENSOR, 0x00, true_false};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::SetPwrLossSensorDetection(uint8_t *pPackBuffer, bool NewState) {
  uint8_t true_false = 0;

  if(NewState!=0){
    true_false = 1;
  }else true_false = 0;

  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_SET_POWERLOST_SENSOR, 0x00, true_false};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetSensorConfigDetection(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_MAINTENANCE, SCMD_MTN_GET_CONFIGS, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::SensorEnableHandle() {
  cur_machine_settings.FilamentEnable = parsed_buffer[4];
  cur_machine_settings.PwrLossEnable = parsed_buffer[5];
}

void ProtocalV30::FetchSettings(strMachineSettings *Setting) {
  *Setting = cur_machine_settings;
}