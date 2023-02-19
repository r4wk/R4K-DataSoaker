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