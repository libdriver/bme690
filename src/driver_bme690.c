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
 * @file      driver_bme690.c
 * @brief     driver bme690 source file
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

#include "driver_bme690.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Bosch BME690"        /**< chip name */
#define MANUFACTURER_NAME         "Bosch"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.71f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                  /**< chip max supply voltage */
#define MAX_CURRENT               0.849f                /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            1000                  /**< driver version */

/**
 * @brief chip register definition
 */
#define BME690_REG_NVM_PAR_T1_L        0xE9        /**< NVM PAR T1 low register */
#define BME690_REG_NVM_PAR_T1_H        0xEA        /**< NVM PAR T1 high register */
#define BME690_REG_NVM_PAR_T2_L        0x8A        /**< NVM PAR T2 low register */
#define BME690_REG_NVM_PAR_T2_H        0x8B        /**< NVM PAR T2 high register */
#define BME690_REG_NVM_PAR_T3          0x8C        /**< NVM PAR T3 register */
#define BME690_REG_NVM_PAR_P1_L        0x94        /**< NVM PAR P1 low register */
#define BME690_REG_NVM_PAR_P1_H        0x95        /**< NVM PAR P1 high register */
#define BME690_REG_NVM_PAR_P2_L        0x96        /**< NVM PAR P2 low register */
#define BME690_REG_NVM_PAR_P2_H        0x97        /**< NVM PAR P2 high register */
#define BME690_REG_NVM_PAR_P3          0x98        /**< NVM PAR P3 register */
#define BME690_REG_NVM_PAR_P4          0x99        /**< NVM PAR P4 register */
#define BME690_REG_NVM_PAR_P5_L        0x8E        /**< NVM PAR P5 low register */
#define BME690_REG_NVM_PAR_P5_H        0x8F        /**< NVM PAR P5 high register */
#define BME690_REG_NVM_PAR_P6_L        0x90        /**< NVM PAR P6 low register */
#define BME690_REG_NVM_PAR_P6_H        0x91        /**< NVM PAR P6 high register */
#define BME690_REG_NVM_PAR_P7          0x92        /**< NVM PAR P7 register */
#define BME690_REG_NVM_PAR_P8          0x93        /**< NVM PAR P8 register */
#define BME690_REG_NVM_PAR_P9_L        0x9C        /**< NVM PAR P9 low register */
#define BME690_REG_NVM_PAR_P9_H        0x9D        /**< NVM PAR P9 high register */
#define BME690_REG_NVM_PAR_P10         0x9E        /**< NVM PAR P10 register */
#define BME690_REG_NVM_PAR_P11         0x9F        /**< NVM PAR P11 register */
#define BME690_REG_NVM_PAR_H1_L        0xE2        /**< NVM PAR H1 low register */
#define BME690_REG_NVM_PAR_H1_H        0xE3        /**< NVM PAR H1 high register */
#define BME690_REG_NVM_PAR_H2          0xE4        /**< NVM PAR H2 register */
#define BME690_REG_NVM_PAR_H3          0xE6        /**< NVM PAR H3 register */
#define BME690_REG_NVM_PAR_H4          0xE5        /**< NVM PAR H4 register */
#define BME690_REG_NVM_PAR_H5_L        0xE2        /**< NVM PAR H5 low register */
#define BME690_REG_NVM_PAR_H5_H        0xE1        /**< NVM PAR H5 high register */
#define BME690_REG_NVM_PAR_H6          0xE7        /**< NVM PAR H6 register */
#define BME690_REG_NVM_PAR_G1          0xED        /**< NVM PAR G1 register */
#define BME690_REG_NVM_PAR_G2_L        0xEB        /**< NVM PAR G2 low register */
#define BME690_REG_NVM_PAR_G2_H        0xEC        /**< NVM PAR G2 high register */
#define BME690_REG_NVM_PAR_G3          0xEE        /**< NVM PAR G3 register */
#define BME690_REG_NVM_RES_HEAT_RANGE  0x02        /**< NVM RES HEAT RANGE register */
#define BME690_REG_NVM_RES_HEAT_VAL    0x00        /**< NVM RES HEAT VAL register */
#define BME690_REG_NVM_RANGE_SWITCH    0x04        /**< NVM RANGE SWITCH ERROR register */
#define BME690_REG_STATUS              0x73        /**< status register */
#define BME690_REG_VARIANT_ID          0xF0        /**< variant id register */
#define BME690_REG_RESET               0xE0        /**< reset register */
#define BME690_REG_ID                  0xD0        /**< id register */
#define BME690_REG_CONFIG              0x75        /**< config register */
#define BME690_REG_CTRL_MEAS           0x74        /**< control meas register */
#define BME690_REG_CTRL_HUM            0x72        /**< control humidity register */
#define BME690_REG_CTRL_GAS_1          0x71        /**< control gas1 register */
#define BME690_REG_CTRL_GAS_0          0x70        /**< control gas0 register */
#define BME690_REG_GAS_WAIT_SHARED     0x6E        /**< gas wait shared register */
#define BME690_REG_GAS_WAIT_X          0x64        /**< gas wait 0 register */
#define BME690_REG_RES_HEAT_X          0x5A        /**< res heat 0 register */
#define BME690_REG_IDAC_HEAT_X         0x50        /**< idac heat 0 register */
#define BME690_REG_GAS_R_LSB_2         0x4F        /**< gas r lsb register */
#define BME690_REG_GAS_R_MSB_2         0x4E        /**< gas r msb register */
#define BME690_REG_HUM_LSB_2           0x48        /**< hum lsb register */
#define BME690_REG_HUM_MSB_2           0x47        /**< hum msb register */
#define BME690_REG_TEMP_XLSB_2         0x46        /**< temp xlsb register */
#define BME690_REG_TEMP_LSB_2          0x45        /**< temp lsb register */
#define BME690_REG_TEMP_MSB_2          0x44        /**< temp msb register */
#define BME690_REG_PRESS_XLSB_2        0x43        /**< press xlsb register */
#define BME690_REG_PRESS_LSB_2         0x42        /**< press lsb register */
#define BME690_REG_PRESS_MSB_2         0x41        /**< press msb register */
#define BME690_REG_SUB_MEAS_INDEX_2    0x40        /**< sub meas index register */
#define BME690_REG_MEAS_STATUS_2       0x3F        /**< meas status 0 register */
#define BME690_REG_GAS_R_LSB_1         0x3E        /**< gas r lsb register */
#define BME690_REG_GAS_R_MSB_1         0x3D        /**< gas r msb register */
#define BME690_REG_HUM_LSB_1           0x37        /**< hum lsb register */
#define BME690_REG_HUM_MSB_1           0x36        /**< hum msb register */
#define BME690_REG_TEMP_XLSB_1         0x35        /**< temp xlsb register */
#define BME690_REG_TEMP_LSB_1          0x34        /**< temp lsb register */
#define BME690_REG_TEMP_MSB_1          0x33        /**< temp msb register */
#define BME690_REG_PRESS_XLSB_1        0x32        /**< press xlsb register */
#define BME690_REG_PRESS_LSB_1         0x31        /**< press lsb register */
#define BME690_REG_PRESS_MSB_1         0x30        /**< press msb register */
#define BME690_REG_SUB_MEAS_INDEX_1    0x2F        /**< sub meas index register */
#define BME690_REG_MEAS_STATUS_1       0x2E        /**< meas status 0 register */
#define BME690_REG_GAS_R_LSB_0         0x2D        /**< gas r lsb register */
#define BME690_REG_GAS_R_MSB_0         0x2C        /**< gas r msb register */
#define BME690_REG_HUM_LSB_0           0x26        /**< hum lsb register */
#define BME690_REG_HUM_MSB_0           0x25        /**< hum msb register */
#define BME690_REG_TEMP_XLSB_0         0x24        /**< temp xlsb register */
#define BME690_REG_TEMP_LSB_0          0x23        /**< temp lsb register */
#define BME690_REG_TEMP_MSB_0          0x22        /**< temp msb register */
#define BME690_REG_PRESS_XLSB_0        0x21        /**< press xlsb register */
#define BME690_REG_PRESS_LSB_0         0x20        /**< press lsb register */
#define BME690_REG_PRESS_MSB_0         0x1F        /**< press msb register */
#define BME690_REG_SUB_MEAS_INDEX_0    0x1E        /**< sub meas index register */
#define BME690_REG_MEAS_STATUS_0       0x1D        /**< meas status 0 register */

/**
 * @brief     change spi page
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] page spi page
 * @return    status code
 *            - 0 success
 *            - 1 change failed
 * @note      none
 */
static uint8_t a_bme690_change_spi_page(bme690_handle_t *handle, uint8_t page)
{
    uint8_t reg;
    uint8_t buf[1];

    reg = BME690_REG_STATUS;                        /* set address */
    reg |= 1 << 7;                                  /* set read mode */
    if (handle->spi_read(reg, buf, 1) != 0)         /* spi read */
    {
        return 1;                                   /* return error */
    }
    if (page == 0)                                  /* check page */
    {
        buf[0] &= ~(1 << 4);                        /* set page 0 */
    }
    else
    {
        buf[0] |= 1 << 4;                           /* set page 1 */
    }
    reg &= ~(1 << 7);                               /* write mode */
    if (handle->spi_write(reg, buf, 1) != 0)        /* spi write */
    {
        return 1;                                   /* return error */
    }
    handle->page = page;                            /* save page */
    
    return 0;                                       /* success return 0 */
}

/**
 * @brief      read multiple bytes
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 iic spi read failed
 * @note       none
 */
static uint8_t a_bme690_iic_spi_read(bme690_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_spi == BME690_INTERFACE_IIC)                           /* iic interface */
    {
        if (handle->iic_read(handle->iic_addr, reg, buf, len) != 0)        /* iic read */
        {
            return 1;                                                      /* return error */
        }

        return 0;                                                          /* success return 0 */
    }
    else                                                                   /* spi interface */
    {
        if (reg > 0x7F)                                                    /* check address */
        {
            if (handle->page != 0)                                         /* check page */
            {
                if (a_bme690_change_spi_page(handle, 0) != 0)              /* change spi change */
                {
                    return 1;                                              /* return error */
                }
            }
            reg -= 0x80;                                                   /* set address */
            reg |= 1 << 7;                                                 /* set read mode */
            if (handle->spi_read(reg, buf, len) != 0)                      /* spi read */
            {
                return 1;                                                  /* return error */
            }
        }
        else
        {
            if (handle->page == 0)                                         /* check page */
            {
                if (a_bme690_change_spi_page(handle, 1) != 0)              /* change spi change */
                {
                    return 1;                                              /* return error */
                }
            }
            reg |= 1 << 7;                                                 /* set read mode */
            if (handle->spi_read(reg, buf, len) != 0)                      /* spi read */
            {
                return 1;                                                  /* return error */
            }
        }

        return 0;                                                          /* success return 0 */
    }
}

/**
 * @brief     write multiple bytes
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 iic spi write failed
 * @note      none
 */
static uint8_t a_bme690_iic_spi_write(bme690_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_spi == BME690_INTERFACE_IIC)                           /* iic interface */
    {
        if (handle->iic_write(handle->iic_addr, reg, buf, len) != 0)       /* iic write */
        {
            return 1;                                                      /* return error */
        }

        return 0;                                                          /* success return 0 */
    }
    else                                                                   /* spi interface */
    {
        if (reg > 0x7F)                                                    /* check address */
        {
            if (handle->page != 0)                                         /* check page */
            {
                if (a_bme690_change_spi_page(handle, 0) != 0)              /* change spi change */
                {
                    return 1;                                              /* return error */
                }
            }
            reg -= 0x80;                                                   /* set address */
            reg &= ~(1 << 7);                                              /* write mode */
            if (handle->spi_write(reg, buf, len) != 0)                     /* spi write */
            {
                return 1;                                                  /* return error */
            }
        }
        else
        {
            if (handle->page == 0)                                         /* check page */
            {
                if (a_bme690_change_spi_page(handle, 1) != 0)              /* change spi change */
                {
                    return 1;                                              /* return error */
                }
            }
            reg &= ~(1 << 7);                                              /* write mode */
            if (handle->spi_write(reg, buf, len) != 0)                     /* spi write */
            {
                return 1;                                                  /* return error */
            }
        }

        return 0;                                                          /* success return 0 */
    }
}

