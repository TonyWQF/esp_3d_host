#include "../protocal_v30.h"
// #include "Arduino.h"
// #include "User/pages/pages.h"

void ProtocalV30::FileListHandle() {
  uint8_t count = parsed_buffer[4];
  char *p = (char*)&parsed_buffer[5];
  uint8_t i, j;
  for(int k=0;k<5;k++) {
    file_names[k][0] = 0;
    // dis_files(file_names[k], k);
  }
  for(i=0;i<count;i++) {
    j = 0;
    file_names[i][0] = 0;
    while(j<FILE_NAME_LEN_MAX) {
      file_names[i][j++] = *p;
      if(*p++ == 0)
        break; 
    }
    // dis_files(file_names[i], i);
  }
}

void ProtocalV30::GetFirstFileNames(uint8_t *pPackBuffer, uint8_t Volumn) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_LIST_START, 0x00, Volumn, 5};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetNextPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_LIST_NEXT, 0x00, Volumn, 5};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::GetPreviousPageFileNames(uint8_t *pPackBuffer, uint8_t Volumn) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_LIST_PREVIOUS, 0x00, Volumn, 5};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::PrintStart(uint8_t *pPackBuffer, char *FileName, uint8_t FileIndex) {
  int i = 0;
  uint8_t send_buffer[FILE_NAME_LEN_MAX + 8];
  send_buffer[i++] = CMD_FILES;
  send_buffer[i++] = SCMD_FIL_START;
  send_buffer[i++] = 0;
  send_buffer[i++] = FileIndex;
  while(*FileName)
    send_buffer[i++] = *FileName++;
  send_buffer[i++] = 0;
  SetupPackage(send_buffer, pPackBuffer, i);
}

void ProtocalV30::PrintPause(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_PAUSE, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::PrintResume(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_RESUME, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::PrintStop(uint8_t *pPackBuffer) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_STOP, 0x00};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}

void ProtocalV30::RecoveryPrint(uint8_t *pPackBuffer, bool recovery) {
  uint8_t send_buffer[] = {CMD_FILES, SCMD_FIL_RECOVERY_PRINT, 0x00, !!recovery};
  SetupPackage(send_buffer, pPackBuffer, sizeof(send_buffer));
}
