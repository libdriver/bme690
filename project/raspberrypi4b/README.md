### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(bme690 REQUIRED)
```

### 3. BME690

#### 3.1 Command Instruction

1. Show bme690 chip and driver information.

   ```shell
   bme690 (-i | --information)
   ```

2. Show bme690 help.

   ```shell
   bme690 (-h | --help)
   ```

3. Show bme690 pin connections of the current board.

   ```shell
   bme690 (-p | --port)
   ```

4. Run bme690 register test.

   ```shell
   bme690 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

5. Run bme690 read test, num means the test times, index is the gas index. 

   ```shell
   bme690 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--times=<num>]
   ```

6. Run bme690 parallel test, num means the test times. 

   ```shell
   bme690 (-t parallel | --test=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```
   
7. Run bme690 read function, num means the read times. 

   ```shell
   bme690 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

8. Run bme690 gas function, num means the read times, index is the gas index, degree is the set degree, wait is the wait time in ms.

   ```shell
   bme690 (-e gas | --example=gas) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--degree=<degree>] [--wait=<ms>] [--times=<num>]
   ```
   
9. Run bme690 parallel function, num means the read times.

   ```shell
   bme690 (-e parallel | --example=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```
   
#### 3.2 Command Example

```shell
./bme690 -i

bme690: chip is Bosch BME690.
bme690: manufacturer is Bosch.
bme690: interface is IIC SPI.
bme690: driver version is 1.0.
bme690: min supply voltage is 1.7V.
bme690: max supply voltage is 3.6V.
bme690: max current is 0.85mA.
bme690: max temperature is 85.0C.
bme690: min temperature is -40.0C.
```

```shell
./bme690 -p

bme690: SPI interface SCK connected to GPIO11(BCM).
bme690: SPI interface MISO connected to GPIO9(BCM).
bme690: SPI interface MOSI connected to GPIO10(BCM).
bme690: SPI interface CS connected to GPIO8(BCM).
bme690: IIC interface SCL connected to GPIO3(BCM).
bme690: IIC interface SDA connected to GPIO2(BCM).
```

```shell
./bme690 -t reg --addr=0 --interface=iic

bme690: chip is Bosch BME690.
bme690: manufacturer is Bosch.
bme690: interface is IIC SPI.
bme690: driver version is 1.0.
bme690: min supply voltage is 1.7V.
bme690: max supply voltage is 3.6V.
bme690: max current is 0.85mA.
bme690: max temperature is 85.0C.
bme690: min temperature is -40.0C.
bme690: start register test.
bme690: bme690_set_interface/bme690_get_interface test.
bme690: set interface spi.
bme690: check interface ok.
bme690: set interface iic.
bme690: check interface ok.
bme690: bme690_set_addr_pin/bme690_get_addr_pin test.
bme690: set addr pin low.
bme690: check addr pin ok.
bme690: set addr pin high.
bme690: check addr pin ok.
bme690: bme690_set_temperature_oversampling/bme690_get_temperature_oversampling test.
bme690: set temperature oversampling skip.
bme690: check temperature oversampling ok.
bme690: set temperature oversampling x1.
bme690: check temperature oversampling ok.
bme690: set temperature oversampling x2.
bme690: check temperature oversampling ok.
bme690: set temperature oversampling x4.
bme690: check temperature oversampling ok.
bme690: set temperature oversampling x8.
bme690: check temperature oversampling ok.
bme690: set temperature oversampling x16.
bme690: check temperature oversampling ok.
bme690: bme690_set_pressure_oversampling/bme690_get_pressure_oversampling test.
bme690: set pressure oversampling skip.
bme690: check pressure oversampling ok.
bme690: set pressure oversampling x1.
bme690: check pressure oversampling ok.
bme690: set pressure oversampling x2.
bme690: check pressure oversampling ok.
bme690: set pressure oversampling x4.
bme690: check pressure oversampling ok.
bme690: set pressure oversampling x8.
bme690: check pressure oversampling ok.
bme690: set pressure oversampling x16.
bme690: check pressure oversampling ok.
bme690: bme690_set_humidity_oversampling/bme690_get_humidity_oversampling test.
bme690: set humidity oversampling skip.
bme690: check humidity oversampling ok.
bme690: set humidity oversampling x1.
bme690: check humidity oversampling ok.
bme690: set humidity oversampling x2.
bme690: check humidity oversampling ok.
bme690: set humidity oversampling x4.
bme690: check humidity oversampling ok.
bme690: set humidity oversampling x8.
bme690: check humidity oversampling ok.
bme690: set humidity oversampling x16.
bme690: check humidity oversampling ok.
bme690: bme690_set_mode/bme690_get_mode test.
bme690: set mode forced.
bme690: check mode ok.
bme690: set mode parallel.
bme690: check mode ok.
bme690: set mode sleep.
bme690: check mode ok.
bme690: bme690_set_filter/bme690_get_filter test.
bme690: set filter off.
bme690: check filter ok.
bme690: set filter coeff 1.
bme690: check filter ok.
bme690: set filter coeff 3.
bme690: check filter ok.
bme690: set filter coeff 7.
bme690: check filter ok.
bme690: set filter coeff 15.
bme690: check filter ok.
bme690: set filter coeff 31.
bme690: check filter ok.
bme690: set filter coeff 63.
bme690: check filter ok.
bme690: set filter coeff 127.
bme690: check filter ok.
bme690: bme690_set_spi_wire/bme690_get_spi_wire test.
bme690: set spi wire 3.
bme690: check spi wire ok.
bme690: set spi wire 4.
bme690: check spi wire ok.
bme690: bme690_set_spi_wire_3_data_interrupt/bme690_get_spi_wire_3_data_interrupt test.
bme690: enable spi wire 3 data interrupt.
bme690: check spi wire 3 data interrupt ok.
bme690: disable spi wire 3 data interrupt.
bme690: check spi wire 3 data interrupt ok.
bme690: set section 0.
bme690: bme690_get_new_data_status test.
bme690: new data status is true.
bme690: bme690_get_gas_measuring_status test.
bme690: gas measuring status is false.
bme690: bme690_get_measuring_status test.
bme690: get measuring status is false.
bme690: bme690_get_gas_measuring_index test.
bme690: gas measuring index is 0x0F.
bme690: bme690_get_gas_valid_status test.
bme690: gas valid status is false.
bme690: bme690_get_heater_stability_status test.
bme690: heater stability status is false.
bme690: set section 1.
bme690: bme690_get_new_data_status test.
bme690: new data status is false.
bme690: bme690_get_gas_measuring_status test.
bme690: gas measuring status is false.
bme690: bme690_get_measuring_status test.
bme690: get measuring status is false.
bme690: bme690_get_gas_measuring_index test.
bme690: gas measuring index is 0x00.
bme690: bme690_get_gas_valid_status test.
bme690: gas valid status is false.
bme690: bme690_get_heater_stability_status test.
bme690: heater stability status is false.
bme690: set section 2.
bme690: bme690_get_new_data_status test.
bme690: new data status is false.
bme690: bme690_get_gas_measuring_status test.
bme690: gas measuring status is false.
bme690: bme690_get_measuring_status test.
bme690: get measuring status is false.
bme690: bme690_get_gas_measuring_index test.
bme690: gas measuring index is 0x00.
bme690: bme690_get_gas_valid_status test.
bme690: gas valid status is false.
bme690: bme690_get_heater_stability_status test.
bme690: heater stability status is false.
bme690: bme690_set_heater_off/bme690_get_heater_off test.
bme690: disable heater off.
bme690: check heater off ok.
bme690: enable heater off.
bme690: check heater off ok.
bme690: bme690_set_run_gas/bme690_get_run_gas test.
bme690: enable run gas.
bme690: check run gas ok.
bme690: disable run gas.
bme690: check run gas ok.
bme690: bme690_set_heater_profile/bme690_get_heater_profile test.
bme690: set heater profile forced mode step 0, parallel mode no step.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 1, parallel mode step 0.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 2, parallel mode step 0 - 1.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 3, parallel mode step 0 - 2.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 4, parallel mode step 0 - 3.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 5, parallel mode step 0 - 4.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 6, parallel mode step 0 - 5.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 7, parallel mode step 0 - 6.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 8, parallel mode step 0 - 7.
bme690: check heater profile ok.
bme690: set heater profile forced mode step 9, parallel mode step 0 - 8.
bme690: check heater profile ok.
bme690: set heater profile forced mode no step, parallel mode step 0 - 9.
bme690: check heater profile ok.
bme690: bme690_set_gas_wait_shared/bme690_get_gas_wait_shared test.
bme690: set gas wait shared 0xEE.
bme690: check gas wait shared ok.
bme690: bme690_set_idac_heater/bme690_get_idac_heater test.
bme690: set index 0 idac heater 0xDE.
bme690: check idac heater ok.
bme690: set index 1 idac heater 0xB8.
bme690: check idac heater ok.
bme690: set index 2 idac heater 0x5F.
bme690: check idac heater ok.
bme690: set index 3 idac heater 0xF3.
bme690: check idac heater ok.
bme690: set index 4 idac heater 0x65.
bme690: check idac heater ok.
bme690: set index 5 idac heater 0x3C.
bme690: check idac heater ok.
bme690: set index 6 idac heater 0x0C.
bme690: check idac heater ok.
bme690: set index 7 idac heater 0x84.
bme690: check idac heater ok.
bme690: set index 8 idac heater 0xB8.
bme690: check idac heater ok.
bme690: set index 9 idac heater 0xD5.
bme690: check idac heater ok.
bme690: bme690_set_resistance_heater/bme690_get_resistance_heater test.
bme690: set index 0 resistance heater 0x16.
bme690: check resistance heater ok.
bme690: set index 1 resistance heater 0x09.
bme690: check resistance heater ok.
bme690: set index 2 resistance heater 0x03.
bme690: check resistance heater ok.
bme690: set index 3 resistance heater 0xED.
bme690: check resistance heater ok.
bme690: set index 4 resistance heater 0xDF.
bme690: check resistance heater ok.
bme690: set index 5 resistance heater 0xBF.
bme690: check resistance heater ok.
bme690: set index 6 resistance heater 0xFB.
bme690: check resistance heater ok.
bme690: set index 7 resistance heater 0x90.
bme690: check resistance heater ok.
bme690: set index 8 resistance heater 0xB2.
bme690: check resistance heater ok.
bme690: set index 9 resistance heater 0x1E.
bme690: check resistance heater ok.
bme690: bme690_set_gas_wait/bme690_get_gas_wait test.
bme690: set index 0 gas wait 0xBB.
bme690: check gas wait ok.
bme690: set index 1 gas wait 0xFA.
bme690: check gas wait ok.
bme690: set index 2 gas wait 0xC8.
bme690: check gas wait ok.
bme690: set index 3 gas wait 0x2C.
bme690: check gas wait ok.
bme690: set index 4 gas wait 0xF9.
bme690: check gas wait ok.
bme690: set index 5 gas wait 0xA7.
bme690: check gas wait ok.
bme690: set index 6 gas wait 0xCF.
bme690: check gas wait ok.
bme690: set index 7 gas wait 0x2B.
bme690: check gas wait ok.
bme690: set index 8 gas wait 0xCA.
bme690: check gas wait ok.
bme690: set index 9 gas wait 0xFA.
bme690: check gas wait ok.
bme690: bme690_resistance_heater_convert_to_register test.
bme690: 67.68C convert to register 0x2F.
bme690: bme690_gas_wait_convert_to_register test.
bme690: 91ms convert to register 0x56.
bme690: bme690_idac_heater_convert_to_register/bme690_idac_heater_convert_to_data test.
bme690: idac heater ma before is 7.60mA.
bme690: idac heater reg is 0x76.
bme690: idac heater ma after is 7.00mA.
bme690: bme690_gas_wait_shared_convert_to_register test.
bme690: 108ms convert to register 0x0E.
bme690: bme690_soft_reset test.
bme690: check soft reset ok.
bme690: finish register test.
```

```shell
./bme690 -t read --addr=0 --interface=iic --times=3

bme690: chip is Bosch BME690.
bme690: manufacturer is Bosch.
bme690: interface is IIC SPI.
bme690: driver version is 1.0.
bme690: min supply voltage is 1.7V.
bme690: max supply voltage is 3.6V.
bme690: max current is 0.85mA.
bme690: max temperature is 85.0C.
bme690: min temperature is -40.0C.
bme690: start read test.
bme690: temperature is 25.14C.
bme690: pressure is 102201.09pa.
bme690: humidity is 16.87%.
bme690: gas index is 0.
bme690: gas resistance is 15169.47ohms.
bme690: temperature is 25.15C.
bme690: pressure is 102200.98pa.
bme690: humidity is 16.77%.
bme690: gas index is 0.
bme690: gas resistance is 9232.54ohms.
bme690: temperature is 25.15C.
bme690: pressure is 102201.12pa.
bme690: humidity is 16.73%.
bme690: gas index is 0.
bme690: gas resistance is 7722.01ohms.
bme690: finish read test.
```

```shell
./bme690 -t parallel --addr=0 --interface=iic --times=3

bme690: chip is Bosch BME690.
bme690: manufacturer is Bosch.
bme690: interface is IIC SPI.
bme690: driver version is 1.0.
bme690: min supply voltage is 1.7V.
bme690: max supply voltage is 3.6V.
bme690: max current is 0.85mA.
bme690: max temperature is 85.0C.
bme690: min temperature is -40.0C.
bme690: start parallel test.
bme690: irq channel data.
bme690: [0] temperature raw is 0x006AF290.
bme690: [0] temperature is 26.18C.
bme690: [0] pressure raw is 0x00627AF0.
bme690: [0] pressure is 102185.94pa.
bme690: [0] humidity raw is 0x000051F8.
bme690: [0] humidity is 16.66%.
bme690: [0] adc raw is 0x03FF.
bme690: [0] adc range is 0x0D.
bme690: [0] resistance ohms is 5684.85ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x006B9EA0.
bme690: [1] temperature is 27.09C.
bme690: [1] pressure raw is 0x0062CA10.
bme690: [1] pressure is 102198.47pa.
bme690: [1] humidity raw is 0x0000517F.
bme690: [1] humidity is 16.15%.
bme690: [1] adc raw is 0x0094.
bme690: [1] adc range is 0x0B.
bme690: [1] resistance ohms is 42609.86ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x006BF870.
bme690: [2] temperature is 27.56C.
bme690: [2] pressure raw is 0x0062F460.
bme690: [2] pressure is 102202.00pa.
bme690: [2] humidity raw is 0x00005144.
bme690: [2] humidity is 15.90%.
bme690: [2] adc raw is 0x013D.
bme690: [2] adc range is 0x0D.
bme690: [2] resistance ohms is 9114.21ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x006C5370.
bme690: [3] temperature is 28.04C.
bme690: [3] pressure raw is 0x00631F60.
bme690: [3] pressure is 102205.00pa.
bme690: [3] humidity raw is 0x000050FC.
bme690: [3] humidity is 15.59%.
bme690: [3] adc raw is 0x02DD.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 13448.20ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x006CA2E0.
bme690: [4] temperature is 28.46C.
bme690: [4] pressure raw is 0x00634500.
bme690: [4] pressure is 102207.19pa.
bme690: [4] humidity raw is 0x000050C4.
bme690: [4] humidity is 15.35%.
bme690: [4] adc raw is 0x0335.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 12741.39ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x006CEAF0.
bme690: [5] temperature is 28.84C.
bme690: [5] pressure raw is 0x00636690.
bme690: [5] pressure is 102210.54pa.
bme690: [5] humidity raw is 0x0000509F.
bme690: [5] humidity is 15.19%.
bme690: [5] adc raw is 0x01AD.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 66545.36ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x006D0090.
bme690: [6] temperature is 28.95C.
bme690: [6] pressure raw is 0x00637100.
bme690: [6] pressure is 102210.54pa.
bme690: [6] humidity raw is 0x00005098.
bme690: [6] humidity is 15.16%.
bme690: [6] adc raw is 0x039F.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 23965.55ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x006D1C40.
bme690: [7] temperature is 29.10C.
bme690: [7] pressure raw is 0x00637E30.
bme690: [7] pressure is 102210.99pa.
bme690: [7] humidity raw is 0x00005084.
bme690: [7] humidity is 15.07%.
bme690: [7] adc raw is 0x0367.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 12371.93ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x006D3B90.
bme690: [8] temperature is 29.27C.
bme690: [8] pressure raw is 0x00638CF0.
bme690: [8] pressure is 102211.91pa.
bme690: [8] humidity raw is 0x00005063.
bme690: [8] humidity is 14.93%.
bme690: [8] adc raw is 0x02BE.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 13716.25ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x006D5C20.
bme690: [9] temperature is 29.44C.
bme690: [9] pressure raw is 0x00639C70.
bme690: [9] pressure is 102212.41pa.
bme690: [9] humidity raw is 0x00005043.
bme690: [9] humidity is 14.79%.
bme690: [9] adc raw is 0x0133.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 18385.52ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x006AF290.
bme690: [0] temperature is 26.18C.
bme690: [0] pressure raw is 0x00627AF0.
bme690: [0] pressure is 102185.94pa.
bme690: [0] humidity raw is 0x000051F8.
bme690: [0] humidity is 16.66%.
bme690: [0] adc raw is 0x03FF.
bme690: [0] adc range is 0x0D.
bme690: [0] resistance ohms is 5684.85ohms.
bme690: [1] temperature raw is 0x006B9EA0.
bme690: [1] temperature is 27.09C.
bme690: [1] pressure raw is 0x0062CA10.
bme690: [1] pressure is 102198.47pa.
bme690: [1] humidity raw is 0x0000517F.
bme690: [1] humidity is 16.15%.
bme690: [1] adc raw is 0x0094.
bme690: [1] adc range is 0x0B.
bme690: [1] resistance ohms is 42609.86ohms.
bme690: [2] temperature raw is 0x006BF870.
bme690: [2] temperature is 27.56C.
bme690: [2] pressure raw is 0x0062F460.
bme690: [2] pressure is 102202.00pa.
bme690: [2] humidity raw is 0x00005144.
bme690: [2] humidity is 15.90%.
bme690: [2] adc raw is 0x013D.
bme690: [2] adc range is 0x0D.
bme690: [2] resistance ohms is 9114.21ohms.
bme690: [3] temperature raw is 0x006C5370.
bme690: [3] temperature is 28.04C.
bme690: [3] pressure raw is 0x00631F60.
bme690: [3] pressure is 102205.00pa.
bme690: [3] humidity raw is 0x000050FC.
bme690: [3] humidity is 15.59%.
bme690: [3] adc raw is 0x02DD.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 13448.20ohms.
bme690: [4] temperature raw is 0x006CA2E0.
bme690: [4] temperature is 28.46C.
bme690: [4] pressure raw is 0x00634500.
bme690: [4] pressure is 102207.19pa.
bme690: [4] humidity raw is 0x000050C4.
bme690: [4] humidity is 15.35%.
bme690: [4] adc raw is 0x0335.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 12741.39ohms.
bme690: [5] temperature raw is 0x006CEAF0.
bme690: [5] temperature is 28.84C.
bme690: [5] pressure raw is 0x00636690.
bme690: [5] pressure is 102210.54pa.
bme690: [5] humidity raw is 0x0000509F.
bme690: [5] humidity is 15.19%.
bme690: [5] adc raw is 0x01AD.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 66545.36ohms.
bme690: [6] temperature raw is 0x006D0090.
bme690: [6] temperature is 28.95C.
bme690: [6] pressure raw is 0x00637100.
bme690: [6] pressure is 102210.54pa.
bme690: [6] humidity raw is 0x00005098.
bme690: [6] humidity is 15.16%.
bme690: [6] adc raw is 0x039F.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 23965.55ohms.
bme690: [7] temperature raw is 0x006D1C40.
bme690: [7] temperature is 29.10C.
bme690: [7] pressure raw is 0x00637E30.
bme690: [7] pressure is 102210.99pa.
bme690: [7] humidity raw is 0x00005084.
bme690: [7] humidity is 15.07%.
bme690: [7] adc raw is 0x0367.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 12371.93ohms.
bme690: [8] temperature raw is 0x006D3B90.
bme690: [8] temperature is 29.27C.
bme690: [8] pressure raw is 0x00638CF0.
bme690: [8] pressure is 102211.91pa.
bme690: [8] humidity raw is 0x00005063.
bme690: [8] humidity is 14.93%.
bme690: [8] adc raw is 0x02BE.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 13716.25ohms.
bme690: [9] temperature raw is 0x006D5C20.
bme690: [9] temperature is 29.44C.
bme690: [9] pressure raw is 0x00639C70.
bme690: [9] pressure is 102212.41pa.
bme690: [9] humidity raw is 0x00005043.
bme690: [9] humidity is 14.79%.
bme690: [9] adc raw is 0x0133.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 18385.52ohms.
bme690: irq channel data.
bme690: [0] temperature raw is 0x006D87B0.
bme690: [0] temperature is 29.67C.
bme690: [0] pressure raw is 0x0063B0E0.
bme690: [0] pressure is 102213.82pa.
bme690: [0] humidity raw is 0x0000501F.
bme690: [0] humidity is 14.64%.
bme690: [0] adc raw is 0x00AD.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 20785.97ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x006D68A0.
bme690: [1] temperature is 29.50C.
bme690: [1] pressure raw is 0x0063A1A0.
bme690: [1] pressure is 102214.62pa.
bme690: [1] humidity raw is 0x00005031.
bme690: [1] humidity is 14.72%.
bme690: [1] adc raw is 0x030E.
bme690: [1] adc range is 0x07.
bme690: [1] resistance ohms is 417448.03ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x006D7F60.
bme690: [2] temperature is 29.62C.
bme690: [2] pressure raw is 0x0063ACC0.
bme690: [2] pressure is 102214.16pa.
bme690: [2] humidity raw is 0x0000501E.
bme690: [2] humidity is 14.64%.
bme690: [2] adc raw is 0x00AB.
bme690: [2] adc range is 0x0C.
bme690: [2] resistance ohms is 20826.55ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x006DA750.
bme690: [3] temperature is 29.83C.
bme690: [3] pressure raw is 0x0063BFC0.
bme690: [3] pressure is 102214.71pa.
bme690: [3] humidity raw is 0x00004FF3.
bme690: [3] humidity is 14.46%.
bme690: [3] adc raw is 0x00AA.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 20846.91ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x006DCFF0.
bme690: [4] temperature is 30.05C.
bme690: [4] pressure raw is 0x0063D310.
bme690: [4] pressure is 102215.27pa.
bme690: [4] humidity raw is 0x00004FD2.
bme690: [4] humidity is 14.31%.
bme690: [4] adc raw is 0x0247.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 14852.63ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x006DCC10.
bme690: [5] temperature is 30.03C.
bme690: [5] pressure raw is 0x0063D0F0.
bme690: [5] pressure is 102215.98pa.
bme690: [5] humidity raw is 0x00004FE1.
bme690: [5] humidity is 14.38%.
bme690: [5] adc raw is 0x0063.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 89604.48ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x006DCC70.
bme690: [6] temperature is 30.03C.
bme690: [6] pressure raw is 0x0063D130.
bme690: [6] pressure is 102215.79pa.
bme690: [6] humidity raw is 0x00004FE1.
bme690: [6] humidity is 14.38%.
bme690: [6] adc raw is 0x0266.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 29077.69ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x006DD990.
bme690: [7] temperature is 30.10C.
bme690: [7] pressure raw is 0x0063D760.
bme690: [7] pressure is 102216.10pa.
bme690: [7] humidity raw is 0x00004FD1.
bme690: [7] humidity is 14.31%.
bme690: [7] adc raw is 0x02A6.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 13931.21ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x006DEF40.
bme690: [8] temperature is 30.21C.
bme690: [8] pressure raw is 0x0063E1A0.
bme690: [8] pressure is 102216.53pa.
bme690: [8] humidity raw is 0x00004FC4.
bme690: [8] humidity is 14.25%.
bme690: [8] adc raw is 0x0265.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 14548.76ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x006E09D0.
bme690: [9] temperature is 30.35C.
bme690: [9] pressure raw is 0x0063EE50.
bme690: [9] pressure is 102216.69pa.
bme690: [9] humidity raw is 0x00004FAA.
bme690: [9] humidity is 14.14%.
bme690: [9] adc raw is 0x0107.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 19110.18ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x006D87B0.
bme690: [0] temperature is 29.67C.
bme690: [0] pressure raw is 0x0063B0E0.
bme690: [0] pressure is 102213.82pa.
bme690: [0] humidity raw is 0x0000501F.
bme690: [0] humidity is 14.64%.
bme690: [0] adc raw is 0x00AD.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 20785.97ohms.
bme690: [1] temperature raw is 0x006D68A0.
bme690: [1] temperature is 29.50C.
bme690: [1] pressure raw is 0x0063A1A0.
bme690: [1] pressure is 102214.62pa.
bme690: [1] humidity raw is 0x00005031.
bme690: [1] humidity is 14.72%.
bme690: [1] adc raw is 0x030E.
bme690: [1] adc range is 0x07.
bme690: [1] resistance ohms is 417448.03ohms.
bme690: [2] temperature raw is 0x006D7F60.
bme690: [2] temperature is 29.62C.
bme690: [2] pressure raw is 0x0063ACC0.
bme690: [2] pressure is 102214.16pa.
bme690: [2] humidity raw is 0x0000501E.
bme690: [2] humidity is 14.64%.
bme690: [2] adc raw is 0x00AB.
bme690: [2] adc range is 0x0C.
bme690: [2] resistance ohms is 20826.55ohms.
bme690: [3] temperature raw is 0x006DA750.
bme690: [3] temperature is 29.83C.
bme690: [3] pressure raw is 0x0063BFC0.
bme690: [3] pressure is 102214.71pa.
bme690: [3] humidity raw is 0x00004FF3.
bme690: [3] humidity is 14.46%.
bme690: [3] adc raw is 0x00AA.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 20846.91ohms.
bme690: [4] temperature raw is 0x006DCFF0.
bme690: [4] temperature is 30.05C.
bme690: [4] pressure raw is 0x0063D310.
bme690: [4] pressure is 102215.27pa.
bme690: [4] humidity raw is 0x00004FD2.
bme690: [4] humidity is 14.31%.
bme690: [4] adc raw is 0x0247.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 14852.63ohms.
bme690: [5] temperature raw is 0x006DCC10.
bme690: [5] temperature is 30.03C.
bme690: [5] pressure raw is 0x0063D0F0.
bme690: [5] pressure is 102215.98pa.
bme690: [5] humidity raw is 0x00004FE1.
bme690: [5] humidity is 14.38%.
bme690: [5] adc raw is 0x0063.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 89604.48ohms.
bme690: [6] temperature raw is 0x006DCC70.
bme690: [6] temperature is 30.03C.
bme690: [6] pressure raw is 0x0063D130.
bme690: [6] pressure is 102215.79pa.
bme690: [6] humidity raw is 0x00004FE1.
bme690: [6] humidity is 14.38%.
bme690: [6] adc raw is 0x0266.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 29077.69ohms.
bme690: [7] temperature raw is 0x006DD990.
bme690: [7] temperature is 30.10C.
bme690: [7] pressure raw is 0x0063D760.
bme690: [7] pressure is 102216.10pa.
bme690: [7] humidity raw is 0x00004FD1.
bme690: [7] humidity is 14.31%.
bme690: [7] adc raw is 0x02A6.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 13931.21ohms.
bme690: [8] temperature raw is 0x006DEF40.
bme690: [8] temperature is 30.21C.
bme690: [8] pressure raw is 0x0063E1A0.
bme690: [8] pressure is 102216.53pa.
bme690: [8] humidity raw is 0x00004FC4.
bme690: [8] humidity is 14.25%.
bme690: [8] adc raw is 0x0265.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 14548.76ohms.
bme690: [9] temperature raw is 0x006E09D0.
bme690: [9] temperature is 30.35C.
bme690: [9] pressure raw is 0x0063EE50.
bme690: [9] pressure is 102216.69pa.
bme690: [9] humidity raw is 0x00004FAA.
bme690: [9] humidity is 14.14%.
bme690: [9] adc raw is 0x0107.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 19110.18ohms.
bme690: irq channel data.
bme690: [0] temperature raw is 0x006E21E0.
bme690: [0] temperature is 30.48C.
bme690: [0] pressure raw is 0x0063FA10.
bme690: [0] pressure is 102216.12pa.
bme690: [0] humidity raw is 0x00004F8D.
bme690: [0] humidity is 14.02%.
bme690: [0] adc raw is 0x00D0.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 20100.50ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x006DE2D0.
bme690: [1] temperature is 30.15C.
bme690: [1] pressure raw is 0x0063DBC0.
bme690: [1] pressure is 102216.28pa.
bme690: [1] humidity raw is 0x00004FBD.
bme690: [1] humidity is 14.22%.
bme690: [1] adc raw is 0x039D.
bme690: [1] adc range is 0x07.
bme690: [1] resistance ohms is 383880.03ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x006DEDE0.
bme690: [2] temperature is 30.21C.
bme690: [2] pressure raw is 0x0063E150.
bme690: [2] pressure is 102215.60pa.
bme690: [2] humidity raw is 0x00004FB2.
bme690: [2] humidity is 14.18%.
bme690: [2] adc raw is 0x00E9.
bme690: [2] adc range is 0x0C.
bme690: [2] resistance ohms is 19637.93ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x006E0C50.
bme690: [3] temperature is 30.37C.
bme690: [3] pressure raw is 0x0063F000.
bme690: [3] pressure is 102215.38pa.
bme690: [3] humidity raw is 0x00004F99.
bme690: [3] humidity is 14.07%.
bme690: [3] adc raw is 0x00CC.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 20176.54ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x006E2D30.
bme690: [4] temperature is 30.54C.
bme690: [4] pressure raw is 0x0063FFC0.
bme690: [4] pressure is 102215.42pa.
bme690: [4] humidity raw is 0x00004F89.
bme690: [4] humidity is 14.00%.
bme690: [4] adc raw is 0x0240.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 14925.37ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x006E1E70.
bme690: [5] temperature is 30.46C.
bme690: [5] pressure raw is 0x0063F830.
bme690: [5] pressure is 102216.73pa.
bme690: [5] humidity raw is 0x00004F80.
bme690: [5] humidity is 13.96%.
bme690: [5] adc raw is 0x0089.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 86166.27ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x006E1AF0.
bme690: [6] temperature is 30.44C.
bme690: [6] pressure raw is 0x0063F670.
bme690: [6] pressure is 102216.92pa.
bme690: [6] humidity raw is 0x00004F80.
bme690: [6] humidity is 13.97%.
bme690: [6] adc raw is 0x0281.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 28552.31ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x006E2440.
bme690: [7] temperature is 30.49C.
bme690: [7] pressure raw is 0x0063FB00.
bme690: [7] pressure is 102216.66pa.
bme690: [7] humidity raw is 0x00004F78.
bme690: [7] humidity is 13.93%.
bme690: [7] adc raw is 0x02CC.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 13593.88ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x006E3680.
bme690: [8] temperature is 30.59C.
bme690: [8] pressure raw is 0x006403D0.
bme690: [8] pressure is 102216.49pa.
bme690: [8] humidity raw is 0x00004F61.
bme690: [8] humidity is 13.83%.
bme690: [8] adc raw is 0x0298.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 14059.75ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x006E4E10.
bme690: [9] temperature is 30.71C.
bme690: [9] pressure raw is 0x00640F30.
bme690: [9] pressure is 102216.26pa.
bme690: [9] humidity raw is 0x00004F4B.
bme690: [9] humidity is 13.74%.
bme690: [9] adc raw is 0x0119.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 18806.94ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x006E21E0.
bme690: [0] temperature is 30.48C.
bme690: [0] pressure raw is 0x0063FA10.
bme690: [0] pressure is 102216.12pa.
bme690: [0] humidity raw is 0x00004F8D.
bme690: [0] humidity is 14.02%.
bme690: [0] adc raw is 0x00D0.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 20100.50ohms.
bme690: [1] temperature raw is 0x006DE2D0.
bme690: [1] temperature is 30.15C.
bme690: [1] pressure raw is 0x0063DBC0.
bme690: [1] pressure is 102216.28pa.
bme690: [1] humidity raw is 0x00004FBD.
bme690: [1] humidity is 14.22%.
bme690: [1] adc raw is 0x039D.
bme690: [1] adc range is 0x07.
bme690: [1] resistance ohms is 383880.03ohms.
bme690: [2] temperature raw is 0x006DEDE0.
bme690: [2] temperature is 30.21C.
bme690: [2] pressure raw is 0x0063E150.
bme690: [2] pressure is 102215.60pa.
bme690: [2] humidity raw is 0x00004FB2.
bme690: [2] humidity is 14.18%.
bme690: [2] adc raw is 0x00E9.
bme690: [2] adc range is 0x0C.
bme690: [2] resistance ohms is 19637.93ohms.
bme690: [3] temperature raw is 0x006E0C50.
bme690: [3] temperature is 30.37C.
bme690: [3] pressure raw is 0x0063F000.
bme690: [3] pressure is 102215.38pa.
bme690: [3] humidity raw is 0x00004F99.
bme690: [3] humidity is 14.07%.
bme690: [3] adc raw is 0x00CC.
bme690: [3] adc range is 0x0C.
bme690: [3] resistance ohms is 20176.54ohms.
bme690: [4] temperature raw is 0x006E2D30.
bme690: [4] temperature is 30.54C.
bme690: [4] pressure raw is 0x0063FFC0.
bme690: [4] pressure is 102215.42pa.
bme690: [4] humidity raw is 0x00004F89.
bme690: [4] humidity is 14.00%.
bme690: [4] adc raw is 0x0240.
bme690: [4] adc range is 0x0C.
bme690: [4] resistance ohms is 14925.37ohms.
bme690: [5] temperature raw is 0x006E1E70.
bme690: [5] temperature is 30.46C.
bme690: [5] pressure raw is 0x0063F830.
bme690: [5] pressure is 102216.73pa.
bme690: [5] humidity raw is 0x00004F80.
bme690: [5] humidity is 13.96%.
bme690: [5] adc raw is 0x0089.
bme690: [5] adc range is 0x0A.
bme690: [5] resistance ohms is 86166.27ohms.
bme690: [6] temperature raw is 0x006E1AF0.
bme690: [6] temperature is 30.44C.
bme690: [6] pressure raw is 0x0063F670.
bme690: [6] pressure is 102216.92pa.
bme690: [6] humidity raw is 0x00004F80.
bme690: [6] humidity is 13.97%.
bme690: [6] adc raw is 0x0281.
bme690: [6] adc range is 0x0B.
bme690: [6] resistance ohms is 28552.31ohms.
bme690: [7] temperature raw is 0x006E2440.
bme690: [7] temperature is 30.49C.
bme690: [7] pressure raw is 0x0063FB00.
bme690: [7] pressure is 102216.66pa.
bme690: [7] humidity raw is 0x00004F78.
bme690: [7] humidity is 13.93%.
bme690: [7] adc raw is 0x02CC.
bme690: [7] adc range is 0x0C.
bme690: [7] resistance ohms is 13593.88ohms.
bme690: [8] temperature raw is 0x006E3680.
bme690: [8] temperature is 30.59C.
bme690: [8] pressure raw is 0x006403D0.
bme690: [8] pressure is 102216.49pa.
bme690: [8] humidity raw is 0x00004F61.
bme690: [8] humidity is 13.83%.
bme690: [8] adc raw is 0x0298.
bme690: [8] adc range is 0x0C.
bme690: [8] resistance ohms is 14059.75ohms.
bme690: [9] temperature raw is 0x006E4E10.
bme690: [9] temperature is 30.71C.
bme690: [9] pressure raw is 0x00640F30.
bme690: [9] pressure is 102216.26pa.
bme690: [9] humidity raw is 0x00004F4B.
bme690: [9] humidity is 13.74%.
bme690: [9] adc raw is 0x0119.
bme690: [9] adc range is 0x0C.
bme690: [9] resistance ohms is 18806.94ohms.
bme690: finish parallel test.
```

```shell
./bme690 -e read --addr=0 --interface=iic --index=0 --times=3

bme690: 1/3.
bme690: temperature is 26.20C.
bme690: pressure is 102401.77Pa.
bme690: humidity is 20.71%.
bme690: 2/3.
bme690: temperature is 26.20C.
bme690: pressure is 102401.55Pa.
bme690: humidity is 20.85%.
bme690: 3/3.
bme690: temperature is 26.20C.
bme690: pressure is 102401.52Pa.
bme690: humidity is 20.97%.
```

```shell
./bme690 -e gas --addr=0 --interface=iic --index=0 --degree=200.0 --wait=150 --times=3

bme690: 1/3.
bme690: temperature is 25.93C.
bme690: pressure is 102406.48Pa.
bme690: humidity is 22.01%.
bme690: gas index is 0.
bme690: degree celsius is 200.0C.
bme690: gas wait is 150 ms.
bme690: gas resistance is 154263.33ohms.
bme690: 2/3.
bme690: temperature is 25.94C.
bme690: pressure is 102406.54Pa.
bme690: humidity is 22.04%.
bme690: gas index is 0.
bme690: degree celsius is 200.0C.
bme690: gas wait is 150 ms.
bme690: gas resistance is 96622.01ohms.
bme690: 3/3.
bme690: temperature is 25.95C.
bme690: pressure is 102406.45Pa.
bme690: humidity is 22.02%.
bme690: gas index is 0.
bme690: degree celsius is 200.0C.
bme690: gas wait is 150 ms.
bme690: gas resistance is 79950.03ohms.
```

```shell
./bme690 -e parallel --addr=0 --interface=iic --times=3

bme690: parallel sample.
bme690: irq channel data.
bme690: [0] temperature raw is 0x0007B646.
bme690: [0] temperature is 27.54C.
bme690: [0] pressure raw is 0x0004AA3F.
bme690: [0] pressure is 102160.91pa.
bme690: [0] humidity raw is 0x00003C4B.
bme690: [0] humidity is 23.72%.
bme690: [0] adc raw is 0x01C4.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 16343.21ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x0007C412.
bme690: [1] temperature is 28.67C.
bme690: [1] pressure raw is 0x0004AE68.
bme690: [1] pressure is 102167.62pa.
bme690: [1] humidity raw is 0x00003C20.
bme690: [1] humidity is 23.57%.
bme690: [1] adc raw is 0x0093.
bme690: [1] adc range is 0x08.
bme690: [1] resistance ohms is 341219.59ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x0007CA80.
bme690: [2] temperature is 29.19C.
bme690: [2] pressure raw is 0x0004B05D.
bme690: [2] pressure is 102169.77pa.
bme690: [2] humidity raw is 0x00003BFC.
bme690: [2] humidity is 23.42%.
bme690: [2] adc raw is 0x02C0.
bme690: [2] adc range is 0x0B.
bme690: [2] resistance ohms is 27397.26ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x0007D23E.
bme690: [3] temperature is 29.83C.
bme690: [3] pressure raw is 0x0004B2B9.
bme690: [3] pressure is 102172.08pa.
bme690: [3] humidity raw is 0x00003BBA.
bme690: [3] humidity is 23.11%.
bme690: [3] adc raw is 0x009A.
bme690: [3] adc range is 0x0B.
bme690: [3] resistance ohms is 42356.05ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x0007D813.
bme690: [4] temperature is 30.31C.
bme690: [4] pressure raw is 0x0004B47E.
bme690: [4] pressure is 102174.03pa.
bme690: [4] humidity raw is 0x00003B71.
bme690: [4] humidity is 22.75%.
bme690: [4] adc raw is 0x02AD.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 55471.29ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x0007DCC5.
bme690: [5] temperature is 30.69C.
bme690: [5] pressure raw is 0x0004B5E8.
bme690: [5] pressure is 102175.98pa.
bme690: [5] humidity raw is 0x00003ADB.
bme690: [5] humidity is 21.97%.
bme690: [5] adc raw is 0x0044.
bme690: [5] adc range is 0x07.
bme690: [5] resistance ohms is 740955.12ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x0007DDE4.
bme690: [6] temperature is 30.79C.
bme690: [6] pressure raw is 0x0004B63F.
bme690: [6] pressure is 102176.35pa.
bme690: [6] humidity raw is 0x00003AA7.
bme690: [6] humidity is 21.70%.
bme690: [6] adc raw is 0x036B.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 197492.77ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x0007DF7B.
bme690: [7] temperature is 30.92C.
bme690: [7] pressure raw is 0x0004B6BD.
bme690: [7] pressure is 102176.41pa.
bme690: [7] humidity raw is 0x00003A7B.
bme690: [7] humidity is 21.47%.
bme690: [7] adc raw is 0x00EE.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 78191.81ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x0007E174.
bme690: [8] temperature is 31.08C.
bme690: [8] pressure raw is 0x0004B758.
bme690: [8] pressure is 102176.71pa.
bme690: [8] humidity raw is 0x00003A50.
bme690: [8] humidity is 21.26%.
bme690: [8] adc raw is 0x030E.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 52181.00ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x0007E399.
bme690: [9] temperature is 31.25C.
bme690: [9] pressure raw is 0x0004B7FF.
bme690: [9] pressure is 102177.27pa.
bme690: [9] humidity raw is 0x00003A26.
bme690: [9] humidity is 21.04%.
bme690: [9] adc raw is 0x02CE.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 54306.32ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x0007B646.
bme690: [0] temperature is 27.54C.
bme690: [0] pressure raw is 0x0004AA3F.
bme690: [0] pressure is 102160.91pa.
bme690: [0] humidity raw is 0x00003C4B.
bme690: [0] humidity is 23.72%.
bme690: [0] adc raw is 0x01C4.
bme690: [0] adc range is 0x0C.
bme690: [0] resistance ohms is 16343.21ohms.
bme690: [1] temperature raw is 0x0007C412.
bme690: [1] temperature is 28.67C.
bme690: [1] pressure raw is 0x0004AE68.
bme690: [1] pressure is 102167.62pa.
bme690: [1] humidity raw is 0x00003C20.
bme690: [1] humidity is 23.57%.
bme690: [1] adc raw is 0x0093.
bme690: [1] adc range is 0x08.
bme690: [1] resistance ohms is 341219.59ohms.
bme690: [2] temperature raw is 0x0007CA80.
bme690: [2] temperature is 29.19C.
bme690: [2] pressure raw is 0x0004B05D.
bme690: [2] pressure is 102169.77pa.
bme690: [2] humidity raw is 0x00003BFC.
bme690: [2] humidity is 23.42%.
bme690: [2] adc raw is 0x02C0.
bme690: [2] adc range is 0x0B.
bme690: [2] resistance ohms is 27397.26ohms.
bme690: [3] temperature raw is 0x0007D23E.
bme690: [3] temperature is 29.83C.
bme690: [3] pressure raw is 0x0004B2B9.
bme690: [3] pressure is 102172.08pa.
bme690: [3] humidity raw is 0x00003BBA.
bme690: [3] humidity is 23.11%.
bme690: [3] adc raw is 0x009A.
bme690: [3] adc range is 0x0B.
bme690: [3] resistance ohms is 42356.05ohms.
bme690: [4] temperature raw is 0x0007D813.
bme690: [4] temperature is 30.31C.
bme690: [4] pressure raw is 0x0004B47E.
bme690: [4] pressure is 102174.03pa.
bme690: [4] humidity raw is 0x00003B71.
bme690: [4] humidity is 22.75%.
bme690: [4] adc raw is 0x02AD.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 55471.29ohms.
bme690: [5] temperature raw is 0x0007DCC5.
bme690: [5] temperature is 30.69C.
bme690: [5] pressure raw is 0x0004B5E8.
bme690: [5] pressure is 102175.98pa.
bme690: [5] humidity raw is 0x00003ADB.
bme690: [5] humidity is 21.97%.
bme690: [5] adc raw is 0x0044.
bme690: [5] adc range is 0x07.
bme690: [5] resistance ohms is 740955.12ohms.
bme690: [6] temperature raw is 0x0007DDE4.
bme690: [6] temperature is 30.79C.
bme690: [6] pressure raw is 0x0004B63F.
bme690: [6] pressure is 102176.35pa.
bme690: [6] humidity raw is 0x00003AA7.
bme690: [6] humidity is 21.70%.
bme690: [6] adc raw is 0x036B.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 197492.77ohms.
bme690: [7] temperature raw is 0x0007DF7B.
bme690: [7] temperature is 30.92C.
bme690: [7] pressure raw is 0x0004B6BD.
bme690: [7] pressure is 102176.41pa.
bme690: [7] humidity raw is 0x00003A7B.
bme690: [7] humidity is 21.47%.
bme690: [7] adc raw is 0x00EE.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 78191.81ohms.
bme690: [8] temperature raw is 0x0007E174.
bme690: [8] temperature is 31.08C.
bme690: [8] pressure raw is 0x0004B758.
bme690: [8] pressure is 102176.71pa.
bme690: [8] humidity raw is 0x00003A50.
bme690: [8] humidity is 21.26%.
bme690: [8] adc raw is 0x030E.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 52181.00ohms.
bme690: [9] temperature raw is 0x0007E399.
bme690: [9] temperature is 31.25C.
bme690: [9] pressure raw is 0x0004B7FF.
bme690: [9] pressure is 102177.27pa.
bme690: [9] humidity raw is 0x00003A26.
bme690: [9] humidity is 21.04%.
bme690: [9] adc raw is 0x02CE.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 54306.32ohms.
bme690: irq channel data.
bme690: [0] temperature raw is 0x0007E674.
bme690: [0] temperature is 31.49C.
bme690: [0] pressure raw is 0x0004B8E1.
bme690: [0] pressure is 102177.35pa.
bme690: [0] humidity raw is 0x000039FA.
bme690: [0] humidity is 20.83%.
bme690: [0] adc raw is 0x0264.
bme690: [0] adc range is 0x0A.
bme690: [0] resistance ohms is 58234.76ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x0007E408.
bme690: [1] temperature is 31.29C.
bme690: [1] pressure raw is 0x0004B818.
bme690: [1] pressure is 102178.88pa.
bme690: [1] humidity raw is 0x000039A6.
bme690: [1] humidity is 20.37%.
bme690: [1] adc raw is 0x01F4.
bme690: [1] adc range is 0x05.
bme690: [1] resistance ohms is 2017734.00ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x0007E4FC.
bme690: [2] temperature is 31.37C.
bme690: [2] pressure raw is 0x0004B867.
bme690: [2] pressure is 102178.30pa.
bme690: [2] humidity raw is 0x00003998.
bme690: [2] humidity is 20.30%.
bme690: [2] adc raw is 0x02CD.
bme690: [2] adc range is 0x0A.
bme690: [2] resistance ohms is 54340.90ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x0007E7A5.
bme690: [3] temperature is 31.59C.
bme690: [3] pressure raw is 0x0004B93A.
bme690: [3] pressure is 102178.30pa.
bme690: [3] humidity raw is 0x00003974.
bme690: [3] humidity is 20.12%.
bme690: [3] adc raw is 0x027E.
bme690: [3] adc range is 0x0A.
bme690: [3] resistance ohms is 57219.49ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x0007EA75.
bme690: [4] temperature is 31.82C.
bme690: [4] pressure raw is 0x0004BA14.
bme690: [4] pressure is 102179.15pa.
bme690: [4] humidity raw is 0x00003952.
bme690: [4] humidity is 19.96%.
bme690: [4] adc raw is 0x0208.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 62135.92ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x0007E9E7.
bme690: [5] temperature is 31.77C.
bme690: [5] pressure raw is 0x0004B9E3.
bme690: [5] pressure is 102180.03pa.
bme690: [5] humidity raw is 0x00003911.
bme690: [5] humidity is 19.61%.
bme690: [5] adc raw is 0x02C8.
bme690: [5] adc range is 0x06.
bme690: [5] resistance ohms is 872231.69ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x0007E996.
bme690: [6] temperature is 31.74C.
bme690: [6] pressure raw is 0x0004B9CD.
bme690: [6] pressure is 102179.48pa.
bme690: [6] humidity raw is 0x000038FE.
bme690: [6] humidity is 19.51%.
bme690: [6] adc raw is 0x029F.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 223923.03ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x0007EA43.
bme690: [7] temperature is 31.80C.
bme690: [7] pressure raw is 0x0004BA05.
bme690: [7] pressure is 102179.06pa.
bme690: [7] humidity raw is 0x000038EC.
bme690: [7] humidity is 19.42%.
bme690: [7] adc raw is 0x0081.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 86868.00ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x0007EBA9.
bme690: [8] temperature is 31.91C.
bme690: [8] pressure raw is 0x0004BA75.
bme690: [8] pressure is 102178.88pa.
bme690: [8] humidity raw is 0x000038DC.
bme690: [8] humidity is 19.34%.
bme690: [8] adc raw is 0x029E.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 56017.50ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x0007ED77.
bme690: [9] temperature is 32.06C.
bme690: [9] pressure raw is 0x0004BB00.
bme690: [9] pressure is 102179.54pa.
bme690: [9] humidity raw is 0x000038C8.
bme690: [9] humidity is 19.25%.
bme690: [9] adc raw is 0x029F.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 55980.76ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x0007E674.
bme690: [0] temperature is 31.49C.
bme690: [0] pressure raw is 0x0004B8E1.
bme690: [0] pressure is 102177.35pa.
bme690: [0] humidity raw is 0x000039FA.
bme690: [0] humidity is 20.83%.
bme690: [0] adc raw is 0x0264.
bme690: [0] adc range is 0x0A.
bme690: [0] resistance ohms is 58234.76ohms.
bme690: [1] temperature raw is 0x0007E408.
bme690: [1] temperature is 31.29C.
bme690: [1] pressure raw is 0x0004B818.
bme690: [1] pressure is 102178.88pa.
bme690: [1] humidity raw is 0x000039A6.
bme690: [1] humidity is 20.37%.
bme690: [1] adc raw is 0x01F4.
bme690: [1] adc range is 0x05.
bme690: [1] resistance ohms is 2017734.00ohms.
bme690: [2] temperature raw is 0x0007E4FC.
bme690: [2] temperature is 31.37C.
bme690: [2] pressure raw is 0x0004B867.
bme690: [2] pressure is 102178.30pa.
bme690: [2] humidity raw is 0x00003998.
bme690: [2] humidity is 20.30%.
bme690: [2] adc raw is 0x02CD.
bme690: [2] adc range is 0x0A.
bme690: [2] resistance ohms is 54340.90ohms.
bme690: [3] temperature raw is 0x0007E7A5.
bme690: [3] temperature is 31.59C.
bme690: [3] pressure raw is 0x0004B93A.
bme690: [3] pressure is 102178.30pa.
bme690: [3] humidity raw is 0x00003974.
bme690: [3] humidity is 20.12%.
bme690: [3] adc raw is 0x027E.
bme690: [3] adc range is 0x0A.
bme690: [3] resistance ohms is 57219.49ohms.
bme690: [4] temperature raw is 0x0007EA75.
bme690: [4] temperature is 31.82C.
bme690: [4] pressure raw is 0x0004BA14.
bme690: [4] pressure is 102179.15pa.
bme690: [4] humidity raw is 0x00003952.
bme690: [4] humidity is 19.96%.
bme690: [4] adc raw is 0x0208.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 62135.92ohms.
bme690: [5] temperature raw is 0x0007E9E7.
bme690: [5] temperature is 31.77C.
bme690: [5] pressure raw is 0x0004B9E3.
bme690: [5] pressure is 102180.03pa.
bme690: [5] humidity raw is 0x00003911.
bme690: [5] humidity is 19.61%.
bme690: [5] adc raw is 0x02C8.
bme690: [5] adc range is 0x06.
bme690: [5] resistance ohms is 872231.69ohms.
bme690: [6] temperature raw is 0x0007E996.
bme690: [6] temperature is 31.74C.
bme690: [6] pressure raw is 0x0004B9CD.
bme690: [6] pressure is 102179.48pa.
bme690: [6] humidity raw is 0x000038FE.
bme690: [6] humidity is 19.51%.
bme690: [6] adc raw is 0x029F.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 223923.03ohms.
bme690: [7] temperature raw is 0x0007EA43.
bme690: [7] temperature is 31.80C.
bme690: [7] pressure raw is 0x0004BA05.
bme690: [7] pressure is 102179.06pa.
bme690: [7] humidity raw is 0x000038EC.
bme690: [7] humidity is 19.42%.
bme690: [7] adc raw is 0x0081.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 86868.00ohms.
bme690: [8] temperature raw is 0x0007EBA9.
bme690: [8] temperature is 31.91C.
bme690: [8] pressure raw is 0x0004BA75.
bme690: [8] pressure is 102178.88pa.
bme690: [8] humidity raw is 0x000038DC.
bme690: [8] humidity is 19.34%.
bme690: [8] adc raw is 0x029E.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 56017.50ohms.
bme690: [9] temperature raw is 0x0007ED77.
bme690: [9] temperature is 32.06C.
bme690: [9] pressure raw is 0x0004BB00.
bme690: [9] pressure is 102179.54pa.
bme690: [9] humidity raw is 0x000038C8.
bme690: [9] humidity is 19.25%.
bme690: [9] adc raw is 0x029F.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 55980.76ohms.
bme690: irq channel data.
bme690: [0] temperature raw is 0x0007EF23.
bme690: [0] temperature is 32.20C.
bme690: [0] pressure raw is 0x0004BB81.
bme690: [0] pressure is 102180.14pa.
bme690: [0] humidity raw is 0x000038B2.
bme690: [0] humidity is 19.14%.
bme690: [0] adc raw is 0x0258.
bme690: [0] adc range is 0x0A.
bme690: [0] resistance ohms is 58715.60ohms.
bme690: irq channel data.
bme690: [1] temperature raw is 0x0007EAA9.
bme690: [1] temperature is 31.83C.
bme690: [1] pressure raw is 0x0004BA1B.
bme690: [1] pressure is 102180.70pa.
bme690: [1] humidity raw is 0x00003891.
bme690: [1] humidity is 18.95%.
bme690: [1] adc raw is 0x0218.
bme690: [1] adc range is 0x05.
bme690: [1] resistance ohms is 1965451.00ohms.
bme690: irq channel data.
bme690: [2] temperature raw is 0x0007EADB.
bme690: [2] temperature is 31.85C.
bme690: [2] pressure raw is 0x0004BA30.
bme690: [2] pressure is 102179.77pa.
bme690: [2] humidity raw is 0x0000389B.
bme690: [2] humidity is 19.00%.
bme690: [2] adc raw is 0x02E4.
bme690: [2] adc range is 0x0A.
bme690: [2] resistance ohms is 53556.48ohms.
bme690: irq channel data.
bme690: [3] temperature raw is 0x0007ECED.
bme690: [3] temperature is 32.02C.
bme690: [3] pressure raw is 0x0004BAD2.
bme690: [3] pressure is 102180.11pa.
bme690: [3] humidity raw is 0x0000389A.
bme690: [3] humidity is 19.00%.
bme690: [3] adc raw is 0x02A3.
bme690: [3] adc range is 0x0A.
bme690: [3] resistance ohms is 55834.24ohms.
bme690: irq channel data.
bme690: [4] temperature raw is 0x0007EF45.
bme690: [4] temperature is 32.21C.
bme690: [4] pressure raw is 0x0004BB88.
bme690: [4] pressure is 102180.74pa.
bme690: [4] humidity raw is 0x00003896.
bme690: [4] humidity is 18.99%.
bme690: [4] adc raw is 0x0216.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 61508.89ohms.
bme690: irq channel data.
bme690: [5] temperature raw is 0x0007EE06.
bme690: [5] temperature is 32.11C.
bme690: [5] pressure raw is 0x0004BB25.
bme690: [5] pressure is 102180.79pa.
bme690: [5] humidity raw is 0x00003897.
bme690: [5] humidity is 18.99%.
bme690: [5] adc raw is 0x032C.
bme690: [5] adc range is 0x06.
bme690: [5] resistance ohms is 819855.88ohms.
bme690: irq channel data.
bme690: [6] temperature raw is 0x0007ED73.
bme690: [6] temperature is 32.06C.
bme690: [6] pressure raw is 0x0004BAFA.
bme690: [6] pressure is 102180.38pa.
bme690: [6] humidity raw is 0x000038A0.
bme690: [6] humidity is 19.04%.
bme690: [6] adc raw is 0x02D8.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 215851.61ohms.
bme690: irq channel data.
bme690: [7] temperature raw is 0x0007EDEA.
bme690: [7] temperature is 32.10C.
bme690: [7] pressure raw is 0x0004BB20.
bme690: [7] pressure is 102180.17pa.
bme690: [7] humidity raw is 0x000038A3.
bme690: [7] humidity is 19.06%.
bme690: [7] adc raw is 0x0096.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 85049.84ohms.
bme690: irq channel data.
bme690: [8] temperature raw is 0x0007EF26.
bme690: [8] temperature is 32.20C.
bme690: [8] pressure raw is 0x0004BB7E.
bme690: [8] pressure is 102180.80pa.
bme690: [8] humidity raw is 0x0000389E.
bme690: [8] humidity is 19.04%.
bme690: [8] adc raw is 0x02B2.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 55291.58ohms.
bme690: irq channel data.
bme690: [9] temperature raw is 0x0007F0CE.
bme690: [9] temperature is 32.34C.
bme690: [9] pressure raw is 0x0004BBFE.
bme690: [9] pressure is 102181.34pa.
bme690: [9] humidity raw is 0x00003890.
bme690: [9] humidity is 18.97%.
bme690: [9] adc raw is 0x029E.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 56017.50ohms.
bme690: irq all data.
bme690: [0] temperature raw is 0x0007EF23.
bme690: [0] temperature is 32.20C.
bme690: [0] pressure raw is 0x0004BB81.
bme690: [0] pressure is 102180.14pa.
bme690: [0] humidity raw is 0x000038B2.
bme690: [0] humidity is 19.14%.
bme690: [0] adc raw is 0x0258.
bme690: [0] adc range is 0x0A.
bme690: [0] resistance ohms is 58715.60ohms.
bme690: [1] temperature raw is 0x0007EAA9.
bme690: [1] temperature is 31.83C.
bme690: [1] pressure raw is 0x0004BA1B.
bme690: [1] pressure is 102180.70pa.
bme690: [1] humidity raw is 0x00003891.
bme690: [1] humidity is 18.95%.
bme690: [1] adc raw is 0x0218.
bme690: [1] adc range is 0x05.
bme690: [1] resistance ohms is 1965451.00ohms.
bme690: [2] temperature raw is 0x0007EADB.
bme690: [2] temperature is 31.85C.
bme690: [2] pressure raw is 0x0004BA30.
bme690: [2] pressure is 102179.77pa.
bme690: [2] humidity raw is 0x0000389B.
bme690: [2] humidity is 19.00%.
bme690: [2] adc raw is 0x02E4.
bme690: [2] adc range is 0x0A.
bme690: [2] resistance ohms is 53556.48ohms.
bme690: [3] temperature raw is 0x0007ECED.
bme690: [3] temperature is 32.02C.
bme690: [3] pressure raw is 0x0004BAD2.
bme690: [3] pressure is 102180.11pa.
bme690: [3] humidity raw is 0x0000389A.
bme690: [3] humidity is 19.00%.
bme690: [3] adc raw is 0x02A3.
bme690: [3] adc range is 0x0A.
bme690: [3] resistance ohms is 55834.24ohms.
bme690: [4] temperature raw is 0x0007EF45.
bme690: [4] temperature is 32.21C.
bme690: [4] pressure raw is 0x0004BB88.
bme690: [4] pressure is 102180.74pa.
bme690: [4] humidity raw is 0x00003896.
bme690: [4] humidity is 18.99%.
bme690: [4] adc raw is 0x0216.
bme690: [4] adc range is 0x0A.
bme690: [4] resistance ohms is 61508.89ohms.
bme690: [5] temperature raw is 0x0007EE06.
bme690: [5] temperature is 32.11C.
bme690: [5] pressure raw is 0x0004BB25.
bme690: [5] pressure is 102180.79pa.
bme690: [5] humidity raw is 0x00003897.
bme690: [5] humidity is 18.99%.
bme690: [5] adc raw is 0x032C.
bme690: [5] adc range is 0x06.
bme690: [5] resistance ohms is 819855.88ohms.
bme690: [6] temperature raw is 0x0007ED73.
bme690: [6] temperature is 32.06C.
bme690: [6] pressure raw is 0x0004BAFA.
bme690: [6] pressure is 102180.38pa.
bme690: [6] humidity raw is 0x000038A0.
bme690: [6] humidity is 19.04%.
bme690: [6] adc raw is 0x02D8.
bme690: [6] adc range is 0x08.
bme690: [6] resistance ohms is 215851.61ohms.
bme690: [7] temperature raw is 0x0007EDEA.
bme690: [7] temperature is 32.10C.
bme690: [7] pressure raw is 0x0004BB20.
bme690: [7] pressure is 102180.17pa.
bme690: [7] humidity raw is 0x000038A3.
bme690: [7] humidity is 19.06%.
bme690: [7] adc raw is 0x0096.
bme690: [7] adc range is 0x0A.
bme690: [7] resistance ohms is 85049.84ohms.
bme690: [8] temperature raw is 0x0007EF26.
bme690: [8] temperature is 32.20C.
bme690: [8] pressure raw is 0x0004BB7E.
bme690: [8] pressure is 102180.80pa.
bme690: [8] humidity raw is 0x0000389E.
bme690: [8] humidity is 19.04%.
bme690: [8] adc raw is 0x02B2.
bme690: [8] adc range is 0x0A.
bme690: [8] resistance ohms is 55291.58ohms.
bme690: [9] temperature raw is 0x0007F0CE.
bme690: [9] temperature is 32.34C.
bme690: [9] pressure raw is 0x0004BBFE.
bme690: [9] pressure is 102181.34pa.
bme690: [9] humidity raw is 0x00003890.
bme690: [9] humidity is 18.97%.
bme690: [9] adc raw is 0x029E.
bme690: [9] adc range is 0x0A.
bme690: [9] resistance ohms is 56017.50ohms.
bme690: parallel done.
```

```shell
./bme690 -h

Usage:
  bme690 (-i | --information)
  bme690 (-h | --help)
  bme690 (-p | --port)
  bme690 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
  bme690 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--times=<num>]
  bme690 (-t parallel | --test=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme690 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme690 (-e gas | --example=gas) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>]
         [--degree=<degree>] [--wait=<ms>] [--times=<num>]
  bme690 (-e parallel | --example=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]

Options:
      --addr=<0 | 1>                 Set the chip iic address.([default: 0])
      --degree=<degree>              Set the heater expected temperature in degree celsius.([default: 200.0])
  -e <read | gas | parallel>, --example=<read | gas | parallel>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --index=<index>                Set the heater index and it range is 0 - 9.([default: 0])
      --interface=<iic | spi>        Set the chip interface.([default: iic])
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read | parallel>, --test=<reg | read | parallel>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
      --wait=<ms>                    Set the heater wait time in ms.([default: 150])
```

