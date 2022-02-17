#include "protocalbase.h"
#include "CommandList.h"
// #include "User/ui_api/ui_api.h"

#define FILE_NAME_LEN_MAX 32

class ProtocalV30 : Protocal  {
public:
  int Parse() override;
  int SetupPackage(uint8_t *pSource, uint8_t *pDestination, uint16_t Length) override;
  void ProcessCommand() override;

  // Screen down stream APIs
  // Status
  void RequestStatus(uint8_t *pPackBuffer) override;
  void GetPrintFeedrate(uint8_t *pPackBuffer) override;
  void GetPowerLostFlag(uint8_t *pPackBuffer) override;
  void FetchStatus(strMachineStatus *NewStatus) override;
  void FetchSettings(strMachineSettings *NewSetting) override;
  // Controls
  void SetFan(uint8_t *pPackBuffer, uint8_t Index, uint8_t Percent) override;
  void SetHeater(uint8_t *pPackBuffer, uint8_t Index, uint16_t Temperature) override;
  void HomeAll(uint8_t *pPackBuffer) override;
  void HomeAxis(uint8_t *pPackBuffer, uint8_t Axis) override;
  void MoveAxis(uint8_t *pPackBuffer, uint8_t Mode, uint8_t Axis, float Distance) override;
  void ManualLeveling(uint8_t *pPackBuffer) override;
  void ManualLevelingMove(uint8_t *pPackBuffer, uint8_t PointIndex) override;
  void ManualLevelingLeave(uint8_t *pPackBuffer, bool Save) override;
  void Autoleveling(uint8_t *pPackBuffer) override;
  void AutoLevelingLeave(uint8_t *pPackBuffer, bool Save) override;
  void FilamentExtrude(uint8_t *pPackBuffer, uint8_t Extruder, float Distance) override;
  void FilamentRetract(uint8_t *pPackBuffer, uint8_t Extruder, float Distance) override;
  void QuickStopStepper(uint8_t *pPackBuffer) override;
  void MotorOff(uint8_t *pPackBuffer) override;
  void SetFeedratePercent(uint8_t *pPackBuffer, uint16_t Percent) override;
  // Print
  void PrintStart(uint8_t *pPackBuffer, char *FileName, uint8_t FileIndex) override;
  void PrintPause(uint8_t *pPackBuffer) override;
  void PrintResume(uint8_t *pPackBuffer) override;
  void PrintStop(uint8_t *pPackBuffer) override;
  void RecoveryPrint(uint8_t *pPackBuffer, bool recovery) override;
  // Maintenance
  void RestoreSetting(uint8_t *pPackBuffer) override;
  void DefaultSetting(uint8_t *pPackBuffer) override;
  void GetMachineInfo(uint8_t *pPackBuffer) override;
  void GetMachineDefination(uint8_t *pPackBuffer) override;
  void SetFilamentSensorDetection(uint8_t *pPackBuffer, bool NewState) override;
  void SetPwrLossSensorDetection(uint8_t *pPackBuffer, bool NewState) override;
  void GetSensorConfigDetection(uint8_t *pPackBuffer) override;

  // Files
  void GetFirstFileNames(uint8_t *pPackBuffer, uint8_t Volumn) override;
  void GetNextPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn) override;
  void GetPreviousPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn) override;

  // Reacks
  int GenerialReack();

private:
  void StatusHandle();
  void GetFeedrateHandle();
  void FileListHandle();
  void SensorEnableHandle();

private:
  uint8_t prefix_0 = 0xa5;
  uint8_t prefix_1 = 0x5a;
  uint8_t Command;
  uint8_t SubCommand;
  uint8_t state;
  char file_names[5][FILE_NAME_LEN_MAX];
  strMachineStatus cur_machine_status;
  strMachineSettings cur_machine_settings;
};
