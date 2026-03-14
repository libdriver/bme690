[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME690

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme690/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BME690是小巧的四合一空气质量传感器，用于监测室内空气质量，能够检测挥发性有机化合物(VOC)、挥发性硫化合物(VSC)及其他气体。BME690是基于BME688进一步开发的型号，耐用性增强，适用于高冷凝水平的环境。

LibDriver BME690是LibDriver推出的BME690全功能驱动，该驱动提供大气压强，温度，湿度和气体读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel) 
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver BME690的源文件。

/interface目录包含了LibDriver BME690与平台无关的IIC、SPI总线模板。

/test目录包含了LibDriver BME690驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver BME690编程范例。

/doc目录包含了LibDriver BME690离线文档。

/datasheet目录包含了BME690数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC、SPI总线模板，完成指定平台的IIC、SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_bme690_basic.h"

uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;

/* basic init */
res = bme690_basic_init(BME690_INTERFACE_IIC, BME690_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
    bme690_interface_debug_print("bme690: %d/%d.\n", i + 1, 3);
    bme690_interface_debug_print("bme690: temperature is %0.2fC.\n", temperature_c);
    bme690_interface_debug_print("bme690: pressure is %0.2fPa.\n", pressure_pa);
    bme690_interface_debug_print("bme690: humidity is %0.2f%%.\n", humidity_percentage);
    
    ...
}

...
    
/* deinit */
(void)bme690_basic_deinit();

return 0;
```

#### example gas

```C
#include "driver_bme690_gas.h"

uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;
float ohms;
uint8_t index = 0;
float degree_celsius = 200.0f;
uint16_t gas_wait_ms = 150;

/* gas init */
res = bme690_gas_init(BME690_INTERFACE_IIC, BME690_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    bme690_interface_delay_ms(1000);

    /* read data */
    res = bme690_gas_read(degree_celsius, gas_wait_ms, index,
                         (float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage, (float *)&ohms);
    if (res != 0)
    {
        (void)bme690_gas_deinit();

        return 1;
    }

    /* output */
    bme690_interface_debug_print("bme690: %d/%d.\n", i + 1, 3);
    bme690_interface_debug_print("bme690: temperature is %0.2fC.\n", temperature_c);
    bme690_interface_debug_print("bme690: pressure is %0.2fPa.\n", pressure_pa);
    bme690_interface_debug_print("bme690: humidity is %0.2f%%.\n", humidity_percentage);
    bme690_interface_debug_print("bme690: gas index is %d.\n", index);
    bme690_interface_debug_print("bme690: degree celsius is %0.1fC.\n", degree_celsius);
    bme690_interface_debug_print("bme690: gas wait is %d ms.\n", gas_wait_ms);
    bme690_interface_debug_print("bme690: gas resistance is %0.2fohms.\n", ohms);
    
    ...
}

...
    
/* deinit */
(void)bme690_gas_deinit();

return 0;
```
#### example parallel

```C
#include "driver_bme690_parallel.h"

uint8_t res;
bme690_parallel_config_t config;
static uint8_t gs_flag = 0;
static const float gsc_heater_temp_prof[] = {320.0f, 100.0f, 330.0f, 350.0f, 
                                             400.0f, 150.0f, 200.0f, 250.0f, 
                                             300.0f, 350.0f};  
static const uint8_t gsc_heater_dur_prof[] = {5, 10, 5, 5, 5, 10, 5, 5, 5, 5}; 
static const float gsc_shared_heater_dur = 140.0f; 

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

...
    
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
    
    ...
}

...
    
/* output */
bme690_interface_debug_print("bme690: parallel done.\n");

/* deinit */
(void)bme690_parallel_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/bme690/index.html](https://www.libdriver.com/docs/bme690/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。