/**
 * @file main.cpp
 * @author r4wk (r4wknet@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <app.h>

/** BLE Name */
char g_ble_dev_name[10] = "Soaker";
/** LoRa Packet Size */
uint16_t PACKET_SIZE = 222;
/** INT array to send dummy data */
int *fake_data = new int[PACKET_SIZE];
/** Time between packets */
#define SLEEP_TIME 10000
/** Forward declaration */
void send_lora_data();
uint8_t* convert_byte(const std::string& hex_string);
void setup_lorawan();

/**
 * @brief Set the up app object
 * 
 */
void setup_app(void)
{
	g_enable_ble = true;
	api_set_version(1, 0, 2);
}

/**
 * @brief Initialize App
 * Fill array with 1's
 * Start LoRa send timer, 10s
 * 
 * @return true 
 * @return false 
 */
bool init_app(void)
{
	MYLOG("APP", "Data Soaker started");
	setup_lorawan();
	api_timer_stop();
    g_lorawan_settings.send_repeat_time = SLEEP_TIME;
    api_timer_restart(SLEEP_TIME);
	std::fill(fake_data, fake_data+PACKET_SIZE, 1);
	return true;
}

/**
 * @brief React to event trigger and send LoRa data
 * 
 */
void app_event_handler(void)
{
	if ((g_task_event_type & STATUS) == STATUS)
	{
		g_task_event_type &= N_STATUS;
		MYLOG("APP", "Woke up");
		send_lora_data();
	}
}

/**
 * @brief Not used
 * 
 */
void lora_data_handler(void)
{

}

/**
 * @brief BLE Data handling
 * 
 */
void ble_data_handler(void)
{
	if (g_enable_ble)
	{
		if ((g_task_event_type & BLE_DATA) == BLE_DATA)
		{
			g_task_event_type &= N_BLE_DATA;

			while (g_ble_uart.available() > 0)
			{
				at_serial_input(uint8_t(g_ble_uart.read()));
				delay(5);
			}
			at_serial_input(uint8_t('\n'));
		}
	}
}

/** Hard code LoRaWAN settings
 * If DEV EUI is not set. Use default settings.
 */
void setup_lorawan() {
	if (!node_device_eui.empty())
	{
		MYLOG("LORA", "Using hardcoded LoRa settings");
		api_read_credentials();
		g_lorawan_settings.auto_join = auto_join;
		g_lorawan_settings.otaa_enabled = otaa_enabled;
		memcpy(g_lorawan_settings.node_device_eui, convert_byte(node_device_eui), 8);
		memcpy(g_lorawan_settings.node_app_eui, convert_byte(node_app_eui), 8);
		memcpy(g_lorawan_settings.node_app_key, convert_byte(node_app_key), 16);
		memcpy(g_lorawan_settings.node_nws_key, convert_byte(node_nws_key), 16);
		memcpy(g_lorawan_settings.node_apps_key, convert_byte(node_apps_key), 16);
		g_lorawan_settings.node_dev_addr = node_dev_addr;
		g_lorawan_settings.send_repeat_time = send_repeat_time;
		g_lorawan_settings.adr_enabled = adr_enabled;
		g_lorawan_settings.public_network = public_network;
		g_lorawan_settings.duty_cycle_enabled = duty_cycle_enabled;
		g_lorawan_settings.join_trials = join_trials;
		g_lorawan_settings.tx_power = tx_power;
		g_lorawan_settings.data_rate = data_rate;
		g_lorawan_settings.lora_class = lora_class;
		g_lorawan_settings.subband_channels = subband_channels;
		g_lorawan_settings.app_port = app_port;
		g_lorawan_settings.confirmed_msg_enabled = confirmed_msg_enabled;
		g_lorawan_settings.resetRequest = resetRequest;
		g_lorawan_settings.lora_region = lora_region;
		api_set_credentials();
	}
}

/**
 * @brief Send LoRaWAN packet with PACKET_SIZE
 * 
 * @param unused 
 */
void send_lora_data()
{
	lmh_error_status result = send_lora_packet((uint8_t *)fake_data, PACKET_SIZE);
	switch (result)
	{
		case LMH_SUCCESS:
		MYLOG("APP", "LoRa packet sent");
		break;

		case LMH_BUSY:
		MYLOG("APP", "LoRa radio busy");
		break;

		case LMH_ERROR:
		MYLOG("APP", "LoRa radio error");
		api_timer_stop();
		break;
	}
}

/**
 * @brief Convert string to bytes
 * 
 * @param hex_string 
 * @return uint8_t* 
 */
uint8_t* convert_byte(const std::string& hex_string) {
    if (hex_string.length() != 16 && hex_string.length() != 32) {
        MYLOG("APP", "Invalid hex string length!");
        return nullptr;
    }

    uint8_t byte_array_size = hex_string.length() / 2;
    uint8_t* bytes = new uint8_t[byte_array_size];

    for (size_t i = 0; i < byte_array_size; ++i) {
        std::string byteString = hex_string.substr(i * 2, 2);
        bytes[i] = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
    }

    return bytes;
}
