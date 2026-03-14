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
 * @file      driver_bme690_parallel.c
 * @brief     driver bme690 parallel source file
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

#include "driver_bme690_parallel.h"

static bme690_handle_t gs_handle;        /**< bme690 handle */

/**
 * @brief     parallel example init
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @param[in] *config pointer to a parallel config structure
 * @param[in] *callback pointer to a callback address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bme690_parallel_init(bme690_interface_t interface, bme690_address_t addr_pin,
                             bme690_parallel_config_t *config, 
                             void (*callback)(uint8_t status, bme690_parallel_data_t *data, uint8_t len))
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_BME690_LINK_INIT(&gs_handle, bme690_handle_t); 
    DRIVER_BME690_LINK_IIC_INIT(&gs_handle, bme690_interface_iic_init);
    DRIVER_BME690_LINK_IIC_DEINIT(&gs_handle, bme690_interface_iic_deinit);
    DRIVER_BME690_LINK_IIC_READ(&gs_handle, bme690_interface_iic_read);
    DRIVER_BME690_LINK_IIC_WRITE(&gs_handle, bme690_interface_iic_write);
    DRIVER_BME690_LINK_SPI_INIT(&gs_handle, bme690_interface_spi_init);
    DRIVER_BME690_LINK_SPI_DEINIT(&gs_handle, bme690_interface_spi_deinit);
    DRIVER_BME690_LINK_SPI_READ(&gs_handle, bme690_interface_spi_read);
    DRIVER_BME690_LINK_SPI_WRITE(&gs_handle, bme690_interface_spi_write);
    DRIVER_BME690_LINK_DELAY_MS(&gs_handle, bme690_interface_delay_ms);
    DRIVER_BME690_LINK_DEBUG_PRINT(&gs_handle, bme690_interface_debug_print);
    DRIVER_BME690_LINK_RECEIVE_CALLBACK(&gs_handle, callback);
    
    /* set interface */
    res = bme690_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bme690_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set addr pin failed.\n");
       
        return 1;
    }
    
    /* bme690 init */
    res = bme690_init(&gs_handle);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: init failed.\n");
        
        return 1;
    }
    
    /* set sleep mode */
    res = bme690_set_mode(&gs_handle, BME690_MODE_SLEEP);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set mode failed.\n");
        (void)bme690_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default temperature oversampling */
    res = bme690_set_temperature_oversampling(&gs_handle, BME690_PARALLEL_DEFAULT_TEMPERATURE_OVERSAMPLING);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set temperature oversampling failed.\n");
        (void)bme690_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pressure oversampling */
    res = bme690_set_pressure_oversampling(&gs_handle, BME690_PARALLEL_DEFAULT_PRESSURE_OVERSAMPLING);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set pressure oversampling failed.\n");
        (void)bme690_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default humidity oversampling */
    res = bme690_set_humidity_oversampling(&gs_handle, BME690_PARALLEL_DEFAULT_HUMIDITY_OVERSAMPLING);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set humidity oversampling failed.\n");
        (void)bme690_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default filter */
    res = bme690_set_filter(&gs_handle, BME690_PARALLEL_DEFAULT_FILTER);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set filter failed.\n");
        (void)bme690_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default spi wire */
    res = bme690_set_spi_wire(&gs_handle, BME690_PARALLEL_DEFAULT_SPI_WIRE);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set spi wire failed.\n");
        (void)bme690_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set parallel config */
    res = bme690_parallel_config(&gs_handle, config);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: parallel config failed.\n");
        (void)bme690_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* disable heater off */
    res = bme690_set_heater_off(&gs_handle, BME690_BOOL_FALSE);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set heat off failed.\n");
        (void)bme690_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable run gas */
    res = bme690_set_run_gas(&gs_handle, BME690_BOOL_TRUE);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set run gas failed.\n");
        (void)bme690_deinit(&gs_handle); 
        
        return 1;
    }

    /* set parallel mode */
    res = bme690_set_mode(&gs_handle, BME690_MODE_PARALLEL);
    if (res != 0)
    {
        bme690_interface_debug_print("bme690: set mode failed.\n");
        (void)bme690_deinit(&gs_handle); 
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  parallel example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bme690_parallel_deinit(void)
{
    /* set sleep mode */
    if (bme690_set_mode(&gs_handle, BME690_MODE_SLEEP)  != 0)
    {
        return 1;
    }
    
    /* heater off */
    if (bme690_set_heater_off(&gs_handle, BME690_BOOL_TRUE) != 0)
    {
        return 1;
    }
    
    /* close bme690 */
    if (bme690_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  parallel example server
 * @return status code
 *         - 0 success
 *         - 1 server failed
 * @note   none
 */
uint8_t bme690_parallel_server(void)
{
    if (bme690_parallel_progress(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  parallel example server reset
 * @return status code
 *         - 0 success
 *         - 1 reset failed
 * @note   none
 */
uint8_t bme690_parallel_server_reset(void)
{
    if (bme690_parallel_reset(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
