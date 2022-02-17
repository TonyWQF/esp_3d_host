# Embed the server root certificate into the final binary
#
# (If this was a component, we would set COMPONENT_EMBED_TXTFILES here.)
idf_component_register(
                    SRCS 
                        "main.cpp"
                        "esp_http_part.c"
                        "esp_usart_part.cpp"
                        "communication/protocals/uartcomm.cpp"
                        "communication/protocals/protocalbase.cpp"
                        "communication/protocals/protocal_v30.cpp"
                        "communication/protocals/V30/control.cpp"
                        "communication/protocals/V30/filelist.cpp"
                        "communication/protocals/V30/leveling.cpp"
                        "communication/protocals/V30/maintenance.cpp"
                        "communication/protocals/V30/status.cpp"
                    INCLUDE_DIRS 
                        "."
                        "./CircleArray"
                        "./communication/protocals"
                        "./communication/protocals/V30"
                    EMBED_TXTFILES howsmyssl_com_root_cert.pem)
