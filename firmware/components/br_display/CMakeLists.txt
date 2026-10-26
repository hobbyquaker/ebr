file(GLOB font_srcs "${CMAKE_CURRENT_SOURCE_DIR}/fonts/*.c")

idf_component_register(SRCS "src/br_display.c" "src/br_status.c" "src/br_ui.c" "src/br_radio.c" ${font_srcs}
                       INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS "src"
                       REQUIRES esp_netif
                       PRIV_REQUIRES esp_app_format esp_lcd esp_driver_spi esp_driver_gpio esp_driver_ledc esp_timer openthread)
