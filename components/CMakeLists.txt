idf_build_get_property(target IDF_TARGET)

set(srcs "nvs_cxx.cpp")

#target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES freertos nvs_flash)
