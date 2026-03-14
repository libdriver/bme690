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
 * @file      main.c
 * @brief     main source file
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

#include "driver_bme690_read_test.h"
#include "driver_bme690_register_test.h"
#include "driver_bme690_parallel_test.h"
#include "driver_bme690_basic.h"
#include "driver_bme690_gas.h"
#include "driver_bme690_parallel.h"
#include <getopt.h>
#include <stdlib.h>

static uint8_t gs_flag = 0;        /**< local flag */
static const float gsc_heater_temp_prof[] = {320.0f, 100.0f, 330.0f, 350.0f, 
                                             400.0f, 150.0f, 200.0f, 250.0f, 
                                             300.0f, 350.0f};                        /**< store the heater temperature profile in degree celsius */
static const uint8_t gsc_heater_dur_prof[] = {5, 10, 5, 5, 5, 10, 5, 5, 5, 5};       /**< number of times tphg sequence needs to be repeated */
static const float gsc_shared_heater_dur = 140.0f;                                   /**< 140ms */

/**
 * @brief     interface receive callback
 * @param[in] status running status
 * @param[in] *data pointer to a parallel data address
 * @param[in] len data length
 * @note      none
 */
static void a_receive_callback(uint8_t status, bme690_parallel_data_t *data, uint8_t len)
{
    switch (status)
    {
        case BME690_STATUS_CHANNEL_DATA :
        {
            /* output */
            bme690_interface_debug_print("bme690: irq channel data.\n");
            
            /* print all */
            bme690_interface_debug_print("bme690: [%d] temperature raw is 0x%08X.\n", data->channel, data->temperature_raw);
            bme690_interface_debug_print("bme690: [%d] temperature is %0.2fC.\n", data->channel, data->temperature_c);
            bme690_interface_debug_print("bme690: [%d] pressure raw is 0x%08X.\n", data->channel, data->pressure_raw);
            bme690_interface_debug_print("bme690: [%d] pressure is %0.2fpa.\n", data->channel, data->pressure_pa);
            bme690_interface_debug_print("bme690: [%d] humidity raw is 0x%08X.\n", data->channel, data->humidity_raw);
            bme690_interface_debug_print("bme690: [%d] humidity is %0.2f%%.\n",  data->channel, data->humidity_percentage);
            bme690_interface_debug_print("bme690: [%d] adc raw is 0x%04X.\n",  data->channel, data->adc_raw);
            bme690_interface_debug_print("bme690: [%d] adc range is 0x%02X.\n",  data->channel, data->adc_range);
            bme690_interface_debug_print("bme690: [%d] resistance ohms is %0.2fohms.\n", data->channel,data->ohms);
            
            break;
        }
        case BME690_STATUS_ALL_DATA :
        {
            uint8_t i;
            
            /* output */
            bme690_interface_debug_print("bme690: irq all data.\n");
            
            /* print all */
            for (i = 0; i < len; i++)
            {
                bme690_interface_debug_print("bme690: [%d] temperature raw is 0x%08X.\n", i, data[i].temperature_raw);
                bme690_interface_debug_print("bme690: [%d] temperature is %0.2fC.\n", i, data[i].temperature_c);
                bme690_interface_debug_print("bme690: [%d] pressure raw is 0x%08X.\n", i, data[i].pressure_raw);
                bme690_interface_debug_print("bme690: [%d] pressure is %0.2fpa.\n", i, data[i].pressure_pa);
                bme690_interface_debug_print("bme690: [%d] humidity raw is 0x%08X.\n", i, data[i].humidity_raw);
                bme690_interface_debug_print("bme690: [%d] humidity is %0.2f%%.\n",  i, data[i].humidity_percentage);
                bme690_interface_debug_print("bme690: [%d] adc raw is 0x%04X.\n",  i, data[i].adc_raw);
                bme690_interface_debug_print("bme690: [%d] adc range is 0x%02X.\n",  i, data[i].adc_range);
                bme690_interface_debug_print("bme690: [%d] resistance ohms is %0.2fohms.\n", i, data[i].ohms);
            }
            
            /* flag done */
            gs_flag = 1;
            
            break;
        }
        case BME690_STATUS_SEQUENCE_LOST :
        {
            /* output */
            bme690_interface_debug_print("bme690: irq sequence lost.\n");
            
            /* parallel reset */
            (void)bme690_parallel_server_reset();
            
            /* flag error */
            gs_flag = 2;
            
            break;
        }
        default :
        {
            bme690_interface_debug_print("bme690: unknown code.\n");
            
            break;
        }
    }
}

