# Spike for step 3 of notes/matter-device.md ("Plan"): the border router as a Matter-over-Thread device that is
# paired over Bluetooth through the H2 and gets the Thread dataset from the pairing. Based on esp-matter's
# examples/thread_border_router (CC0), for the P4 with Ethernet. Needs ESP_MATTER_PATH (esp-matter release/v1.6).
cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED ENV{ESP_MATTER_PATH})
    message(FATAL_ERROR "Please set ESP_MATTER_PATH to the path of esp-matter repo")
endif()

# No buttons or LEDs through esp-matter's device HAL
set(ENV{ESP_MATTER_DEVICE_PATH} $ENV{ESP_MATTER_PATH}/device_hal/device/hollow)
# The H2 firmware (Thread RCP + BLE controller), packed into rcp_fw; CONFIG_RCP_SRC_DIR reads this
set(ENV{BR_RCP_BUILD_DIR} "${CMAKE_CURRENT_LIST_DIR}/../rcp_h2/build")

set(ESP_MATTER_PATH $ENV{ESP_MATTER_PATH})
set(MATTER_SDK_PATH ${ESP_MATTER_PATH}/connectedhomeip/connectedhomeip)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
include($ENV{ESP_MATTER_DEVICE_PATH}/esp_matter_device.cmake)

# Not esp-matter's device HAL (device_hal/device, its led_driver and an old button component): we have no
# Matter LEDs or buttons, and that button component breaks esp_lvgl_port's button support (other API version)
set(EXTRA_COMPONENT_DIRS
    "${MATTER_SDK_PATH}/config/esp32/components"
    "${ESP_MATTER_PATH}/components")

project(ebr)

idf_build_set_property(CXX_COMPILE_OPTIONS "-std=gnu++17;-Os;-DCHIP_HAVE_CONFIG_H" APPEND)
idf_build_set_property(C_COMPILE_OPTIONS "-Os" APPEND)
idf_build_set_property(COMPILE_OPTIONS "-Wno-format-nonliteral;-Wno-format-security" APPEND)

# Manufacturer and product as Apple Home shows them (Basic Information cluster); the project is "ebr" (esp border
# router), decided 2026-10-20
idf_build_set_property(COMPILE_OPTIONS
    "-DCHIP_DEVICE_CONFIG_DEVICE_VENDOR_NAME=\"hobbyquaker\";-DCHIP_DEVICE_CONFIG_DEVICE_PRODUCT_NAME=\"ebr\""
    APPEND)

# Own test pairing data instead of Espressif's 20202021/3840, which the C6 dataset donor (paired in Apple Home)
# uses too - with the same code the Home app aborted at once ("pairing failed"). Still test parameters
# (ENABLE_TEST_SETUP_PARAMS); a real product would provision these per device in a factory partition.
# The verifier from connectedhomeip's scripts/tools/spake2p/spake2p.py gen-verifier -p 49582731
# -s U1BBS0UyUCBLZXkgU2FsdA== -i 1000 (the default test salt and iteration count).
idf_build_set_property(COMPILE_OPTIONS
    "-DCHIP_DEVICE_CONFIG_USE_TEST_SETUP_PIN_CODE=49582731;-DCHIP_DEVICE_CONFIG_USE_TEST_SETUP_DISCRIMINATOR=0xA5C"
    APPEND)
idf_build_set_property(COMPILE_OPTIONS
    "-DCHIP_DEVICE_CONFIG_USE_TEST_SPAKE2P_VERIFIER=\"Lu9FytdcJPRS7nZoX6zhYYjnGWyRwfcs8tb8Tt7uMckE7nG9RJskLfqwzY0iqvDTWLCvku887tt/zdjmUq4WzftEfcssnwH+9Z8a3zHNKBuhHUhcpJjO7KvejDVmdD3URw==\""
    APPEND)
