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
	api_timer_stop();
    g_lorawan_settings.send_repeat_time = SLEEP_TIME;
    api_timer_restart(SLEEP_TIME);
	std::fill(fake_data, fake_data+PACKET_SIZE, 1);
	return true;
}

/**
 * @brief Not used
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
