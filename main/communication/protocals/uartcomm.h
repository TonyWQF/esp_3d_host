#include "protocal_v30.h"

class UartCom {
public:

  void Init();
  void Loop();

  // Screen down stream APIs
  void FetchMachineStatus(strMachineStatus *Status) { protocal->FetchStatus(Status); }
  void FetchMachineSettings(strMachineSettings *Settings) { protocal->FetchSettings(Settings); }
  void RequestMachineStatus() { protocal->RequestStatus(send_package); SendPackage(); }
  void GetPrintFeedrate() { protocal->GetPrintFeedrate(send_package); SendPackage(); }
  void GetPowerLostFlag() { protocal->GetPowerLostFlag(send_package); SendPackage(); }
  // Controls
  void SetFan(uint8_t Index, uint8_t Percent) { protocal->SetFan(send_package, Index, Percent); ; SendPackage(); }
  void SetHeater(uint8_t Index, uint16_t Temperature) { protocal->SetHeater(send_package, Index, Temperature); ; SendPackage(); }
  void HomeAll() { protocal->HomeAll(send_package); SendPackage(); };
  void HomeAxis(uint8_t Axis) { protocal->HomeAxis(send_package, Axis); SendPackage(); };
  void MoveAxis(uint8_t Axis, float Distance) { protocal->MoveAxis(send_package, 1, Axis, Distance); SendPackage(); }
  void FilamentExtrude(uint8_t Extruder, float Distance) { protocal->FilamentExtrude(send_package, Extruder, Distance); SendPackage(); }
  void FilamentRetract(uint8_t Extruder, float Distance) { protocal->FilamentRetract(send_package, Extruder, Distance); SendPackage(); }
  void QuickStopStepper() { protocal->QuickStopStepper(send_package); SendPackage(); }
  void MotorOff(){protocal->MotorOff(send_package); SendPackage();}
  void SetFeedRatePercent(uint16_t Percent) { protocal->SetFeedratePercent(send_package, Percent); SendPackage(); }
  // Print
  void PrintStart(char *FileName, uint8_t FileIndex) { protocal->PrintStart(send_package, FileName, FileIndex); SendPackage(); };
  void PrintPause() { protocal->PrintPause(send_package); SendPackage(); };
  void PrintResume() { protocal->PrintResume(send_package); SendPackage(); };
  void PrintStop() { protocal->PrintStop(send_package); SendPackage(); };
  void RecoveryPrint(bool recovery) { protocal->RecoveryPrint(send_package, recovery); SendPackage(); }

  // Maintenance
  void RestoreSetting() { protocal->RestoreSetting(send_package); SendPackage(); } 
  void DefaultSetting() { protocal->DefaultSetting(send_package); SendPackage(); } 
  void GetMachineInfo() { protocal->GetMachineInfo(send_package); SendPackage(); };
  void GetMachineDefination() { protocal->GetMachineDefination(send_package); SendPackage(); };
  void SetFilamentSensorDetection(bool NewState) { protocal->SetFilamentSensorDetection(send_package, NewState); SendPackage(); };
  void SetPwrLossSensorDetection(bool NewState) {protocal->SetPwrLossSensorDetection(send_package, NewState); SendPackage();};
  void SetSensorDetection(bool PowerLossNewState, bool FilamentNewState) { SetPwrLossSensorDetection(PowerLossNewState); SetFilamentSensorDetection(FilamentNewState);};
  void GetSensorConfigDetection() { protocal->GetSensorConfigDetection(send_package); SendPackage(); };
  
  // Adjust
  void ManualLeveling() { protocal->ManualLeveling(send_package); SendPackage(); }
  void ManualLevelingMove(uint8_t PointIndex) { protocal->ManualLevelingMove(send_package, PointIndex); SendPackage(); }
  void ManualLevelingLeave(bool Save) { protocal->ManualLevelingLeave(send_package, Save); SendPackage(); }
  void AutoLeveling() { protocal->Autoleveling(send_package); SendPackage(); }
  void AutoLevelingLeave(bool Save) { protocal->AutoLevelingLeave(send_package, Save); SendPackage(); }

  // File list
  void GetFirstFileNames(uint8_t Volumn) { protocal->GetFirstFileNames(send_package, Volumn); SendPackage(); };
  void GetNextPageFileNames(uint8_t Volumn) { protocal->GetNextPageFileNames(send_package, Volumn); SendPackage(); };
  void GetPreviousPageFileNames(uint8_t Volumn) { protocal->GetPreviousPageFileNames(send_package, Volumn); SendPackage(); };

  void FillBuffer();
  void Parse();
  void SendPackage();
  void AutoRequestStatus();
  uint32_t auto_request_tick;
private:

  Protocal *protocal;
  uint8_t send_package[512];
  

  ProtocalV30 v30protocal;
 
};

extern UartCom SComm3;