idf_component_register(SRC_DIRS          "."
                       INCLUDE_DIRS      "."
                       LDFRAGMENTS "linker.lf")

target_compile_options(${COMPONENT_LIB} PRIVATE "-DCHIP_HAVE_CONFIG_H")

# ESP-IDF's OpenThread border router library (libopenthread_br.a, the discovery proxy) calls the mdns component,
# but openthread does not declare it; without a link dependency the symbols come too late in the link order.
idf_component_add_link_dependency(FROM openthread TO espressif__mdns)