/**
 * @brief     get nvm calibration
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 get calibration data failed
 * @note      none
 */
static uint8_t a_bme690_get_nvm_calibration(bme690_handle_t *handle)
{
    uint8_t reg;
    uint8_t buf[2];

    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_T1_L, (uint8_t *)buf, 2) != 0)        /* read t1 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_t1 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par t1 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_T2_L, (uint8_t *)buf, 2) != 0)        /* read t2 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_t2 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par t2 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_T3, (uint8_t *)&reg, 1) != 0)         /* read t3 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_t3 = (int8_t)(reg);                                                            /* set par t3 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P1_L, (uint8_t *)buf, 2) != 0)        /* read p1 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p1 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par p1 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P2_L, (uint8_t *)buf, 2) != 0)        /* read p2 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p2 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par p2 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P3, (uint8_t *)&reg, 1) != 0)         /* read p3 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p3 = (int8_t)(reg);                                                            /* set par p3 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P4, (uint8_t *)&reg, 1) != 0)         /* read p4 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p4 = (int8_t)(reg);                                                            /* set par p4 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P5_L, (uint8_t *)buf, 2) != 0)        /* read p5 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p5 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par p5 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P6_L, (uint8_t *)buf, 2) != 0)        /* read p6 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p6 = (int16_t)((uint16_t)buf[1] << 8 | buf[0]);                                /* set par p6 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P7, (uint8_t *)&reg, 1) != 0)         /* read p7 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p7 = (int8_t)(reg);                                                            /* set par p7 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P8, (uint8_t *)&reg, 1) != 0)         /* read p8 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p8 = (int8_t)(reg);                                                            /* set par p8 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P9_L, (uint8_t *)buf, 2) != 0)        /* read p9 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p9 = (int16_t)((uint16_t)buf[1] << 8 | buf[0]);                                /* set par p9 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P10, (uint8_t *)&reg, 1) != 0)        /* read p10 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p10 = (int8_t)(reg);                                                           /* set par p10 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_P11, (uint8_t *)&reg, 1) != 0)        /* read p11 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_p11 = (int8_t)(reg);                                                           /* set par p11 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H1_L, (uint8_t *)buf, 2) != 0)        /* read h1 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h1 = (int16_t)((uint16_t)buf[1] << 4 | (buf[0] & 0x0F));                       /* set h1 */
    if (handle->par_h1 > 2047)                                                                 /* check range */
    {
        handle->par_h1 = (int16_t)(handle->par_h1 - 4096);                                     /* set h1 */
    }
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H2, (uint8_t *)&reg, 1) != 0)         /* read h2 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h2 = (uint8_t)reg;                                                             /* set h2 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H3, (uint8_t *)&reg, 1) != 0)         /* read h3 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h3 = (int8_t)reg;                                                              /* set h3 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H4, (uint8_t *)&reg, 1) != 0)         /* read h4 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h4 = (int8_t)reg;                                                              /* set h4 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H5_H, (uint8_t *)buf, 2) != 0)        /* read h5 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h5 = (int16_t)((uint16_t)buf[0] << 4 | buf[1] >> 4);                           /* set h5 */
    if (handle->par_h5 > 2047)                                                                 /* check h5 */
    {
        handle->par_h5 = (int16_t)(handle->par_h5 - 4096);                                     /* set h5 */
    }
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_H6, (uint8_t *)&reg, 1) != 0)         /* read h6 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_h6 = (int8_t)reg;                                                              /* set h6 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_G1, (uint8_t *)&reg, 1) != 0)         /* read gh1 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_g1 = (int8_t)reg;                                                              /* set par g1 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_G2_L, (uint8_t *)buf, 2) != 0)        /* read g2 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_g2 = (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                               /* set par g2 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_PAR_G3, (uint8_t *)&reg, 1) != 0)         /* read g3 */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->par_g3 = (int8_t)reg;                                                              /* set par g3 */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_RES_HEAT_RANGE, (uint8_t *)&reg, 1) != 0) /* read res heat range */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->res_heat_range = (uint8_t)((reg >> 4) & 3);                                        /* set res heat range */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_RES_HEAT_VAL, (uint8_t *)&reg, 1) != 0)   /* read res heat val */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->res_heat_val = (int8_t)(reg);                                                      /* set res heat val */
    if (a_bme690_iic_spi_read(handle, BME690_REG_NVM_RANGE_SWITCH, (uint8_t *)&reg, 1) != 0)   /* read range switch error */
    {
        handle->debug_print("bme690: get calibration data failed.\n");                         /* get calibration data failed */

        return 1;                                                                              /* return error */
    }
    handle->range_sw_err = (int8_t)(((int8_t)(reg & 0xF0)) / 16);                              /* set range switch error */
    handle->t_fine = 0.0f;                                                                     /* init 0 */
    handle->amb_temp = 25;                                                                     /* set 25c */

    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      compensate temperature
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  raw raw data
 * @param[out] *output pointer to an output buffer
 * @return     status code
 *             - 0 success
 *             - 1 compensate temperature failed
 * @note       none
 */
static uint8_t a_bme690_compensate_temperature(bme690_handle_t *handle, uint32_t raw, float *output)
{
    int32_t do1;
    double cf;
    double dtk1, dtk2, temp1, temp2;
    double calc_temp;
    
    do1 = (int32_t)handle->par_t1 << 8;                          /* calculate do1 */
    dtk1 = (double)handle->par_t2 / (double)(1ULL << 30);        /* calculate dtk1 */
    dtk2 = (double)handle->par_t3 / (double)(1ULL << 48);        /* calculate dtk2 */
    cf = (double)raw - (double)do1;                              /* calculate cf */
    temp1 = (double)(cf * dtk1);                                 /* calculate temp1 */
    temp2 = (double)(cf) * (double)(cf) * dtk2;                  /* calculate temp2 */
    calc_temp = temp1 + temp2;                                   /* calculate calc temp */
    *output = (float)calc_temp ;                                 /* compensated temperature data */
    
    return 0;                                                    /* success return 0 */
}

/**
 * @brief      compensate pressure
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  raw raw data
 * @param[in]  comp_temperature compensate temperature
 * @param[out] *output pointer to an output buffer
 * @return     status code
 *             - 0 success
 *             - 1 compensate pressure failed
 * @note       none
 */
static uint8_t a_bme690_compensate_pressure(bme690_handle_t *handle, float comp_temperature, uint32_t raw, float *output)
{
    uint32_t o;
    double tk10, tk20, tk30;
    double s;
    double tk1s, tk2s, tk3s;
    double nls, tknls, nls3;
    double calc_pres, tmp1, tmp2, tmp3, tmp4;
    
    o = (uint32_t)handle->par_p1 * (uint32_t)(1ULL << 3);                                                 /* calculate o */
    tk10 = (double)handle->par_p2 / (double)(1ULL << 6);                                                  /* calculate tk10 */
    tk20 = (double)handle->par_p3 / (double)(1ULL << 8);                                                  /* calculate tk20 */
    tk30 = (double)handle->par_p4 / (double)(1ULL << 15);                                                 /* calculate tk30 */
    s = ((double)handle->par_p5 - (double)(1ULL << 14)) / (double)(1ULL << 20);                           /* calculate s */
    tk1s = ((double)handle->par_p6 - (double)(1ULL << 14)) / (double)(1ULL << 29);                        /* calculate tk1s */
    tk2s = (double)handle->par_p7 / (double)(1ULL << 32);                                                 /* calculate tk2s */
    tk3s = (double)handle->par_p8 / (double)(1ULL << 37);                                                 /* calculate tk3s */
    nls = (double)handle->par_p9 / (double)(1ULL << 48);                                                  /* calculate nls */
    tknls = (double)handle->par_p10 / (double)(1ULL << 48);                                               /* calculate tknls */
    nls3 = (double)handle->par_p11 / ((double)(1ULL << 35) * (double)(1ULL << 30));                       /* calculate nls3 */
    tmp1 = (double)o + (tk10 * comp_temperature) + (tk20 * comp_temperature * comp_temperature) +
           (tk30 * comp_temperature * comp_temperature * comp_temperature);                               /* calculate tmp1 */
    tmp2 = (double)raw *
           ((double)s + (tk1s * comp_temperature) + (tk2s * comp_temperature * comp_temperature) +
           (tk3s * comp_temperature * comp_temperature * comp_temperature));                              /* calculate tmp2 */
    tmp3 = (double)raw * (double)raw * (nls + (tknls * comp_temperature));                                /* calculate tmp3 */
    tmp4 = (double)raw * (double)raw * (double)raw * nls3;                                                /* calculate tmp4 */
    calc_pres = tmp1 + tmp2 + tmp3 + tmp4;                                                                /* set calc pres */
    *output= (float)calc_pres;                                                                            /* save to output */
    
    return 0;                                                                                             /* success return 0 */
}

/**
 * @brief      compensate humidity
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  raw raw data
 * @param[in]  comp_temperature compensate temperature
 * @param[out] *output pointer to an output buffer
 * @return     status code
 *             - 0 success
 *             - 1 compensate humidity failed
 * @note       none
 */
static uint8_t a_bme690_compensate_humidity(bme690_handle_t *handle, float comp_temperature, uint16_t raw, float *output)
{
    double oh, tk10h, sh;
    double tk1sh, tk2sh, hlin2;
    double hoff, hsens;
    double temp_comp, calc_hum, hum_float_val;
    
    temp_comp = (comp_temperature * 5120) - 76800;                                                  /* calculate temp comp */
    oh = (double)handle->par_h1 * (double)(1ULL << 6);                                              /* calculate oh */
    sh = (double)handle->par_h5 / (double)(1ULL << 16);                                             /* calculate sh */
    tk10h = (double)handle->par_h2 / (double)(1ULL << 14);                                          /* calculate tk10h */
    tk1sh = (double)handle->par_h4 / (double)(1ULL << 26);                                          /* calculate tk1sh */
    tk2sh = (double)handle->par_h3 / (double)(1ULL << 26);                                          /* calculate tk2sh */
    hlin2 = (double)handle->par_h6 / (double)(1ULL << 19);                                          /* calculate hlin2 */
    hoff = (double)raw - (oh + tk10h * temp_comp);                                                  /* calculate hoff */
    hsens = hoff * sh * (1 + (tk1sh * temp_comp) + (tk1sh * tk2sh * temp_comp * temp_comp));        /* calculate hsens */
    hum_float_val = hsens * (1 - hlin2 * hsens);                                                    /* calculate hum float val */
    if (hum_float_val < 0.0)                                                                        /* check hum float val */
    {
        hum_float_val = 0.0;                                                                        /* set 0 */
    }
    else if (hum_float_val >= 100.00)                                                               /* check hum float val */
    {
        hum_float_val = 100.0;                                                                      /* set 100 */
    }
    else
    {
        
    }
    calc_hum = hum_float_val;                                                                       /* set calc_hum */
    *output = (float)calc_hum;                                                                      /* save to output */
    
    return 0;                                                                                       /* success return 0 */
}

/**
 * @brief      compensate heat
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  temp heat temp
 * @param[out] *reg pointer to a register buffer
 * @return     status code
 *             - 0 success
 *             - 1 compensate heat failed
 * @note       none
 */
