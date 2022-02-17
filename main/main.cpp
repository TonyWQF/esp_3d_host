
extern "C" {

extern void xc_usart_init();
extern void xc_sd_init();

extern void http_part();
extern void usart_part();

void app_main(void)
{   
    
    /*
    xc_sd_init  spi-mode -> sd
    #define PIN_NUM_MISO 19
    #define PIN_NUM_MOSI 23
    #define PIN_NUM_CLK  18
    #define PIN_NUM_CS   5
    
    idf.py menuconfig
    =====================
    (Top) --->Component config --->FAT Filesystem support

    fat:long filename support in heap(255)
    =====================
    */
    xc_sd_init();

    /*
    wifi init
    server handler init
    client process task
    */
    http_part();

    /*
    usart init
    usart data parse task
    (tx -> 3d printer board)
    (rx <- 3d printer board)
    */
    usart_part();

}

}


