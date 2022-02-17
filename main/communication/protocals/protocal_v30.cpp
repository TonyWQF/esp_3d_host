#include "protocal_v30.h"

/** @brief  Parse data
  * @retval Command pack length
  */
int ProtocalV30::Parse() {
  uint16_t tmp_len, buffer_size, tmp_tail, tmp_head;
  uint8_t cmd_l, cmd_h;
  uint16_t pack_len;


  tmp_head = head;
  tmp_tail = tail;
  buffer_size = sizeof(read_buffer);
  tmp_len = (tmp_head + buffer_size - tmp_tail) % buffer_size;
  parsed_length = 0;
  
  while(tmp_len > 7) {
    if(read_buffer[tmp_tail] != prefix_0) {
      tail = (tail + 1) % buffer_size;
      tmp_tail = tail;
      tmp_len--;
      continue;
    }
    if(read_buffer[(tmp_tail + 1) % buffer_size] != prefix_1) {
      tail = (tail + 2) % buffer_size;
      tmp_tail = tail;
      tmp_len = tmp_len - 2;
      continue;
    }

    // Pack size
    cmd_l = read_buffer[(tmp_tail + 3) % buffer_size];
    cmd_h = read_buffer[(tmp_tail + 4) % buffer_size];
    if((cmd_l ^ cmd_h) != read_buffer[(tmp_tail + 5) % buffer_size]) {
      tail = (tail + 2) % buffer_size;
      tmp_tail = tail;
      tmp_len = tmp_len - 2;
      continue;
    }
    pack_len = (cmd_h << 8) | cmd_l;
    // Package size exceed 768 bytes
    if(pack_len > 768) {
      tail = (tail + 2) % buffer_size;
      tmp_tail = tail;
      tmp_len = tmp_len - 2;
      continue;
    }
    // Check if there are enougth data received
    if(pack_len + 8 > tmp_len) {
      return 0;
    }

    // Copy data
    uint16_t checksum = 0;
    uint16_t checkget = (read_buffer[(tmp_tail + 7) % buffer_size] << 8) | read_buffer[(tmp_tail + 6) % buffer_size];
    for(int i=0;i<pack_len;i++) {
      parsed_buffer[i] = read_buffer[(tmp_tail + 8 + i) % buffer_size];
      checksum += parsed_buffer[i];
    }
    // Verify fail
    if(checksum != checkget) {
      tail = (tail + 2) % buffer_size;
      tmp_tail = tail;
      tmp_len = tmp_len - 2;
      continue;
    }
    parsed_length = pack_len;
    tail = (tmp_tail + pack_len + 8) % buffer_size;
    return pack_len;
  }
  return 0;
}

/** @brief  Process command
  * @retval None
  */
void ProtocalV30::ProcessCommand() {
  Command = parsed_buffer[0];
  SubCommand = parsed_buffer[1];
  state = parsed_buffer[2];
  cur_machine_status.printer_status = parsed_buffer[3];
  switch(Command) {
    case CMD_STATUS:
      switch (SubCommand) {
        case SCMD_STAT_MACHINE:
          StatusHandle();
        break;

        case SCMD_STAT_FEEDRATE:
          GetFeedrateHandle();
        break;

        case SCMD_STAT_POWERLOST_FLAG:
        break;
        
        default:
        break;
      }
    break;

    case CMD_ADJUST:
    break;

    case CMD_PRINT:
    break;

    case CMD_FILES:
      switch(SubCommand) {
        case SCMD_FIL_LIST_START:
        case SCMD_FIL_LIST_NEXT:
        case SCMD_FIL_LIST_PREVIOUS:
          FileListHandle();
        break;
      }
    break;

    case CMD_MAINTENANCE:
      switch(SubCommand) {
        case SCMD_MTN_GET_CONFIGS:
          SensorEnableHandle();
        break;
      }
    break;
  }

  // if(pfun != 0)
  //   pfun(parsed_buffer);

}

/** @brief  Setup a package
  * @param  pSource: Data to be packed up
  * @param  Length: Size of the source data
  * @retval Size of the data packed
  */
int ProtocalV30::SetupPackage(uint8_t *pSource, uint8_t *pDestination, uint16_t Length) {
  int i = 0;
  uint32_t checksum = 0;
  pack_up_size = 0;
  
  pDestination[i++] = prefix_0;
  pDestination[i++] = prefix_1;
  pDestination[i++] = 0x30;
  pDestination[i++] = (uint8_t)(Length);
  pDestination[i++] = (uint8_t)(Length >> 8);
  pDestination[i++] = pDestination[3] ^ pDestination[4];
  // Fill checksum with zero
  pDestination[i++] = 0;
  pDestination[i++] = 0;
  for(int j=0;j<Length;j++) {
    checksum = checksum + pSource[j];
    pDestination[i++] = pSource[j];
  }
  // Refill checksum
  pDestination[6] = (uint8_t)(checksum);
  pDestination[7] = (uint8_t)(checksum >> 8);
  pack_up_size = i;
  return i;
}