static uint8_t a_bme690_compensate_heat(bme690_handle_t *handle, float temp, uint8_t *reg)
{
    float var1;
    float var2;
    float var3;
    float var4;
    float var5;
    uint8_t res_heat;

    if (temp > 400.0f)                                                                      /* cap temperature */
    {
        temp = 400.0f;                                                                      /* set 400 */
    }
    var1 = (((float)handle->par_g1 / (16.0f)) + 49.0f);                                     /* calculate var1 */
    var2 = ((((float)handle->par_g2 / (32768.0f)) * (0.0005f)) + 0.00235f);                 /* calculate var2 */
    var3 = ((float)handle->par_g3 / (1024.0f));                                             /* calculate var3 */
    var4 = (var1 * (1.0f + (var2 * (float)temp)));                                          /* calculate var4 */
    var5 = (var4 + (var3 * (float)handle->amb_temp));                                       /* calculate var5 */
    res_heat = (uint8_t)(3.4f * ((var5 * (4 / (4 + (float)handle->res_heat_range)) *
               (1 / (1 + ((float)handle->res_heat_val * 0.002f)))) - 25));                  /* calculate res heat */
    *reg = res_heat;                                                                        /* set res */
    
    return 0;                                                                               /* success return 0 */
}

/**
 * @brief      compensate gas resistance
 * @param[in]  gas_res_adc gas resistance adc
 * @param[in]  gas_range gas range
 * @param[out] *ohms pointer to an ohms buffer
 * @return     status code
 *             - 0 success
 *             - 1 compensate gas resistance failed
 * @note       none
 */
static uint8_t a_bme690_compensate_gas_resistance(uint16_t gas_res_adc, uint8_t gas_range, float *ohms)
{
    float calc_gas_res;
    
    uint32_t var1 = (uint32_t)262144 >> gas_range;                /* calculate var1 */
    int32_t var2 = (int32_t)gas_res_adc - (int32_t)512;           /* calculate var2 */
    var2 *= (int32_t)3;                                           /* calculate var2 */
    var2 = (int32_t)4096 + var2;                                  /* calculate var2 */
    calc_gas_res = 1000000.0f * (float)var1 / (float)var2;        /* calculate calc_gas_res */
    *ohms = calc_gas_res;                                         /* save gas resistance to ohms */
    
    return 0;                                                     /* success return 0 */
}

/**
 * @brief     calculate parallel counter
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    counter
 * @note      none
 */
static uint8_t a_bme690_calculate_parallel_counter(bme690_handle_t *handle)
{
    uint8_t i;
    uint8_t cnt;
    
    cnt = 0;                                                        /* init 0 */
    for (i = 0; i < 16; i++)                                        /* 16 times */
    {
        if ((handle->parallel_data_flag >> (15 - i)) & 0x01)        /* check flag */
        {
            cnt++;                                                  /* cnt++ */
        }
    }
    
    return cnt;                                                     /* return counter */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] addr_pin iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bme690_set_addr_pin(bme690_handle_t *handle, bme690_address_t addr_pin)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }

    handle->iic_addr = (uint8_t)addr_pin;        /* set iic address */

    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *addr_pin pointer to an iic address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme690_get_addr_pin(bme690_handle_t *handle, bme690_address_t *addr_pin)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }

    *addr_pin = (bme690_address_t)handle->iic_addr;        /* get iic address */

    return 0;                                              /* success return 0 */
}

/**
 * @brief     set the interface
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bme690_set_interface(bme690_handle_t *handle, bme690_interface_t interface)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }

    handle->iic_spi = (uint8_t)interface;      /* set interface */

    return 0;                                  /* success return 0 */
}

/**
 * @brief      get the interface
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *interface pointer to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme690_get_interface(bme690_handle_t *handle, bme690_interface_t *interface)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }

    *interface = (bme690_interface_t)(handle->iic_spi);        /* get interface */

    return 0;                                                  /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is error
 *            - 5 reset failed
 *            - 6 read calibration failed
 * @note      none
 */
uint8_t bme690_init(bme690_handle_t *handle)
{
    uint8_t i;
    uint8_t id;
    uint8_t reg;

    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                                 /* check debug_print */
    {
        return 3;                                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                                    /* check iic_init */
    {
        handle->debug_print("bme690: iic_init is null.\n");                          /* iic_init is nul */

        return 3;                                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                                  /* check iic_deinit */
    {
        handle->debug_print("bme690: iic_deinit is null.\n");                        /* iic_deinit is null */

        return 3;                                                                    /* return error */
    }
    if (handle->iic_read == NULL)                                                    /* check iic_read */
    {
        handle->debug_print("bme690: iic_read is null.\n");                          /* iic_read is null */

        return 3;                                                                    /* return error */
    }
    if (handle->iic_write == NULL)                                                   /* check iic_write */
    {
        handle->debug_print("bme690: iic_write is null.\n");                         /* iic_write is null */

        return 3;                                                                    /* return error */
    }
    if (handle->spi_init == NULL)                                                    /* check spi_init */
    {
        handle->debug_print("bme690: spi_init is null.\n");                          /* spi_init is nul */

        return 3;                                                                    /* return error */
    }
    if (handle->spi_deinit == NULL)                                                  /* check spi_deinit */
    {
        handle->debug_print("bme690: spi_deinit is null.\n");                        /* spi_deinit is nul */

        return 3;                                                                    /* return error */
    }
    if (handle->spi_read == NULL)                                                    /* check spi_read */
    {
        handle->debug_print("bme690: spi_read is null.\n");                          /* spi_read is nul */

        return 3;                                                                    /* return error */
    }
    if (handle->spi_write == NULL)                                                   /* check spi_write */
    {
        handle->debug_print("bme690: spi_write is null.\n");                         /* spi_write is nul */

        return 3;                                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                                    /* check delay_ms */
    {
        handle->debug_print("bme690: delay_ms is null.\n");                          /* delay_ms is null */

        return 3;                                                                    /* return error */
    }
    if (handle->receive_callback == NULL)                                            /* check receive_callback */
    {
        handle->debug_print("bme690: receive_callback is null.\n");                  /* receive_callback is null */

        return 3;                                                                    /* return error */
    }
    
    if (handle->iic_spi == BME690_INTERFACE_IIC)                                     /* iic interface */
    {
        if (handle->iic_init() != 0)                                                 /* iic init */
        {
            handle->debug_print("bme690: iic init failed.\n");                       /* iic init failed */

            return 1;                                                                /* return error */
        }
    }
    else                                                                             /* spi interface */
    {
        if (handle->spi_init() != 0)                                                 /* spi init */
        {
            handle->debug_print("bme690: spi init failed.\n");                       /* spi init failed */

            return 1;                                                                /* return error */
        }
        if (a_bme690_change_spi_page(handle, 0) != 0)                                /* change spi page 0 */
        {
            handle->debug_print("bme690: change spi page failed.\n");                /* change spi page failed */

            return 1;                                                                /* return error */
        }
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_ID, (uint8_t *)&id, 1) != 0)        /* read chip id */
    {
        handle->debug_print("bme690: read id failed.\n");                            /* read id failed */
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }
        
        return 4;                                                                    /* return error */
    }
    if (id != 0x61)                                                                  /* check id */
    {
        handle->debug_print("bme690: id is error.\n");                               /* id is error */
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }

        return 4;                                                                    /* return error */
    }
    if (a_bme690_iic_spi_read(handle, BME690_REG_VARIANT_ID, 
                             (uint8_t *)&id, 1) != 0)                                /* read variant id */
    {
        handle->debug_print("bme690: read variant id failed.\n");                    /* read variant id failed */
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }

        return 4;                                                                    /* return error */
    }
    if (id != 0x02)                                                                  /* check variant id */
    {
        handle->debug_print("bme690: variant id is error.\n");                       /* variant id is error */
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }

        return 4;                                                                    /* return error */
    }
    reg = 0xB6;                                                                      /* set the reset value */
    if (a_bme690_iic_spi_write(handle, BME690_REG_RESET, &reg, 1) != 0)              /* reset the chip */
    {
        handle->debug_print("bme690: reset failed.\n");                              /* reset failed */
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }

        return 5;                                                                    /* return error */
    }
    handle->delay_ms(5);                                                             /* delay 5ms */
    if (a_bme690_get_nvm_calibration(handle) != 0)                                   /* get nvm calibration */
    {
        if (handle->iic_spi == BME690_INTERFACE_IIC)                                 /* iic interface */
        {
            (void)handle->iic_deinit();                                              /* iic deinit */
        }
        else                                                                         /* spi interface */
        {
            (void)handle->spi_deinit();                                              /* spi deinit */
        }

        return 6;                                                                    /* return error */
    }
    for (i = 0; i < 3; i++)                                                          /* set all 0 */
    {
        handle->parallel_sequence_trigger[i] = 0;                                    /* init 0 */
        handle->parallel_sequence_number[i] = 0;                                     /* init 0 */
    }
    handle->parallel_data_len = 0;                                                   /* init 0 */
    handle->parallel_data_flag = 0;                                                  /* init 0 */
    handle->inited = 1;                                                              /* flag finish initialization */

    return 0;                                                                        /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t bme690_deinit(bme690_handle_t *handle)
{
    uint8_t prev;

    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)         /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                    /* read ctrl meas failed */

        return 4;                                                                   /* return error */
    }
    prev &= ~(3 << 0);                                                              /* clear settings */
    prev |= 0 << 0;                                                                 /* set sleep mode */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)        /* write ctrl meas */
    {
        handle->debug_print("bme690: write ctrl meas failed.\n");                   /* write ctrl meas failed */

        return 4;                                                                   /* return error */
    }
    if (handle->iic_spi == BME690_INTERFACE_IIC)                                    /* iic interface */
    {
        if (handle->iic_deinit() != 0)                                              /* iic deinit */
        {
            handle->debug_print("bme690: iic deinit failed.\n");                    /* iic deinit failed */

            return 1;                                                               /* return error */
        }
    }
    else                                                                            /* spi interface */
    {
        if (handle->spi_deinit() != 0)                                              /* spi deinit */
        {
            handle->debug_print("bme690: spi deinit failed.\n");                    /* spi deinit failed */

            return 1;                                                               /* return error */
        }
    }
    handle->inited = 0;                                                             /* flag close */

    return 0;                                                                       /* success return 0 */
}

