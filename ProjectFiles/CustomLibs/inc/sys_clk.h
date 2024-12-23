/**
  ******************************************************************************
  * @file    sys_clk.h
  * @author  ICV
  * @version V1.2.0
  * @date    05/12/2024
  * @brief   sys_CLK initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SysCLK_init
#define SysCLK_init


/**
 * @brief Enumerates the available configurations for the PLL (Phase-Locked Loop).
 * 
 * This enumeration defines different configuration modes for the PLL,
 * which can be used to initialize the clock settings of a microcontroller.
 * Each value corresponds to a specific PLL setup stored in an array of configurations.
 * 
 * @note The last enumerator, @ref NOT_VALID_CONFIG, represents the total number
 *       of valid configurations and can be used for bounds checking.
 */
typedef enum {
    FAST_CONFIG = 0,          /*!< Fast PLL configuration: prioritizes performance over power consumption. */
    SLOW_CONFIG = 1,          /*!< Slow PLL configuration: optimized for power efficiency. */
    // Add more configurations above this comment
    NOT_VALID_CONFIG          /*!< Number of valid configurations (used for array size and bounds checking). */
} PLL_configuration_t;

void Setup_CPU_Clock(PLL_configuration_t pll_config);

#endif /* SysCLK_init */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE sys_clk.h */
