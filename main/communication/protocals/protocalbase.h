#include "stdint.h"

typedef struct {
  float current_pos[4];
  int16_t hotend_temp[2];
  int16_t hotend_tar_temp[2];
  uint16_t bed_temp;
  uint16_t bed_tar_temp;
  uint16_t percent;
  uint16_t feedrate_percent;
  uint8_t fan_speed_percent;
  uint8_t printer_status;
}strMachineStatus;

typedef struct {
  bool FilamentEnable;
  bool PwrLossEnable;
}strMachineSettings;

class Protocal {
public:
  virtual int Parse();
  virtual int SetupPackage(uint8_t *pSource, uint8_t *pDestination, uint16_t Length);
  virtual void ProcessCommand();

  // Screen down stream APIs
  // Status
  virtual void RequestStatus(uint8_t *pPackBuffer);
  virtual void GetPrintFeedrate(uint8_t *pPackBuffer);
  virtual void GetPowerLostFlag(uint8_t *pPackBuffer);
  virtual void FetchStatus(strMachineStatus *NewStatus);
  virtual void FetchSettings(strMachineSettings *NewSetting);
  // Controls
  virtual void SetFan(uint8_t *pPackBuffer, uint8_t Index, uint8_t Percent);
  virtual void SetHeater(uint8_t *pPackBuffer, uint8_t Index, uint16_t Temperature);
  virtual void HomeAll(uint8_t *pPackBuffer);
  virtual void HomeAxis(uint8_t *pPackBuffer, uint8_t Axis);
  virtual void MoveAxis(uint8_t *pPackBuffer, uint8_t Mode, uint8_t Axis, float Distance);
  virtual void ManualLeveling(uint8_t *pPackBuffer);
  virtual void ManualLevelingMove(uint8_t *pPackBuffer, uint8_t PointIndex);
  virtual void ManualLevelingLeave(uint8_t *pPackBuffer, bool Save);
  virtual void Autoleveling(uint8_t *pPackBuffer);
  virtual void AutoLevelingLeave(uint8_t *pPackBuffer, bool Save);
  virtual void FilamentExtrude(uint8_t *pPackBuffer, uint8_t Extruder, float Distance);
  virtual void FilamentRetract(uint8_t *pPackBuffer, uint8_t Extruder, float Distance);
  virtual void QuickStopStepper(uint8_t *pPackBuffer);
  virtual void MotorOff(uint8_t *pPackBuffer);
  virtual void SetFeedratePercent(uint8_t *pPackBuffer, uint16_t Percent);
  // Print
  virtual void PrintStart(uint8_t *pPackBuffer, char *FileName, uint8_t FileIndex);
  virtual void PrintPause(uint8_t *pPackBuffer);
  virtual void PrintResume(uint8_t *pPackBuffer);
  virtual void PrintStop(uint8_t *pPackBuffer);
  virtual void RecoveryPrint(uint8_t *pPackBuffer, bool recovery);
  // Maintenance
  virtual void RestoreSetting(uint8_t *pPackBuffer);
  virtual void DefaultSetting(uint8_t *pPackBuffer);
  virtual void GetMachineInfo(uint8_t *pPackBuffer);
  virtual void GetMachineDefination(uint8_t *pPackBuffer);
  virtual void SetFilamentSensorDetection(uint8_t *pPackBuffer, bool NewState);
  virtual void SetPwrLossSensorDetection(uint8_t *pPackBuffer, bool NewState);
  virtual void GetSensorConfigDetection(uint8_t *pPackBuffer);

  // File list
  virtual void GetFirstFileNames(uint8_t *pPackBuffer, uint8_t Volumn);
  virtual void GetNextPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn);
  virtual void GetPreviousPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn);


  bool PushOneByte(uint8_t Data);
  uint16_t GetPackupSize() { return pack_up_size; }
protected:
  uint16_t tail;
  uint16_t head;
  uint8_t read_buffer[1024];
  uint8_t parsed_buffer[1024];
  uint16_t parsed_length;
  uint16_t pack_up_size;
};