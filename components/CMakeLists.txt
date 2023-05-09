idf_build_get_property(target IDF_TARGET)

set(srcs nvs_cxx.cpp wlx_cxx.cpp)
set(requires esp_timer esp_event)

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES freertos nvs_flash esp_wifi
                    REQUIRES ${requires})
