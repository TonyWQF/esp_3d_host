#pragma once

#define CMD_STATUS              0x00
#define SCMD_STAT_MACHINE       0x00
#define SCMD_STAT_FEEDRATE      0x01
#define SCMD_STAT_POWERLOST_FLAG    0x02

#define CMD_CONTROL             0x01
#define SCMD_CTRL_FAN           0x01
#define SCMD_CTRL_HEATER        0x02
#define SCMD_CTRL_HOME          0x03
#define SCMD_CTRL_HOME_AXIS     0x04
#define SCMD_CTRL_MOVE          0x05
#define SCMD_CTRL_MOTOR_OFF     0x06
#define SCMD_CTRL_EXTRUDE       0x07
#define SCMD_CTRL_RETRACT       0x08
#define SCMD_CTRL_STOP_STEPPER  0x09
#define SCMD_CTRL_FEEDRATE      0x0a

#define CMD_ADJUST                0x02
#define SCMD_ADJ_LEVELING         0x01
#define SCMD_ADJ_MANUAL_LEVELING  0x02
#define SCMD_ADJ_MANUAL_LEVELING_MOVE  0x03
#define SCMD_ADJ_MANUAL_LEVELING_SAVE  0x04
#define SCMD_ADJ_AUTO_LEVELING    0x05
#define SCMD_ADJ_AUTO_LEVELING_SAVE    0x06
#define SCMD_ADJ_AUTO_POINT       0x07

#define CMD_PRINT                 0x03
#define SCMD_PRT_START            0x01
#define SCMD_PRT_PAUSE            0x02
#define SCMD_PRT_RESUME           0x03
#define SCMD_PRT_STOP             0x04
#define SCMD_PRT_ENDING           0x05
#define SCMD_PRT_FINISH           0x06

#define CMD_FILES                 0x04
#define SCMD_FIL_VOLUMN           0x01
#define SCMD_FIL_LIST_START       0x02
#define SCMD_FIL_LIST_NEXT        0x03
#define SCMD_FIL_LIST_PREVIOUS    0x04
#define SCMD_FIL_DEL              0x05
#define SCMD_FIL_START            0x06
#define SCMD_FIL_PAUSE            0x07
#define SCMD_FIL_RESUME           0x08
#define SCMD_FIL_STOP             0x09
#define SCMD_FIL_ENDDING          0x0A
#define SCMD_FIL_FINISHED         0x0B
#define SCMD_FIL_MEDIA            0x0C
#define SCMD_FIL_RECOVERY_PRINT   0x0D

#define CMD_MAINTENANCE           0x05
#define SCMD_MTN_LOAD_SETTING     0x01
#define SCMD_MTN_SAVE_SETTING     0x02
#define SCMD_MTN_DEFAULT_SETTING  0x03
#define SCMD_MTN_GET_MACHINE_DEF  0x04
#define SCMD_MTN_GET_MACHINE_INFO 0x05
#define SCMD_MTN_GET_CONFIGS      0x06
#define SCMD_MTN_SET_FIL_SENSOR   0x07
#define SCMD_MTN_SET_POWERLOST_SENSOR 0x08