/**
 * @brief     bme690 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t bme690(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"interface", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {"index", required_argument, NULL, 4},
        {"degree", required_argument, NULL, 5},
        {"wait", required_argument, NULL, 6},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint8_t index = 0;
    uint32_t times = 3;
    float degree_celsius = 200.0f;
    uint16_t gas_wait_ms = 150;
    bme690_interface_t interface = BME690_INTERFACE_IIC;
    bme690_address_t addr = BME690_ADDRESS_ADO_LOW;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running addr pin */
            case 1 :
            {
                if (strcmp("0", optarg) == 0)
                {
                    addr = BME690_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = BME690_ADDRESS_ADO_HIGH;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running interface */
            case 2 :
            {
                if (strcmp("iic", optarg) == 0)
                {
                    interface = BME690_INTERFACE_IIC;
                }
                else if (strcmp("spi", optarg) == 0)
                {
                    interface = BME690_INTERFACE_SPI;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* index */
            case 4 :
            {
                /* set the index */
                index = (uint8_t)atol(optarg);
                
                break;
            }
            
            /* degree */
            case 5 :
            {
                /* set degree */
                degree_celsius = (float)atof(optarg);
                
                break;
            }
            
            /* wait */
            case 6 :
            {
                /* set wait */
                gas_wait_ms = (uint16_t)atol(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        uint8_t res;
        
        /* run the reg test */
        res = bme690_register_test(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = bme690_read_test(interface, addr, index, times);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_parallel", type) == 0)
    {
        uint8_t res;
        
        /* run the parallel test */
        res = bme690_parallel_test(interface, addr, times);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature_c;
        float pressure_pa;
        float humidity_percentage;
        
        /* basic init */
        res = bme690_basic_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            bme690_interface_delay_ms(1000);
            
            /* read data */
            res = bme690_basic_read((float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage);
            if (res != 0)
            {
                (void)bme690_basic_deinit();
                
                return 1;
            }
            
            /* output */
            bme690_interface_debug_print("bme690: %d/%d.\n", i + 1, times);
            bme690_interface_debug_print("bme690: temperature is %0.2fC.\n", temperature_c);
            bme690_interface_debug_print("bme690: pressure is %0.2fPa.\n", pressure_pa);
            bme690_interface_debug_print("bme690: humidity is %0.2f%%.\n", humidity_percentage);
        }
        
        /* deinit */
        (void)bme690_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_gas", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature_c;
        float pressure_pa;
        float humidity_percentage;
        float ohms;
        
        /* gas init */
        res = bme690_gas_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            bme690_interface_delay_ms(1000);
            
            /* read data */
            res = bme690_gas_read(degree_celsius, gas_wait_ms, index,
                                 (float *)&temperature_c, (float *)&pressure_pa, 
                                 (float *)&humidity_percentage, (float *)&ohms);
            if (res != 0)
            {
                (void)bme690_gas_deinit();
                
                return 1;
            }
            
            /* output */
            bme690_interface_debug_print("bme690: %d/%d.\n", i + 1, times);
            bme690_interface_debug_print("bme690: temperature is %0.2fC.\n", temperature_c);
            bme690_interface_debug_print("bme690: pressure is %0.2fPa.\n", pressure_pa);
            bme690_interface_debug_print("bme690: humidity is %0.2f%%.\n", humidity_percentage);
            bme690_interface_debug_print("bme690: gas index is %d.\n", index);
            bme690_interface_debug_print("bme690: degree celsius is %0.1fC.\n", degree_celsius);
            bme690_interface_debug_print("bme690: gas wait is %d ms.\n", gas_wait_ms);
            bme690_interface_debug_print("bme690: gas resistance is %0.2fohms.\n", ohms);
        }
        
        /* deinit */
        (void)bme690_gas_deinit();
        
        return 0;
    }
    else if (strcmp("e_parallel", type) == 0)
    {
        uint8_t res;
        bme690_parallel_config_t config;
        
        /* parallel config */
        config.heater_temp_prof = gsc_heater_temp_prof;
        config.heater_dur_prof = gsc_heater_dur_prof;
        config.profile_len = 10;
        config.shared_heater_dur = gsc_shared_heater_dur;
        res = bme690_parallel_init(interface, addr, &config, a_receive_callback);
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        bme690_interface_debug_print("bme690: parallel sample.\n");
        
        /* init 0 */
        gs_flag = 0;
        
        /* loop all */
        while (1)
        {
            /* parallel server */
            (void)bme690_parallel_server();
            
            /* delay */
            bme690_interface_delay_ms((uint32_t)gsc_shared_heater_dur);
            
            /* check flag */
            if (gs_flag != 0)
            {
                if (gs_flag == 2)
                {
                    bme690_interface_debug_print("bme690: find error.\n");
                    (void)bme690_parallel_deinit(); 
                    
                    return 1;
                }
                
                /* init 0 */
                gs_flag = 0;
                
                /* check times */
                if (times != 0)
                {
                    times--;
                    
                    /* check times */
                    if (times == 0)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        
        /* output */
        bme690_interface_debug_print("bme690: parallel done.\n");
        
        /* deinit */
        (void)bme690_parallel_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        bme690_interface_debug_print("Usage:\n");
        bme690_interface_debug_print("  bme690 (-i | --information)\n");
        bme690_interface_debug_print("  bme690 (-h | --help)\n");
        bme690_interface_debug_print("  bme690 (-p | --port)\n");
        bme690_interface_debug_print("  bme690 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]\n");
        bme690_interface_debug_print("  bme690 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--times=<num>]\n");
        bme690_interface_debug_print("  bme690 (-t parallel | --test=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme690_interface_debug_print("  bme690 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme690_interface_debug_print("  bme690 (-e gas | --example=gas) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>]\n");
        bme690_interface_debug_print("         [--degree=<degree>] [--wait=<ms>] [--times=<num>]\n");
        bme690_interface_debug_print("  bme690 (-e parallel | --example=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme690_interface_debug_print("\n");
        bme690_interface_debug_print("Options:\n");
        bme690_interface_debug_print("      --addr=<0 | 1>                 Set the chip iic address.([default: 0])\n");
        bme690_interface_debug_print("      --degree=<degree>              Set the heater expected temperature in degree celsius.([default: 200.0])\n");
        bme690_interface_debug_print("  -e <read | gas | parallel>, --example=<read | gas | parallel>\n");
        bme690_interface_debug_print("                                     Run the driver example.\n");
        bme690_interface_debug_print("  -h, --help                         Show the help.\n");
        bme690_interface_debug_print("  -i, --information                  Show the chip information.\n");
        bme690_interface_debug_print("      --index=<index>                Set the heater index and it range is 0 - 9.([default: 0])\n");
        bme690_interface_debug_print("      --interface=<iic | spi>        Set the chip interface.([default: iic])\n");
        bme690_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        bme690_interface_debug_print("  -t <reg | read | parallel>, --test=<reg | read | parallel>\n");
        bme690_interface_debug_print("                                     Run the driver test.\n");
        bme690_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");
        bme690_interface_debug_print("      --wait=<ms>                    Set the heater wait time in ms.([default: 150])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        bme690_info_t info;
        
        /* print bme690 info */
        bme690_info(&info);
        bme690_interface_debug_print("bme690: chip is %s.\n", info.chip_name);
        bme690_interface_debug_print("bme690: manufacturer is %s.\n", info.manufacturer_name);
        bme690_interface_debug_print("bme690: interface is %s.\n", info.interface);
        bme690_interface_debug_print("bme690: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bme690_interface_debug_print("bme690: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bme690_interface_debug_print("bme690: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bme690_interface_debug_print("bme690: max current is %0.2fmA.\n", info.max_current_ma);
        bme690_interface_debug_print("bme690: max temperature is %0.1fC.\n", info.temperature_max);
        bme690_interface_debug_print("bme690: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        bme690_interface_debug_print("bme690: SPI interface SCK connected to GPIO11(BCM).\n");
        bme690_interface_debug_print("bme690: SPI interface MISO connected to GPIO9(BCM).\n");
        bme690_interface_debug_print("bme690: SPI interface MOSI connected to GPIO10(BCM).\n");
        bme690_interface_debug_print("bme690: SPI interface CS connected to GPIO8(BCM).\n");
        bme690_interface_debug_print("bme690: IIC interface SCL connected to GPIO3(BCM).\n");
        bme690_interface_debug_print("bme690: IIC interface SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = bme690(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        bme690_interface_debug_print("bme690: run failed.\n");
    }
    else if (res == 5)
    {
        bme690_interface_debug_print("bme690: param is invalid.\n");
    }
    else
    {
        bme690_interface_debug_print("bme690: unknown status code.\n");
    }

    return 0;
}
