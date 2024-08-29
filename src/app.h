/**
 * @file app.h
 * @author r4wk (r4wknet@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include <WisBlock-API.h> 

/** LoRaWAN Settings */
bool auto_join = true;                                    // Flag if node joins automatically after reboot
bool otaa_enabled = true;                                 // Flag for OTAA or ABP

/** Most important section is here
 * Dev EUI, APP EUI and APP KEY are probably
 * the only ones you will need
*/
std::string node_device_eui = "";                         // OTAA Device EUI MSB
std::string node_app_eui = "";                            // OTAA Application EUI MSB
std::string node_app_key = "";                            // OTAA Application Key MSB
std::string node_nws_key = "";		                        // ABP Network Session Key MSB
std::string node_apps_key = "";		                        // ABP Application Session key MSB
/** To here  */

uint32_t node_dev_addr = 0x26021FB4;								      // ABP Device Address MSB
uint32_t send_repeat_time = 11000;							          // Send repeat time in milliseconds: 2 * 60 * 1000 => 2 minutes
bool adr_enabled = false;									                // Flag for ADR on or off
bool public_network = true;								                // Flag for public or private network
bool duty_cycle_enabled = false;						              // Flag to enable duty cycle (validity depends on Region)
uint8_t join_trials = 5;									                // Number of join retries
uint8_t tx_power = 0;											                // TX power 0 .. 15 (validity depends on Region)
uint8_t data_rate = 3;										                // Data rate 0 .. 15 (validity depends on Region)
uint8_t lora_class = 0;										                // LoRaWAN class 0: A, 2: C, 1: B is not supported
uint8_t subband_channels = 2;							                // Subband channel selection 1 .. 9
uint8_t app_port = 2;											                // Data port to send data
lmh_confirm confirmed_msg_enabled = LMH_UNCONFIRMED_MSG; 	// Flag to enable confirmed messages
bool resetRequest = true;									                // Command from BLE to reset device
eLoRaMacRegion_t lora_region = LORAMAC_REGION_US915;		  // LoRa region

// Debug output set to 0 to disable app debug output
#ifndef MY_DEBUG
#define MY_DEBUG 1
#endif

#if MY_DEBUG > 0
#define MYLOG(tag, ...)           \
  do                            \
  {                             \
    if (tag)                  \
      PRINTF("[%s] ", tag); \
    PRINTF(__VA_ARGS__);      \
    PRINTF("\n");             \
  } while (0)
#else
#define MYLOG(...)
#endif

#endif