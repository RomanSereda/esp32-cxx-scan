#include "wlx_cxx.hpp"

namespace wlx_cxx {
void wifi::init()
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

void wifi::create_sta()
{
    esp_netif = esp_netif_create_default_wifi_sta();
    assert(esp_netif);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi::destroy()
{
    ESP_ERROR_CHECK(esp_wifi_stop());
    esp_netif_destroy(esp_netif);
}
    
}