/**
 * @brief     set idac heater
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set idac heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme690_set_idac_heater(bme690_handle_t *handle, uint8_t index, uint8_t reg)
{
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    if (index > 9)                                                                            /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                          /* index > 9 */

        return 4;                                                                             /* return error */
    }

    prev = reg;
    if (a_bme690_iic_spi_write(handle, BME690_REG_IDAC_HEAT_X + index, &prev, 1) != 0)        /* write idac heater */
    {
        handle->debug_print("bme690: write idac heater failed.\n");                           /* write idac heater failed */

        return 1;                                                                             /* return error */
    }

    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief      get idac heater
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get idac heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme690_get_idac_heater(bme690_handle_t *handle, uint8_t index, uint8_t *reg)
{
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    if (index > 9)                                                                         /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                       /* index > 9 */

        return 4;                                                                          /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_IDAC_HEAT_X + index, reg, 1) != 0)        /* read idac heater */
    {
        handle->debug_print("bme690: read idac heater failed.\n");                         /* read idac heater failed */

        return 1;                                                                          /* return error */
    }

    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set resistance heater
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set resistance heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme690_set_resistance_heater(bme690_handle_t *handle, uint8_t index, uint8_t reg)
{
    uint8_t prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    if (index > 9)                                                                           /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                         /* index > 9 */

        return 4;                                                                            /* return error */
    }

    prev = reg;
    if (a_bme690_iic_spi_write(handle, BME690_REG_RES_HEAT_X + index, &prev, 1) != 0)        /* write resistance heater */
    {
        handle->debug_print("bme690: write resistance heater failed.\n");                    /* write resistance heater failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get resistance heater
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resistance heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme690_get_resistance_heater(bme690_handle_t *handle, uint8_t index, uint8_t *reg)
{
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (index > 9)                                                                        /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                      /* index > 9 */

        return 4;                                                                         /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_RES_HEAT_X + index, reg, 1) != 0)        /* read resistance heater */
    {
        handle->debug_print("bme690: read resistance heater failed.\n");                  /* read resistance heater failed */

        return 1;                                                                         /* return error */
    }

    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set gas wait
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set gas wait failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme690_set_gas_wait(bme690_handle_t *handle, uint8_t index, uint8_t reg)
{
    uint8_t prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    if (index > 9)                                                                           /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                         /* index > 9 */

        return 4;                                                                            /* return error */
    }

    prev = reg;
    if (a_bme690_iic_spi_write(handle, BME690_REG_GAS_WAIT_X + index, &prev, 1) != 0)        /* write gas wait */
    {
        handle->debug_print("bme690: write gas wait failed.\n");                             /* write gas wait failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get gas wait
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas wait failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme690_get_gas_wait(bme690_handle_t *handle, uint8_t index, uint8_t *reg)
{
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (index > 9)                                                                        /* check index */
    {
        handle->debug_print("bme690: index > 9.\n");                                      /* index > 9 */

        return 4;                                                                         /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_GAS_WAIT_X + index, reg, 1) != 0)        /* read gas wait */
    {
        handle->debug_print("bme690: read gas wait failed.\n");                           /* read gas wait failed */

        return 1;                                                                         /* return error */
    }

    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set gas wait shared
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set gas wait shared failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_gas_wait_shared(bme690_handle_t *handle, uint8_t reg)
{
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }

    prev = reg;                                                                           /* set param */
    if (a_bme690_iic_spi_write(handle, BME690_REG_GAS_WAIT_SHARED, &prev, 1) != 0)        /* write gas wait shared */
    {
        handle->debug_print("bme690: write gas wait shared failed.\n");                   /* write gas wait shared failed */

        return 1;                                                                         /* return error */
    }

    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get gas wait shared
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas wait shared failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_gas_wait_shared(bme690_handle_t *handle, uint8_t *reg)
{
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_GAS_WAIT_SHARED, &prev, 1) != 0)        /* read gas wait shared */
    {
        handle->debug_print("bme690: read gas wait shared failed.\n");                   /* read gas wait shared failed */

        return 1;                                                                        /* return error */
    }
    *reg = prev;                                                                         /* set reg */

    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     soft reset
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_soft_reset(bme690_handle_t *handle)
{
    uint8_t reg;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    reg = 0xB6;                                                                /* set the reset value */
    if (a_bme690_iic_spi_write(handle, BME690_REG_RESET, &reg, 1) != 0)        /* reset the chip */
    {
        handle->debug_print("bme690: reset failed.\n");                        /* reset failed */

        return 1;                                                              /* return error */
    }
    handle->delay_ms(5);                                                       /* delay 5ms */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     enable or disable spi wire3 data interrupt
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire 3 data interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_spi_wire_3_data_interrupt(bme690_handle_t *handle, bme690_bool_t enable)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)     /* read ctrl hum */
    {
        handle->debug_print("bme690: read ctrl hum failed.\n");                /* read ctrl hum failed */

        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 6);                                                         /* clear settings */
    prev |= enable << 6;                                                       /* set bool */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)    /* write ctrl hum */
    {
        handle->debug_print("bme690: write ctrl hum failed.\n");               /* write ctrl hum failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      get spi wire3 data interrupt status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire 3 data interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_spi_wire_3_data_interrupt(bme690_handle_t *handle, bme690_bool_t *enable)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)     /* read ctrl hum */
    {
        handle->debug_print("bme690: read ctrl hum failed.\n");                /* read ctrl hum failed */

        return 1;                                                              /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 6) & 0x01);                             /* get bool */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set humidity oversampling
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] oversampling humidity oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set humidity oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_humidity_oversampling(bme690_handle_t *handle, bme690_oversampling_t oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)     /* read ctrl hum */
    {
        handle->debug_print("bme690: read ctrl hum failed.\n");                /* read ctrl hum failed */

        return 1;                                                              /* return error */
    }
    prev &= ~(7 << 0);                                                         /* clear settings */
    prev |= oversampling << 0;                                                 /* set oversampling */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)    /* write ctrl hum */
    {
        handle->debug_print("bme690: write ctrl hum failed.\n");               /* write ctrl hum failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      get humidity oversampling
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *oversampling pointer to a humidity oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get humidity oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_humidity_oversampling(bme690_handle_t *handle, bme690_oversampling_t *oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_HUM, &prev, 1) != 0)     /* read ctrl hum */
    {
        handle->debug_print("bme690: read ctrl hum failed.\n");                /* read ctrl hum failed */

        return 1;                                                              /* return error */
    }
    *oversampling = (bme690_oversampling_t)(prev & 0x07);                      /* get oversampling */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set temperature oversampling
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] oversampling temperature oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set temperature oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_temperature_oversampling(bme690_handle_t *handle, bme690_oversampling_t oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");               /* read ctrl meas failed */

        return 1;                                                              /* return error */
    }
    prev &= ~(7 << 5);                                                         /* clear settings */
    prev |= oversampling << 5;                                                 /* set oversampling */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)   /* write ctrl meas */
    {
        handle->debug_print("bme690: write ctrl meas failed.\n");              /* write ctrl meas failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      get temperature oversampling
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *oversampling pointer to a oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get temperature oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_temperature_oversampling(bme690_handle_t *handle, bme690_oversampling_t *oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");               /* read ctrl meas failed */

        return 1;                                                              /* return error */
    }
    *oversampling = (bme690_oversampling_t)((prev >> 5) & 0x7);                /* set oversampling */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set pressure oversampling
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] oversampling pressure oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set pressure oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_pressure_oversampling(bme690_handle_t *handle, bme690_oversampling_t oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");               /* read ctrl meas failed */

        return 1;                                                              /* return error */
    }
    prev &= ~(7 << 2);                                                         /* clear settings */
    prev |= oversampling << 2;                                                 /* set oversampling */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)   /* write ctrl meas */
    {
        handle->debug_print("bme690: write ctrl meas failed.\n");              /* write ctrl meas failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      get pressure oversampling
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *oversampling pointer to a oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pressure oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_pressure_oversampling(bme690_handle_t *handle, bme690_oversampling_t *oversampling)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");               /* read ctrl meas failed */

        return 1;                                                              /* return error */
    }
    *oversampling = (bme690_oversampling_t)((prev >> 2) & 0x7);                /* set oversampling */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set mode
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_mode(bme690_handle_t *handle, bme690_mode_t mode)
{
    uint8_t prev;

    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)         /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                    /* read ctrl meas failed */

        return 1;                                                                   /* return error */
    }
    prev &= ~(3 << 0);                                                              /* clear settings */
    prev |= mode << 0;                                                              /* set mode */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)        /* write ctrl meas */
    {
        handle->debug_print("bme690: write ctrl meas failed.\n");                   /* write ctrl meas failed */

        return 1;                                                                   /* return error */
    }

    return 0;                                                                       /* success return 0 */
}

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *mode pointer to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_mode(bme690_handle_t *handle, bme690_mode_t *mode)
{
    uint8_t prev;

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");               /* read ctrl meas failed */

        return 1;                                                              /* return error */
    }
    *mode = (bme690_mode_t)((prev >> 0) & 0x3);                                /* set mode */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set filter
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] filter input filter
 * @return    status code
 *            - 0 success
 *            - 1 set filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_filter(bme690_handle_t *handle, bme690_filter_t filter)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CONFIG, &prev, 1) != 0)         /* read config */
    {
        handle->debug_print("bme690: read config failed.\n");                    /* read config failed */

        return 1;                                                                /* return error */
    }
    prev &= ~(7 << 2);                                                           /* clear settings */
    prev |= (filter & 0x07) << 2;                                                /* set filter */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CONFIG, &prev, 1) != 0)        /* write config */
    {
        handle->debug_print("bme690: write config failed.\n");                   /* write config failed */

        return 1;                                                                /* return error */
    }

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get filter
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *filter pointer to a filter buffer
 * @return     status code
 *             - 0 success
 *             - 1 get filter failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_filter(bme690_handle_t *handle, bme690_filter_t *filter)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CONFIG, &prev, 1) != 0)         /* read config */
    {
        handle->debug_print("bme690: read config failed.\n");                    /* read config failed */

        return 1;                                                                /* return error */
    }
    *filter = (bme690_filter_t)((prev >> 2) & 0x07);                             /* set filter */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     set spi wire
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] spi spi wire
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_spi_wire(bme690_handle_t *handle, bme690_spi_wire_t spi)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CONFIG, &prev, 1) != 0)         /* read config */
    {
        handle->debug_print("bme690: read config failed.\n");                    /* read config failed */

        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= spi << 0;                                                            /* set spi wire */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CONFIG, &prev, 1) != 0)        /* write config */
    {
        handle->debug_print("bme690: write config failed.\n");                   /* write config failed */

        return 1;                                                                /* return error */
    }

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get spi wire
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *spi pointer to a spi wire buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_spi_wire(bme690_handle_t *handle, bme690_spi_wire_t *spi)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CONFIG, &prev, 1) != 0)         /* read config */
    {
        handle->debug_print("bme690: read config failed.\n");                    /* read config failed */

        return 1;                                                                /* return error */
    }
    *spi = (bme690_spi_wire_t)((prev >> 0) & 0x01);                              /* get spi */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     enable or disable heater off
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_heater_off(bme690_handle_t *handle, bme690_bool_t enable)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_0, &prev, 1) != 0)     /* read ctrl gas0 */
    {
        handle->debug_print("bme690: read ctrl gas0 failed.\n");                 /* read ctrl gas0 failed */

        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 3);                                                           /* clear settings */
    prev |= enable << 3;                                                         /* set bool */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_GAS_0, &prev, 1) != 0)    /* write ctrl gas0 */
    {
        handle->debug_print("bme690: write ctrl gas0 failed.\n");                /* write ctrl gas0 failed */

        return 1;                                                                /* return error */
    }

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get heater off status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater off failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_heater_off(bme690_handle_t *handle, bme690_bool_t *enable)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_0, &prev, 1) != 0)     /* read ctrl gas0 */
    {
        handle->debug_print("bme690: read ctrl gas0 failed.\n");                 /* read ctrl gas0 failed */

        return 1;                                                                /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 3) & 0x01);                               /* get bool */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     enable or disable run gas
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set run gas failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_run_gas(bme690_handle_t *handle, bme690_bool_t enable)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)     /* read ctrl gas1 */
    {
        handle->debug_print("bme690: read ctrl gas1 failed.\n");                 /* read ctrl gas1 failed */

        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 5);                                                           /* clear settings */
    prev |= enable << 5;                                                         /* set bool */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)    /* write ctrl gas1 */
    {
        handle->debug_print("bme690: write ctrl gas1 failed.\n");                /* write ctrl gas1 failed */

        return 1;                                                                /* return error */
    }

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get run gas status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get run gas failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_run_gas(bme690_handle_t *handle, bme690_bool_t *enable)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)     /* read ctrl gas1 */
    {
        handle->debug_print("bme690: read ctrl gas1 failed.\n");                 /* read ctrl gas1 failed */

        return 1;                                                                /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 5) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     set heater profile
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] profile heater profile
 * @return    status code
 *            - 0 success
 *            - 1 set heater profile failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_heater_profile(bme690_handle_t *handle, bme690_heater_profile_t profile)
{
    uint8_t i;
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)     /* read ctrl gas1 */
    {
        handle->debug_print("bme690: read ctrl gas1 failed.\n");                 /* read ctrl gas1 failed */

        return 1;                                                                /* return error */
    }
    prev &= ~(0x0F << 0);                                                        /* clear settings */
    prev |= (profile & 0x0F) << 0;                                               /* set profile */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)    /* write ctrl gas1 */
    {
        handle->debug_print("bme690: write ctrl gas1 failed.\n");                /* write ctrl gas1 failed */

        return 1;                                                                /* return error */
    }
    for (i = 0; i < 3; i++)                                                      /* set all 0 */
    {
        handle->parallel_sequence_trigger[i] = 0;                                /* init 0 */
        handle->parallel_sequence_number[i] = 0;                                 /* init 0 */
    }
    handle->parallel_data_len = (uint8_t)profile;                                /* set parallel data length */
    handle->parallel_data_flag = 0;                                              /* flag init 0 */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get heater profile
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *profile pointer to a profile buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater profile failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_heater_profile(bme690_handle_t *handle, bme690_heater_profile_t *profile)
{
    uint8_t prev;

    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)     /* read ctrl gas1 */
    {
        handle->debug_print("bme690: read ctrl gas1 failed.\n");                 /* read ctrl gas1 failed */

        return 1;                                                                /* return error */
    }
    *profile = (bme690_heater_profile_t)(prev & 0x0F);                           /* set profile */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      convert the resistance heater to the register raw data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  degree_celsius input degree celsius
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_resistance_heater_convert_to_register(bme690_handle_t *handle, float degree_celsius, uint8_t *reg)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    (void)a_bme690_compensate_heat(handle, degree_celsius, reg);        /* convert real data to register data */
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      convert the idac heater to the register raw data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  ma input ma
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_idac_heater_convert_to_register(bme690_handle_t *handle, float ma, uint8_t *reg)
{
    if (handle == NULL)                         /* check handle */
    {
        return 2;                               /* return error */
    }
    if (handle->inited != 1)                    /* check handle initialization */
    {
        return 3;                               /* return error */
    }
    
    *reg = ((uint8_t)(ma * 8) - 1) << 1;        /* convert real data to register data  */
    
    return 0;                                   /* success return 0 */
}

