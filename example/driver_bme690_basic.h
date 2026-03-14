/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bme690_basic.h
 * @brief     driver bme690 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-03-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/03/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BME690_BASIC_H
#define DRIVER_BME690_BASIC_H

#include "driver_bme690_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bme690_example_driver bme690 example driver function
 * @brief    bme690 example driver modules
 * @ingroup  bme690_driver
 * @{
 */

/**
 * @brief bme690 basic example default definition
 */
#define BME690_BASIC_DEFAULT_TEMPERATURE_OVERSAMPLING        BME690_OVERSAMPLING_x2            /**< temperature oversampling x2 */
#define BME690_BASIC_DEFAULT_PRESSURE_OVERSAMPLING           BME690_OVERSAMPLING_x16           /**< pressure oversampling x16 */
#define BME690_BASIC_DEFAULT_HUMIDITY_OVERSAMPLING           BME690_OVERSAMPLING_x1            /**< humidity oversampling x1 */
#define BME690_BASIC_DEFAULT_FILTER                          BME690_FILTER_COEFF_15            /**< filter coeff 15 */
#define BME690_BASIC_DEFAULT_SPI_WIRE                        BME690_SPI_WIRE_4                 /**< spi wire 4 */

/**
 * @brief     basic example init
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bme690_basic_init(bme690_interface_t interface, bme690_address_t addr_pin);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bme690_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *temperature pointer to a converted temperature buffer
 * @param[out] *pressure pointer to a converted pressure buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bme690_basic_read(float *temperature, float *pressure, float *humidity_percentage);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
