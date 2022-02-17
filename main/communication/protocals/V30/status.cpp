#include "../protocal_v30.h"
// #include "Arduino.h"

/** @brief  StartPrint
  * @retval None
  */
void ProtocalV30::StatusHandle() {
  uint32_t u32_value;

  cur_machine_status.printer_status = parsed_buffer[3];
  cur_machine_status.hotend_temp[0] = (int16_t)((parsed_buffer[5] << 8) | parsed_buffer[4]);
  cur_machine_status.hotend_tar_temp[0] = (int16_t)((parsed_buffer[7] << 8) | parsed_buffer[6]);

  cur_machine_status.bed_temp = (int16_t)((parsed_buffer[9] << 8) | parsed_buffer[8]);
  cur_machine_status.bed_tar_temp = (int16_t)((parsed_buffer[11] << 8) | parsed_buffer[10]);

  u32_value = (parsed_buffer[15] << 24) | (parsed_buffer[14] << 16) | (parsed_buffer[13] << 8) | parsed_buffer[12];
  cur_machine_status.current_pos[0] = u32_value / 1000.0f;

  u32_value = (parsed_buffer[19] << 24) | (parsed_buffer[18] << 16) | (parsed_buffer[17] << 8) | parsed_buffer[16];
  cur_machine_status.current_pos[1] = u32_value / 1000.0f;

  u32_value = (parsed_buffer[23] << 24) | (parsed_buffer[22] << 16) | (parsed_buffer[21] << 8) | parsed_buffer[20];
  cur_machine_status.current_pos[2] = u32_value / 1000.0f;

  u32_value = (parsed_buffer[27] << 24) | (parsed_buffer[26] << 16) | (parsed_buffer[25] << 8) | parsed_buffer[24];
  cur_machine_status.current_pos[3] = u32_value / 1000.0f;
  
  cur_machine_status.percent = (parsed_buffer[29] << 8) | parsed_buffer[28];

  cur_machine_status.fan_speed_percent = parsed_buffer[30];
}

void ProtocalV30::GetFeedrateHandle() {
  cur_machine_status.feedrate_percent = (parsed_buffer[5] << 8) | parsed_buffer[4];
}

void ProtocalV30::GetPrintFeedrate(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_STATUS, SCMD_STAT_FEEDRATE, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetPowerLostFlag(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_STATUS, SCMD_STAT_POWERLOST_FLAG, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::RequestStatus(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_STATUS, SCMD_STAT_MACHINE, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::FetchStatus(strMachineStatus *NewStatus) {
  *NewStatus = cur_machine_status;
}