/**
 * @brief      convert the register raw data to idac heater
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  reg register raw data
 * @param[out] *ma pointer to a ma buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_idac_heater_convert_to_data(bme690_handle_t *handle, uint8_t reg, float *ma)
{
    if (handle == NULL)                         /* check handle */
    {
        return 2;                               /* return error */
    }
    if (handle->inited != 1)                    /* check handle initialization */
    {
        return 3;                               /* return error */
    }
    
    *ma = (float)(((reg >> 1) + 1) / 8.0f);     /* convert raw data to real data */
    
    return 0;                                   /* success return 0 */
}

/**
 * @brief      convert the gas wait to the register raw data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  ms input ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 ms > 0x0FC0
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_gas_wait_convert_to_register(bme690_handle_t *handle, uint16_t ms, uint8_t *reg)
{
    uint8_t factor = 0;
    
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    if (ms > 0xFC0)                                            /* check ms */
    {
        handle->debug_print("bme690: ms > 0x0FC0.\n");         /* ms > 0x0FC0 */

        return 1;                                              /* return error */
    }
    else
    {
        while (ms > 0x3F)                                      /* check ms */
        {
            ms = ms / 4;                                       /* div 4 */
            factor += 1;                                       /* factor */
        }
        
        *reg = (uint8_t)(ms + (factor * 64));                  /* set reg */
    }
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      convert the gas wait shared to the register raw data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  m input ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 ms > 0x0783
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_gas_wait_shared_convert_to_register(bme690_handle_t *handle, float m, uint8_t *reg)
{
    uint16_t ms;
    uint8_t factor = 0;
    
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    ms = (uint16_t)m;                                          /* set ms */
    if (ms > 0x0783U)                                          /* check ms */
    {
        handle->debug_print("bme690: ms > 0x0783.\n");         /* ms > 0x0783 */

        return 1;                                              /* return error */
    }
    else
    {
        ms = (uint16_t)(((uint32_t)ms * 1000) / 477);          /* set ms */
        while (ms > 0x3F)                                      /* check ms */
        {
            ms = ms >> 2;                                      /* right shift 2 */
            factor += 1;                                       /* add 1 */
        }
        
        *reg = (uint8_t)(ms + (factor * 64));                  /* set reg */
    }
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      get new data status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get new data status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_new_data_status(bme690_handle_t *handle, bme690_section_t section, bme690_bool_t *enable)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (section == BME690_SECTION_0)                                 /* section 0 */
    {
        reg = BME690_REG_MEAS_STATUS_0;                              /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                            /* section 1 */
    {
        reg = BME690_REG_MEAS_STATUS_1;                              /* set section 1 */
    }
    else                                                             /* section 2 */
    {
        reg = BME690_REG_MEAS_STATUS_2;                              /* set section 2 */
    }
    
    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)           /* read status */
    {
        handle->debug_print("bme690: read status failed.\n");        /* read status failed */

        return 1;                                                    /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 7) & 0x01);                   /* set bool */

    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get gas measuring status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas measuring status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_gas_measuring_status(bme690_handle_t *handle, bme690_section_t section, bme690_bool_t *enable)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (section == BME690_SECTION_0)                                 /* section 0 */
    {
        reg = BME690_REG_MEAS_STATUS_0;                              /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                            /* section 1 */
    {
        reg = BME690_REG_MEAS_STATUS_1;                              /* set section 1 */
    }
    else                                                             /* section 2 */
    {
        reg = BME690_REG_MEAS_STATUS_2;                              /* set section 2 */
    }
    
    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)           /* read status */
    {
        handle->debug_print("bme690: read status failed.\n");        /* read status failed */

        return 1;                                                    /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 6) & 0x01);                   /* set bool */

    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get measuring status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get measuring status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_measuring_status(bme690_handle_t *handle, bme690_section_t section, bme690_bool_t *enable)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (section == BME690_SECTION_0)                                 /* section 0 */
    {
        reg = BME690_REG_MEAS_STATUS_0;                              /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                            /* section 1 */
    {
        reg = BME690_REG_MEAS_STATUS_1;                              /* set section 1 */
    }
    else                                                             /* section 2 */
    {
        reg = BME690_REG_MEAS_STATUS_2;                              /* set section 2 */
    }

    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)           /* read status */
    {
        handle->debug_print("bme690: read status failed.\n");        /* read status failed */

        return 1;                                                    /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 5) & 0x01);                   /* set bool */

    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get gas measuring index
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *index pointer to an index buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas measuring index failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_gas_measuring_index(bme690_handle_t *handle, bme690_section_t section, uint8_t *index)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (section == BME690_SECTION_0)                                 /* section 0 */
    {
        reg = BME690_REG_MEAS_STATUS_0;                              /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                            /* section 1 */
    {
        reg = BME690_REG_MEAS_STATUS_1;                              /* set section 1 */
    }
    else                                                             /* section 2 */
    {
        reg = BME690_REG_MEAS_STATUS_2;                              /* set section 2 */
    }
    
    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)           /* read status */
    {
        handle->debug_print("bme690: read status failed.\n");        /* read status failed */

        return 1;                                                    /* return error */
    }
    *index = (prev & 0xF);                                           /* set index */

    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get gas valid status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas valid status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_gas_valid_status(bme690_handle_t *handle, bme690_section_t section, bme690_bool_t *enable)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (section == BME690_SECTION_0)                                  /* section 0 */
    {
        reg = BME690_REG_GAS_R_LSB_0;                                 /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                             /* section 1 */
    {
        reg = BME690_REG_GAS_R_LSB_1;                                 /* set section 1 */
    }
    else                                                              /* section 2 */
    {
        reg = BME690_REG_GAS_R_LSB_2;                                 /* set section 2 */
    }
    
    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)            /* read gas lsb */
    {
        handle->debug_print("bme690: read gas lsb failed.\n");        /* read gas lsb failed */

        return 1;                                                     /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 5) & 0x01);                    /* set bool */

    return 0;                                                         /* success return 0 */
}

/**
 * @brief      get heater stability status
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater stability status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_heater_stability_status(bme690_handle_t *handle, bme690_section_t section, bme690_bool_t *enable)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (section == BME690_SECTION_0)                                  /* section 0 */
    {
        reg = BME690_REG_GAS_R_LSB_0;                                 /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                             /* section 1 */
    {
        reg = BME690_REG_GAS_R_LSB_1;                                 /* set section 1 */
    }
    else                                                              /* section 2 */
    {
        reg = BME690_REG_GAS_R_LSB_2;                                 /* set section 2 */
    }

    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)            /* read gas lsb */
    {
        handle->debug_print("bme690: read gas lsb failed.\n");        /* read gas lsb failed */

        return 1;                                                     /* return error */
    }
    *enable = (bme690_bool_t)((prev >> 4) & 0x01);                    /* set bool */

    return 0;                                                         /* success return 0 */
}

/**
 * @brief      get sub measurement index
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *ind pointer to an index buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub measurement index failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_sub_measurement_index(bme690_handle_t *handle, bme690_section_t section, uint8_t *ind)
{
    uint8_t reg;
    uint8_t prev;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    if (section == BME690_SECTION_0)                                               /* section 0 */
    {
        reg = BME690_REG_SUB_MEAS_INDEX_0;                                         /* set section 0 */
    }
    else if (section == BME690_SECTION_1)                                          /* section 1 */
    {
        reg = BME690_REG_SUB_MEAS_INDEX_1;                                         /* set section 1 */
    }
    else                                                                           /* section 2 */
    {
        reg = BME690_REG_SUB_MEAS_INDEX_2;                                         /* set section 2 */
    }

    if (a_bme690_iic_spi_read(handle, reg, &prev, 1) != 0)                         /* get sub measurement index*/
    {
        handle->debug_print("bme690: get sub measurement index failed.\n");        /* get sub measurement index failed */

        return 1;                                                                  /* return error */
    }
    *ind = prev;                                                                   /* set number */

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief      read the gas resistance
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *adc_raw pointer to an adc raw buffer
 * @param[out] *adc_range pointer to an adc range buffer
 * @param[out] *ohms pointer to an ohms buffer
 * @param[out] *index pointer to a heater index buffer
 * @return     status code
 *             - 0 success
 *             - 1 gas resistance read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate gas resistance failed
 *             - 5 read timeout
 *             - 6 gas is invalid
 *             - 7 heater is not stable
 * @note       none
 */
