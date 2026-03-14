[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME690

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme690/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BME690は、室内空気質を監視するための世界最小の4in1空気質センサーであり、揮発性有機化合物（VOC）、揮発性硫黄化合物（VSC）、およびその他のガスを検出できます。BME690はBME688をさらに改良したもので、結露レベルの高い環境での使用に対応できるよう堅牢性が向上しています。

LibDriver BME690は、LibDriverがリリースしたBME690のフル機能ドライバです。圧力、温度、湿度、ガス測定機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver BME690のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver BME690用のプラットフォームに依存しないIIC, SPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver BME690ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver BME690プログラミング例が含まれています。

/ docディレクトリには、LibDriver BME690オフラインドキュメントが含まれています。

/ datasheetディレクトリには、BME690データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIIC, SPIバステンプレートを参照して、指定したプラットフォームのIIC, SPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/bme690/index.html](https://www.libdriver.com/docs/bme690/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。