#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "sdkconfig.h"

//   UART
#include "driver/uart.h"
#include "driver/gpio.h"


#include "uartcomm.h"

#define RX_BUF_SIZE 1024

/** @brief  Initialize
  * @retval None
  */
void UartCom::Init() {
  // Serial.begin(115200);

  protocal = (Protocal*)&v30protocal;
}

/** @brief  uart handle loop
  * @retval None
  */
void UartCom::Loop() {
  while(1){
    FillBuffer();
    Parse();
    AutoRequestStatus();
  }
}

/** @brief  Fill ring buffer
  * @retval None
  */
void UartCom::FillBuffer() {
  // while(Serial.available()) {
  //   int c = Serial.read();
  //   if(c < 0)
  //     break;
  //   protocal->PushOneByte((uint8_t)c);
  // }

  static const char *RX_TASK_TAG = "RX_TASK";
  esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
  uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);

  const int rxBytes = uart_read_bytes(UART_NUM_2, data, RX_BUF_SIZE, 1000 / portTICK_RATE_MS);
  if (rxBytes > 0) {
      data[rxBytes] = 0;
      for(int i = 0; i<rxBytes;i++){
        protocal->PushOneByte((uint8_t)data[i]);
      }
      
      ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
      ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
  }

  free(data);

}

/** @brief  Parse data
  * @retval None
  */
void UartCom::Parse() {
  if(protocal->Parse())
    protocal->ProcessCommand();
}

/** @brief  Auto request machine status
  * @retval None
  */
void UartCom::AutoRequestStatus() {
  // if(auto_request_tick < millis()) {
    // auto_request_tick = millis() + 1000;
    // RequestMachineStatus();
  // }
  if(auto_request_tick < xTaskGetTickCount()) {
      auto_request_tick = xTaskGetTickCount() + 1000;
      AutoRequestStatus();
  }
}

extern int sendData(const char* logName, const char* data);

/** @brief  Send package
  * @retval None
  */
void UartCom::SendPackage() { 
  // Serial.write(send_package, protocal->GetPackupSize() ); 
  uart_write_bytes(UART_NUM_2, send_package, protocal->GetPackupSize());
}

UartCom SComm3;