uint8_t bme690_read_gas_resistance(bme690_handle_t *handle, bme690_section_t section, uint16_t *adc_raw, uint8_t *adc_range, float *ohms, uint8_t *index)
{
    uint8_t res;
    uint8_t reg_status;
    uint8_t reg_gas;
    uint8_t prev;
    uint32_t timeout;
    uint8_t buf[2];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_0;                                                  /* set section 0 */
            reg_status = BME690_REG_MEAS_STATUS_0;                                             /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_1;                                                  /* set section 1 */
            reg_status = BME690_REG_MEAS_STATUS_1;                                             /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_2;                                                  /* set section 2 */
            reg_status = BME690_REG_MEAS_STATUS_2;                                             /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                  /* read gas */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 5)) == 0)                                                          /* check gas valid */
        {
            handle->debug_print("bme690: gas is invalid.\n");                                  /* gas is invalid */

            return 6;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 4)) == 0)                                                          /* check heat */
        {
            handle->debug_print("bme690: heater is not stable.\n");                            /* heater is not stable */

            return 7;                                                                          /* return error */
        }
        *adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                         /* set adc raw */
        *adc_range = buf[1] & 0x0F;                                                            /* set adc range */
        res = a_bme690_compensate_gas_resistance(*adc_raw , *adc_range, ohms);                 /* compensate gas resistance */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate gas resistance failed.\n");                /* compensate gas resistance failed */

            return 4;                                                                          /* return error */
        }
        if (a_bme690_iic_spi_read(handle, reg_status, &prev, 1) != 0)                          /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                              /* read status failed */

            return 1;                                                                          /* return error */
        }
        *index = (prev & 0xF);                                                                 /* set index */
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_0;                                                  /* set section 0 */
            reg_status = BME690_REG_MEAS_STATUS_0;                                             /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_1;                                                  /* set section 1 */
            reg_status = BME690_REG_MEAS_STATUS_1;                                             /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_2;                                                  /* set section 2 */
            reg_status = BME690_REG_MEAS_STATUS_2;                                             /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                  /* read gas */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 5)) == 0)                                                          /* check gas valid */
        {
            handle->debug_print("bme690: gas is invalid.\n");                                  /* gas is invalid */

            return 6;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 4)) == 0)                                                          /* check heat */
        {
            handle->debug_print("bme690: heater is not stable.\n");                            /* heater is not stable */

            return 7;                                                                          /* return error */
        }
        *adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                         /* set adc raw */
        *adc_range = buf[1] & 0x0F;                                                            /* set adc range */
        res = a_bme690_compensate_gas_resistance(*adc_raw , *adc_range, ohms);                 /* compensate gas resistance */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate gas resistance failed.\n");                /* compensate gas resistance failed */

            return 4;                                                                          /* return error */
        }
        if (a_bme690_iic_spi_read(handle, reg_status, &prev, 1) != 0)                          /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                              /* read status failed */

            return 1;                                                                          /* return error */
        }
        *index = (prev & 0xF);                                                                 /* set index */
    }
    
    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      read the pressure data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 pressure read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate pressure failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme690_read_pressure(bme690_handle_t *handle, bme690_section_t section, uint32_t *pressure_raw, float *pressure_pa)
{
    uint8_t res;
    uint8_t reg_press;
    uint8_t prev;
    uint32_t timeout;
    uint32_t temperature_raw;
    float temperature_c;
    uint8_t buf[6];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 6);                                /* read temperature and pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                          (((uint32_t)(buf[4])) << 8) |
                          ((uint32_t)buf[5] << 0));                                            /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, temperature_c, *pressure_raw,
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 6);                                /* read temperature and pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                          (((uint32_t)(buf[4])) << 8) |
                          ((uint32_t)buf[5] << 0));                                            /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, temperature_c, *pressure_raw,
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
    }

    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      read the temperature data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 temperature read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate temperature failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme690_read_temperature(bme690_handle_t *handle, bme690_section_t section, uint32_t *temperature_raw, float *temperature_c)
{
    uint8_t res;
    uint8_t reg_press;
    uint8_t prev;
    uint32_t timeout;
    uint8_t buf[6];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 6);                                /* read temperature and pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 6);                                /* read temperature and pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
    }

    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      read the humidity data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate humidity failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme690_read_humidity(bme690_handle_t *handle, bme690_section_t section, uint32_t *humidity_raw, float *humidity_percentage)
{
    uint8_t res;
    uint8_t reg_press;
    uint8_t prev;
    uint32_t timeout;
    uint32_t temperature_raw;
    float temperature_c;
    uint8_t buf[8];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                          (((uint32_t)(buf[4])) << 8) |
                          ((uint32_t)buf[5] << 0));                                            /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                          (((uint32_t)(buf[4])) << 8) |
                          ((uint32_t)buf[5] << 0));                                            /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
    }

    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      read the temperature pressure and humidity data
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme690_read_temperature_pressure_humidity(bme690_handle_t *handle, bme690_section_t section,
                                                  uint32_t *temperature_raw, float *temperature_c,
                                                  uint32_t *pressure_raw, float *pressure_pa,
                                                  uint32_t *humidity_raw, float *humidity_percentage)
{
    uint8_t res;
    uint8_t reg_press;
    uint8_t prev;
    uint32_t timeout;
    uint8_t buf[8];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, *temperature_c, *pressure_raw,
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, *temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, *temperature_c, *pressure_raw,
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, *temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
    }

    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief      read the temperature pressure humidity and gas resistance
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @param[out] *adc_raw pointer to an adc raw buffer
 * @param[out] *adc_range pointer to an adc range buffer
 * @param[out] *ohms pointer to an ohms buffer
 * @param[out] *index pointer to a heater index buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate failed
 *             - 5 read timeout
 *             - 6 gas is invalid
 *             - 7 heater is not stable
 * @note       none
 */
uint8_t bme690_read(bme690_handle_t *handle, bme690_section_t section,
                    uint32_t *temperature_raw, float *temperature_c,
                    uint32_t *pressure_raw, float *pressure_pa,
                    uint32_t *humidity_raw, float *humidity_percentage,
                    uint16_t *adc_raw, uint8_t *adc_range, float *ohms, uint8_t *index)
{
    uint8_t res;
    uint8_t reg_status;
    uint8_t reg_gas;
    uint8_t reg_press;
    uint8_t prev;
    uint32_t timeout;
    uint8_t buf[8];

    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                    /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                               /* read ctrl meas failed */

        return 1;                                                                              /* return error */
    }
    
    if ((prev & 0x03) != (uint8_t)BME690_MODE_PARALLEL)                                        /* sleep or forced mode */
    {
        if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                /* read ctrl meas */
        {
            handle->debug_print("bme690: read ctrl meas failed.\n");                           /* read ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        prev &= ~(3 << 0);                                                                     /* clear settings */
        prev |= 0x01 << 0;                                                                     /* set forced mode */
        if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)               /* write ctrl meas */
        {
            handle->debug_print("bme690: write ctrl meas failed.\n");                          /* write ctrl meas failed */

            return 1;                                                                          /* return error */
        }
        timeout = 10 * 1000;                                                                   /* set timeout */
        while (timeout != 0)                                                                   /* check timeout */
        {
            if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)            /* read ctrl meas */
            {
                handle->debug_print("bme690: read ctrl meas failed.\n");                       /* read ctrl meas failed */

                return 1;                                                                      /* return error */
            }
            if ((prev & 0x03) == 0)                                                            /* if finished */
            {
                break;                                                                         /* break */
            }
            handle->delay_ms(1);                                                               /* delay 1ms */
            timeout--;                                                                         /* timeout-- */
        }
        if (timeout == 0)                                                                      /* check timeout */
        {
            handle->debug_print("bme690: read timeout.\n");                                    /* read timeout */

            return 5;                                                                          /* return error */
        }
        
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_0;                                                  /* set section 0 */
            reg_status = BME690_REG_MEAS_STATUS_0;                                             /* set section 0 */
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_1;                                                  /* set section 1 */
            reg_status = BME690_REG_MEAS_STATUS_1;                                             /* set section 1 */
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_2;                                                  /* set section 2 */
            reg_status = BME690_REG_MEAS_STATUS_2;                                             /* set section 2 */
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, *temperature_c, *pressure_raw, 
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, *temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                  /* read gas */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 5)) == 0)                                                          /* check gas valid */
        {
            handle->debug_print("bme690: gas is invalid.\n");                                  /* gas is invalid */

            return 6;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 4)) == 0)                                                          /* check heat */
        {
            handle->debug_print("bme690: heater is not stable.\n");                            /* heater is not stable */

            return 7;                                                                          /* return error */
        }
        *adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                         /* set adc raw */
        *adc_range = buf[1] & 0x0F;                                                            /* set adc range */
        res = a_bme690_compensate_gas_resistance(*adc_raw , *adc_range, ohms);                 /* compensate gas resistance */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate gas resistance failed.\n");                /* compensate gas resistance failed */

            return 4;                                                                          /* return error */
        }
        if (a_bme690_iic_spi_read(handle, reg_status, &prev, 1) != 0)                          /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                              /* read status failed */

            return 1;                                                                          /* return error */
        }
        *index = (prev & 0xF);                                                                 /* set index */
    }
    else
    {
        if (section == BME690_SECTION_0)                                                       /* section 0 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_0;                                                  /* set section 0 */
            reg_status = BME690_REG_MEAS_STATUS_0;                                             /* set section 0 */
            reg_press = BME690_REG_PRESS_MSB_0;                                                /* set section 0 */
        }
        else if (section == BME690_SECTION_1)                                                  /* section 1 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_1;                                                  /* set section 1 */
            reg_status = BME690_REG_MEAS_STATUS_1;                                             /* set section 1 */
            reg_press = BME690_REG_PRESS_MSB_1;                                                /* set section 1 */
        }
        else                                                                                   /* section 2 */
        {
            reg_gas = BME690_REG_GAS_R_MSB_2;                                                  /* set section 2 */
            reg_status = BME690_REG_MEAS_STATUS_2;                                             /* set section 2 */
            reg_press = BME690_REG_PRESS_MSB_2;                                                /* set section 2 */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                /* read temperature pressure and humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        *temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                           (((uint32_t)(buf[4])) << 8) |
                           ((uint32_t)buf[5] << 0));                                           /* set temperature raw */
        res = a_bme690_compensate_temperature(handle, *temperature_raw, temperature_c);        /* compensate temperature */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate temperature failed.\n");                   /* compensate temperature failed */

            return 4;                                                                          /* return error */
        }
        *pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                        (((uint32_t)(buf[1])) << 8) |
                        (((uint32_t)(buf[2])) << 0));                                          /* set pressure raw */
        res = a_bme690_compensate_pressure(handle, *temperature_c, *pressure_raw,
                                           pressure_pa);                                       /* compensate pressure */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate pressure failed.\n");                      /* compensate pressure failed */

            return 4;                                                                          /* return error */
        }
        *humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                        /* set humidity raw */
        res = a_bme690_compensate_humidity(handle, *temperature_c, *humidity_raw,
                                           humidity_percentage);                               /* compensate humidity */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate humidity failed.\n");                      /* compensate humidity failed */

            return 4;                                                                          /* return error */
        }
        
        res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                  /* read gas */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: read failed.\n");                                     /* read failed */

            return 1;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 5)) == 0)                                                          /* check gas valid */
        {
            handle->debug_print("bme690: gas is invalid.\n");                                  /* gas is invalid */

            return 6;                                                                          /* return error */
        }
        if ((buf[1] & (1 << 4)) == 0)                                                          /* check heat */
        {
            handle->debug_print("bme690: heater is not stable.\n");                            /* heater is not stable */

            return 7;                                                                          /* return error */
        }
        *adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                         /* set adc raw */
        *adc_range = buf[1] & 0x0F;                                                            /* set adc range */
        res = a_bme690_compensate_gas_resistance(*adc_raw , *adc_range, ohms);                 /* compensate gas resistance */
        if (res != 0)                                                                          /* check result */
        {
            handle->debug_print("bme690: compensate gas resistance failed.\n");                /* compensate gas resistance failed */

            return 4;                                                                          /* return error */
        }
        if (a_bme690_iic_spi_read(handle, reg_status, &prev, 1) != 0)                          /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                              /* read status failed */

            return 1;                                                                          /* return error */
        }
        *index = (prev & 0xF);                                                                 /* set index */
    }
    
    return 0;                                                                                  /* success return 0 */
}

/**
 * @brief     parallel progress
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 parallel progress failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not parallel mode
 *            - 5 not ready
 *            - 6 index is invalid
 *            - 7 compensate failed
 *            - 8 gas is invalid
 * @note      none
 */
