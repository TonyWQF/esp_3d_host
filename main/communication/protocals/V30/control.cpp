#include "../protocal_v30.h"
// #include "Arduino.h"

void ProtocalV30::SetFan(uint8_t *pPackBuffer, uint8_t Index, uint8_t Percent) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_FAN, 0x00, Index, Percent};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::SetHeater(uint8_t *pPackBuffer, uint8_t Index, uint16_t Temperature) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_HEATER, 0x00, Index, (uint8_t)Temperature, (uint8_t)(Temperature >> 8)};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::HomeAll(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_HOME, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::HomeAxis(uint8_t *pPackBuffer, uint8_t Axis) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_HOME_AXIS, 0x00, Axis};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::MoveAxis(uint8_t *pPackBuffer, uint8_t Mode, uint8_t Axis, float Distance) {
  int32_t u32_distance_mul_1000 = Distance * 1000.0f;
  uint8_t distance_array[4];
  distance_array[0] = (uint8_t)(u32_distance_mul_1000);
  distance_array[1] = (uint8_t)(u32_distance_mul_1000 >> 8);
  distance_array[2] = (uint8_t)(u32_distance_mul_1000 >> 16);
  distance_array[3] = (uint8_t)(u32_distance_mul_1000 >> 24);
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_MOVE, 0x00, Axis, Mode, distance_array[0], distance_array[1], distance_array[2], distance_array[3] };
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::FilamentExtrude(uint8_t *pPackBuffer, uint8_t Extruder, float Distance) {
  int32_t u32_distance_mul_1000 = Distance * 1000.0f;
  uint8_t distance_array[4];

  if(Distance < 0)
    Distance = -Distance;
  distance_array[0] = (uint8_t)(u32_distance_mul_1000);
  distance_array[1] = (uint8_t)(u32_distance_mul_1000 >> 8);
  distance_array[2] = (uint8_t)(u32_distance_mul_1000 >> 16);
  distance_array[3] = (uint8_t)(u32_distance_mul_1000 >> 24);
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_EXTRUDE, 0x00, Extruder, distance_array[0], distance_array[1], distance_array[2], distance_array[3] };
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::FilamentRetract(uint8_t *pPackBuffer, uint8_t Extruder, float Distance) {
  int32_t u32_distance_mul_1000 = Distance * 1000.0f;
  uint8_t distance_array[4];

  if(Distance < 0)
    Distance = -Distance;
  distance_array[0] = (uint8_t)(u32_distance_mul_1000);
  distance_array[1] = (uint8_t)(u32_distance_mul_1000 >> 8);
  distance_array[2] = (uint8_t)(u32_distance_mul_1000 >> 16);
  distance_array[3] = (uint8_t)(u32_distance_mul_1000 >> 24);
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_RETRACT, 0x00, Extruder, distance_array[0], distance_array[1], distance_array[2], distance_array[3] };
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::QuickStopStepper(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_STOP_STEPPER, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::MotorOff(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_MOTOR_OFF, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::SetFeedratePercent(uint8_t *pPackBuffer, uint16_t Percent) {
  uint8_t send_buffer[] = {CMD_CONTROL, SCMD_CTRL_FEEDRATE,  0x00, (uint8_t)Percent, (uint8_t)(Percent >> 8)};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}