uint8_t bme690_parallel_progress(bme690_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_MEAS, &prev, 1) != 0)                            /* read ctrl meas */
    {
        handle->debug_print("bme690: read ctrl meas failed.\n");                                       /* read ctrl meas failed */

        return 1;                                                                                      /* return error */
    }
    
    if ((prev & 0x03) == (uint8_t)BME690_MODE_PARALLEL)                                                /* parallel mode */
    {
        uint8_t reg;
        uint8_t trigger;
        uint8_t prev0;
        uint8_t prev1;
        uint8_t prev2;
        uint8_t index0;
        uint8_t index1;
        uint8_t index2;
        uint8_t reg_gas;
        uint8_t reg_press;
        uint8_t reg_sub;
        uint8_t buf[8];
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_pa;
        uint32_t humidity_raw;
        float humidity_percentage;
        uint16_t adc_raw;
        uint8_t adc_range;
        float ohms;
        uint8_t ind;
            
        if (a_bme690_iic_spi_read(handle, BME690_REG_MEAS_STATUS_0, &prev0, 1) != 0)                   /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                                      /* read status failed */

            return 1;                                                                                  /* return error */
        }
        if (a_bme690_iic_spi_read(handle, BME690_REG_MEAS_STATUS_1, &prev1, 1) != 0)                   /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                                      /* read status failed */

            return 1;                                                                                  /* return error */
        }
        if (a_bme690_iic_spi_read(handle, BME690_REG_MEAS_STATUS_2, &prev2, 1) != 0)                   /* read status */
        {
            handle->debug_print("bme690: read status failed.\n");                                      /* read status failed */

            return 1;                                                                                  /* return error */
        }
        
        trigger = 0;                                                                                   /* init 0 */
        if (((prev0 >> 7) & 0x01) != 0)                                                                /* check output */
        {
            trigger = 1;                                                                               /* init 1 */
            index0 = prev0 & 0xF;                                                                      /* set index 0 */
            if (index0 > 9)                                                                            /* check index */
            {
                handle->debug_print("bme690: index is invalid.\n");                                    /* index is invalid */

                return 6;                                                                              /* return error */
            }
            
            reg_gas = BME690_REG_GAS_R_MSB_0;                                                          /* set section 0 */
            reg_press = BME690_REG_PRESS_MSB_0;                                                        /* set section 0 */
            reg_sub = BME690_REG_SUB_MEAS_INDEX_0;                                                     /* set section 0 */
            ind = index0;                                                                              /* set section 0 */
            
            res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                    /* read temperature pressure and humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                               (((uint32_t)(buf[4])) << 8) |
                               ((uint32_t)buf[5] << 0));                                               /* set temperature raw */
            res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);            /* compensate temperature */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate temperature failed.\n");                       /* compensate temperature failed */

                return 7;                                                                              /* return error */
            }
            pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                            (((uint32_t)(buf[1])) << 8) |
                            (((uint32_t)(buf[2])) << 0));                                              /* set pressure raw */
            res = a_bme690_compensate_pressure(handle, temperature_c, pressure_raw,
                                               &pressure_pa);                                          /* compensate pressure */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate pressure failed.\n");                          /* compensate pressure failed */

                return 7;                                                                              /* return error */
            }
            humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                             /* set humidity raw */
            res = a_bme690_compensate_humidity(handle, temperature_c, humidity_raw,
                                               &humidity_percentage);                                  /* compensate humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate humidity failed.\n");                          /* compensate humidity failed */

                return 7;                                                                              /* return error */
            }
            
            res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                      /* read gas */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                              /* set adc raw */
            adc_range = buf[1] & 0x0F;                                                                 /* set adc range */
            res = a_bme690_compensate_gas_resistance(adc_raw , adc_range, &ohms);                      /* compensate gas resistance */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate gas resistance failed.\n");                    /* compensate gas resistance failed */

                return 7;                                                                              /* return error */
            }
            res = a_bme690_iic_spi_read(handle, reg_sub, &reg, 1);                                     /* read sub index */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            if (handle->parallel_sequence_trigger[0] == 0)                                             /* check trigger */
            {
                handle->parallel_sequence_number[0] = reg;                                             /* set sequence number */
            }
            else
            {
                if ((uint16_t)(handle->parallel_sequence_number[0] + 3) > 255)                         /* set sequence number */
                {
                    reg = (uint8_t)(handle->parallel_sequence_number[0] + 3);                          /* reset to new data */
                }
                if (reg != (uint8_t)(handle->parallel_sequence_number[0] + 3))                         /* check sequence number */
                {
                    handle->debug_print("bme690: sequence is lost.\n");                                /* sequence is lost */
                    if (handle->receive_callback != NULL)                                              /* not null */
                    {
                        handle->receive_callback((uint8_t)BME690_STATUS_SEQUENCE_LOST, 
                                                  NULL, 0);                                            /* run the callback */
                    }
                    
                    return 10;                                                                         /* return error */
                }
            }
            handle->parallel_sequence_trigger[0] = 1;                                                  /* set trigger */
            handle->parallel_sequence_number[0] = reg;                                                 /* set sequence number */
            if ((buf[1] & (1 << 5)) == 0)                                                              /* check gas valid */
            {
                goto step1;                                                                            /* goto step1 */
            }
            if ((buf[1] & (1 << 4)) == 0)                                                              /* check heat */
            {
                goto step1;                                                                            /* goto step1 */
            }
            handle->parallel_data[ind].channel = ind;                                                  /* set channel */
            handle->parallel_data[ind].temperature_raw = temperature_raw;                              /* set temperature raw */
            handle->parallel_data[ind].temperature_c = temperature_c;                                  /* set temperature */
            handle->parallel_data[ind].pressure_raw = pressure_raw;                                    /* set pressure raw */
            handle->parallel_data[ind].pressure_pa = pressure_pa;                                      /* set pressure */
            handle->parallel_data[ind].humidity_raw = humidity_raw;                                    /* set humidity raw */
            handle->parallel_data[ind].humidity_percentage = humidity_percentage;                      /* set humidity */
            handle->parallel_data[ind].adc_raw = adc_raw;                                              /* set adc raw */
            handle->parallel_data[ind].adc_range = adc_range;                                          /* set adc range */
            handle->parallel_data[ind].ohms = ohms;                                                    /* set ohms */
            handle->parallel_data_flag |= 1 << ind;                                                    /* set flag */
            if (handle->receive_callback != NULL)                                                      /* not null */
            {
                handle->receive_callback((uint8_t)BME690_STATUS_CHANNEL_DATA, 
                                          &handle->parallel_data[ind], 1);                             /* run the callback */
            }
        }
        
        step1:
        if (((prev1 >> 7) & 0x01) != 0)                                                                /* check output */
        {
            trigger = 1;                                                                               /* init 1 */
            index1 = prev1 & 0xF;                                                                      /* set index 1 */
            if (index1 > 9)                                                                            /* check index */
            {
                handle->debug_print("bme690: index is invalid.\n");                                    /* index is invalid */

                return 6;                                                                              /* return error */
            }
            
            reg_gas = BME690_REG_GAS_R_MSB_1;                                                          /* set section 1 */
            reg_press = BME690_REG_PRESS_MSB_1;                                                        /* set section 1 */
            reg_sub = BME690_REG_SUB_MEAS_INDEX_1;                                                     /* set section 1 */
            ind = index1;                                                                              /* set section 1 */
            
            res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                    /* read temperature pressure and humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                               (((uint32_t)(buf[4])) << 8) |
                               ((uint32_t)buf[5] << 0));                                               /* set temperature raw */
            res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);            /* compensate temperature */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate temperature failed.\n");                       /* compensate temperature failed */

                return 7;                                                                              /* return error */
            }
            pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                            (((uint32_t)(buf[1])) << 8) |
                            (((uint32_t)(buf[2])) << 0));                                              /* set pressure raw */
            res = a_bme690_compensate_pressure(handle, temperature_c, pressure_raw,
                                               &pressure_pa);                                          /* compensate pressure */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate pressure failed.\n");                          /* compensate pressure failed */

                return 7;                                                                              /* return error */
            }
            humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                             /* set humidity raw */
            res = a_bme690_compensate_humidity(handle, temperature_c, humidity_raw,
                                               &humidity_percentage);                                  /* compensate humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate humidity failed.\n");                          /* compensate humidity failed */

                return 7;                                                                              /* return error */
            }
            
            res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                      /* read gas */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                              /* set adc raw */
            adc_range = buf[1] & 0x0F;                                                                 /* set adc range */
            res = a_bme690_compensate_gas_resistance(adc_raw , adc_range, &ohms);                      /* compensate gas resistance */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate gas resistance failed.\n");                    /* compensate gas resistance failed */

                return 7;                                                                              /* return error */
            }
            res = a_bme690_iic_spi_read(handle, reg_sub, &reg, 1);                                     /* read sub index */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            if (handle->parallel_sequence_trigger[1] == 0)                                             /* check trigger */
            {
                handle->parallel_sequence_number[1] = reg;                                             /* set sequence number */
            }
            else
            {
                if ((uint16_t)(handle->parallel_sequence_number[1] + 3) > 255)                         /* set sequence number */
                {
                    reg = (uint8_t)(handle->parallel_sequence_number[1] + 3);                          /* reset to new data */
                }
                if (reg != (uint8_t)(handle->parallel_sequence_number[1] + 3))                         /* check sequence number */
                {
                    handle->debug_print("bme690: sequence is lost.\n");                                /* sequence is lost */
                    if (handle->receive_callback != NULL)                                              /* not null */
                    {
                        handle->receive_callback((uint8_t)BME690_STATUS_SEQUENCE_LOST, 
                                                  NULL, 0);                                            /* run the callback */
                    }
                    
                    return 10;                                                                         /* return error */
                }
            }
            handle->parallel_sequence_trigger[1] = 1;                                                  /* set trigger */
            handle->parallel_sequence_number[1] = reg;                                                 /* set sequence number */
            if ((buf[1] & (1 << 5)) == 0)                                                              /* check gas valid */
            {
                goto step2;                                                                            /* goto step1 */
            }
            if ((buf[1] & (1 << 4)) == 0)                                                              /* check heat */
            {
                goto step2;                                                                            /* goto step1 */
            }
            handle->parallel_data[ind].channel = ind;                                                  /* set channel */
            handle->parallel_data[ind].temperature_raw = temperature_raw;                              /* set temperature raw */
            handle->parallel_data[ind].temperature_c = temperature_c;                                  /* set temperature */
            handle->parallel_data[ind].pressure_raw = pressure_raw;                                    /* set pressure raw */
            handle->parallel_data[ind].pressure_pa = pressure_pa;                                      /* set pressure */
            handle->parallel_data[ind].humidity_raw = humidity_raw;                                    /* set humidity raw */
            handle->parallel_data[ind].humidity_percentage = humidity_percentage;                      /* set humidity */
            handle->parallel_data[ind].adc_raw = adc_raw;                                              /* set adc raw */
            handle->parallel_data[ind].adc_range = adc_range;                                          /* set adc range */
            handle->parallel_data[ind].ohms = ohms;                                                    /* set ohms */
            handle->parallel_data_flag |= 1 << ind;                                                    /* set flag */
            if (handle->receive_callback != NULL)                                                      /* not null */
            {
                handle->receive_callback((uint8_t)BME690_STATUS_CHANNEL_DATA, 
                                          &handle->parallel_data[ind], 1);                             /* run the callback */
            }
        }
        
        step2:
        if (((prev2 >> 7) & 0x01) != 0)                                                                /* check output */
        {
            trigger = 1;                                                                               /* init 1 */
            index2 = prev2 & 0xF;                                                                      /* set index 2 */
            if (index2 > 9)                                                                            /* check index */
            {
                handle->debug_print("bme690: index is invalid.\n");                                    /* index is invalid */

                return 6;                                                                              /* return error */
            }
            
            reg_gas = BME690_REG_GAS_R_MSB_2;                                                          /* set section 2 */
            reg_press = BME690_REG_PRESS_MSB_2;                                                        /* set section 2 */
            reg_sub = BME690_REG_SUB_MEAS_INDEX_2;                                                     /* set section 2 */
            ind = index2;                                                                              /* set section 2 */
            
            res = a_bme690_iic_spi_read(handle, reg_press, buf, 8);                                    /* read temperature pressure and humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            temperature_raw = ((((uint32_t)(buf[3])) << 16) |
                               (((uint32_t)(buf[4])) << 8) |
                               ((uint32_t)buf[5] << 0));                                               /* set temperature raw */
            res = a_bme690_compensate_temperature(handle, temperature_raw, &temperature_c);            /* compensate temperature */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate temperature failed.\n");                       /* compensate temperature failed */

                return 7;                                                                              /* return error */
            }
            pressure_raw = ((((uint32_t)(buf[0])) << 16) |
                            (((uint32_t)(buf[1])) << 8) |
                            (((uint32_t)(buf[2])) << 0));                                              /* set pressure raw */
            res = a_bme690_compensate_pressure(handle, temperature_c, pressure_raw,
                                               &pressure_pa);                                          /* compensate pressure */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate pressure failed.\n");                          /* compensate pressure failed */

                return 7;                                                                              /* return error */
            }
            humidity_raw = (uint32_t)buf[6] << 8 | buf[7];                                             /* set humidity raw */
            res = a_bme690_compensate_humidity(handle, temperature_c, humidity_raw,
                                               &humidity_percentage);                                  /* compensate humidity */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate humidity failed.\n");                          /* compensate humidity failed */

                return 7;                                                                              /* return error */
            }
            
            res = a_bme690_iic_spi_read(handle, reg_gas, buf, 2);                                      /* read gas */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            adc_raw = (((uint16_t)buf[0]) << 2) | ((buf[1] >> 6) & 0x03);                              /* set adc raw */
            adc_range = buf[1] & 0x0F;                                                                 /* set adc range */
            res = a_bme690_compensate_gas_resistance(adc_raw , adc_range, &ohms);                      /* compensate gas resistance */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: compensate gas resistance failed.\n");                    /* compensate gas resistance failed */

                return 7;                                                                              /* return error */
            }
            res = a_bme690_iic_spi_read(handle, reg_sub, &reg, 1);                                     /* read sub index */
            if (res != 0)                                                                              /* check result */
            {
                handle->debug_print("bme690: read failed.\n");                                         /* read failed */

                return 1;                                                                              /* return error */
            }
            if (handle->parallel_sequence_trigger[2] == 0)                                             /* check trigger */
            {
                handle->parallel_sequence_number[2] = reg;                                             /* set sequence number */
            }
            else
            {
                if ((uint16_t)(handle->parallel_sequence_number[2] + 3) > 255)                         /* set sequence number */
                {
                    reg = (uint8_t)(handle->parallel_sequence_number[2] + 3);                          /* reset to new data */
                }
                if (reg != (uint8_t)(handle->parallel_sequence_number[2] + 3))                         /* check sequence number */
                {
                    handle->debug_print("bme690: sequence is lost.\n");                                /* sequence is lost */
                    if (handle->receive_callback != NULL)                                              /* not null */
                    {
                        handle->receive_callback((uint8_t)BME690_STATUS_SEQUENCE_LOST, 
                                                  NULL, 0);                                            /* run the callback */
                    }
                    
                    return 10;                                                                         /* return error */
                }
            }
            handle->parallel_sequence_trigger[2] = 1;                                                  /* set trigger */
            handle->parallel_sequence_number[2] = reg;                                                 /* set sequence number */
            if ((buf[1] & (1 << 5)) == 0)                                                              /* check gas valid */
            {
                goto step3;                                                                            /* dummy gas slot, skip it */
            }
            if ((buf[1] & (1 << 4)) == 0)                                                              /* check heat */
            {
                goto step3;                                                                            /* dummy gas slot, skip it */
            }
            handle->parallel_data[ind].channel = ind;                                                  /* set channel */
            handle->parallel_data[ind].temperature_raw = temperature_raw;                              /* set temperature raw */
            handle->parallel_data[ind].temperature_c = temperature_c;                                  /* set temperature */
            handle->parallel_data[ind].pressure_raw = pressure_raw;                                    /* set pressure raw */
            handle->parallel_data[ind].pressure_pa = pressure_pa;                                      /* set pressure */
            handle->parallel_data[ind].humidity_raw = humidity_raw;                                    /* set humidity raw */
            handle->parallel_data[ind].humidity_percentage = humidity_percentage;                      /* set humidity */
            handle->parallel_data[ind].adc_raw = adc_raw;                                              /* set adc raw */
            handle->parallel_data[ind].adc_range = adc_range;                                          /* set adc range */
            handle->parallel_data[ind].ohms = ohms;                                                    /* set ohms */
            handle->parallel_data_flag |= 1 << ind;                                                    /* set flag */
            if (handle->receive_callback != NULL)                                                      /* not null */
            {
                handle->receive_callback((uint8_t)BME690_STATUS_CHANNEL_DATA, 
                                          &handle->parallel_data[ind], 1);                             /* run the callback */
            }
        }
        step3:
        if (a_bme690_calculate_parallel_counter(handle) >= handle->parallel_data_len)                  /* check parallel counter */
        {
            if (handle->receive_callback != NULL)                                                      /* not null */
            {
                handle->receive_callback((uint8_t)BME690_STATUS_ALL_DATA, 
                                          &handle->parallel_data[0], 
                                          handle->parallel_data_len);                                  /* run the callback */
            }
            handle->parallel_data_flag = 0;                                                            /* init 0 */
        }
        if (trigger == 0)                                                                              /* check trigger */
        {
            return 5;                                                                                  /* return not ready */
        }
        
        return 0;                                                                                      /* success return 0 */
    }
    else
    {
        handle->debug_print("bme690: not parallel mode.\n");                                           /* not parallel mode */
        
        return 4;                                                                                      /* return error */
    }
}

/**
 * @brief     parallel reset
 * @param[in] *handle pointer to a bme690 handle structure
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_parallel_reset(bme690_handle_t *handle)
{
    uint8_t i;

    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }
    
    for (i = 0; i < 3; i++)                              /* set all 0 */
    {
        handle->parallel_sequence_trigger[i] = 0;        /* init 0 */
        handle->parallel_sequence_number[i] = 0;         /* init 0 */
    }
    handle->parallel_data_flag = 0;                      /* flag init 0 */

    return 0;                                            /* success return 0 */
}

/**
 * @brief     parallel config
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] *config pointer to a bme690 parallel config structure
 * @return    status code
 *            - 0 success
 *            - 1 parallel config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 config is invalid
 *            - 5 profile_len > 10
 *            - 6 ms > 0x0783
 * @note      none
 */
uint8_t bme690_parallel_config(bme690_handle_t *handle, bme690_parallel_config_t *config)
{
    uint8_t prev;
    uint8_t i;
    uint8_t factor;
    uint16_t ms;

    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (config == NULL)                                                                   /* check config */
    {
        handle->debug_print("bme690: config is invalid.\n");                              /* config is invalid */
        
        return 4;                                                                         /* return error */
    }
    if ((config->heater_dur_prof == NULL) || (config->heater_temp_prof == NULL))          /* check config */
    {
        handle->debug_print("bme690: config is invalid.\n");                              /* config is invalid */
        
        return 4;                                                                         /* return error */
    }
    if (config->profile_len > 10)                                                         /* check profile length */
    {
        handle->debug_print("bme690: profile_len > 10.\n");                               /* profile_len > 10 */
        
        return 5;                                                                         /* return error */
    }
    
    for (i = 0; i < config->profile_len; i++)                                             /* set all profile */
    {
        (void)a_bme690_compensate_heat(handle, config->heater_temp_prof[i], &prev);       /* convert real data to register data */
        if (a_bme690_iic_spi_write(handle, BME690_REG_RES_HEAT_X + i, &prev, 1) != 0)     /* write resistance heat */
        {
            handle->debug_print("bme690: write resistance heat failed.\n");               /* write resistance heat failed */

            return 1;                                                                     /* return error */
        }
        
        prev = config->heater_dur_prof[i];                                                /* set wait */
        if (a_bme690_iic_spi_write(handle, BME690_REG_GAS_WAIT_X + i, &prev, 1) != 0)     /* write gas wait */
        {
            handle->debug_print("bme690: write gas wait failed.\n");                      /* write gas wait failed */

            return 1;                                                                     /* return error */
        }
    }
    
    factor = 0;                                                                           /* init 0 */
    ms = (uint16_t)config->shared_heater_dur;                                             /* set ms */
    if (ms > 0x0783U)                                                                     /* check ms */
    {
        handle->debug_print("bme690: ms > 0x0783.\n");                                    /* ms > 0x0783 */

        return 6;                                                                         /* return error */
    }
    else
    {
        ms = (uint16_t)(((uint32_t)ms * 1000) / 477);                                     /* set ms */
        while (ms > 0x3F)                                                                 /* check ms */
        {
            ms = ms >> 2;                                                                 /* right shift 2 */
            factor += 1;                                                                  /* add 1 */
        }
        
        prev = (uint8_t)(ms + (factor * 64));                                             /* set param */
    }
    
    if (a_bme690_iic_spi_write(handle, BME690_REG_GAS_WAIT_SHARED, &prev, 1) != 0)        /* write gas wait shared */
    {
        handle->debug_print("bme690: write gas wait shared failed.\n");                   /* write gas wait shared failed */

        return 1;                                                                         /* return error */
    }
    
    if (a_bme690_iic_spi_read(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)              /* read ctrl gas1 */
    {
        handle->debug_print("bme690: read ctrl gas1 failed.\n");                          /* read ctrl gas1 failed */

        return 1;                                                                         /* return error */
    }
    prev &= ~(0x0F << 0);                                                                 /* clear settings */
    prev |= (config->profile_len & 0x0F) << 0;                                            /* set profile */
    if (a_bme690_iic_spi_write(handle, BME690_REG_CTRL_GAS_1, &prev, 1) != 0)             /* write ctrl gas1 */
    {
        handle->debug_print("bme690: write ctrl gas1 failed.\n");                         /* write ctrl gas1 failed */

        return 1;                                                                         /* return error */
    }
    handle->parallel_data_len = config->profile_len;                                      /* set parallel data length */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set ambient temperature
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] amb_temp_c ambient temperature in C
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_ambient_temperature(bme690_handle_t *handle, int8_t amb_temp_c)
{
    if (handle == NULL)                   /* check handle */
    {
        return 2;                         /* return error */
    }
    if (handle->inited != 1)              /* check handle initialization */
    {
        return 3;                         /* return error */
    }
    
    handle->amb_temp = amb_temp_c;        /* set ambient temperature */
    
    return 0;                             /* success return 0 */
}

/**
 * @brief      get ambient temperature
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[out] *amb_temp_c pointer to an ambient temperature buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_ambient_temperature(bme690_handle_t *handle, int8_t *amb_temp_c)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    *amb_temp_c = handle->amb_temp;        /* set ambient temperature */
    
    return 0;                              /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a bme690 handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme690_set_reg(bme690_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    return a_bme690_iic_spi_write(handle, reg, buf, len);       /* write register */
}

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a bme690 handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme690_get_reg(bme690_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }

    return a_bme690_iic_spi_read(handle, reg, buf, len);       /* read register */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a bme690 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme690_info(bme690_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(bme690_info_t));                         /* initialize bme690 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC SPI", 8);                         /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
