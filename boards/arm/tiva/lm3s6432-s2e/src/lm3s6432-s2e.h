/****************************************************************************
 * boards/arm/tiva/lm3s6432-s2e/src/lm3s6432-s2e.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_TIVA_LM3S6432_S2E_SRC_LM3S6432_S2E_H
#define __BOARDS_ARM_TIVA_LM3S6432_S2E_SRC_LM3S6432_S2E_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include "chip.h"
#include "tiva_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* How many SSI modules does this chip support?
 * The LM3S6432 supports 1 SSI module
 * (others may support more than 2 -- in such case, the following must be
 * expanded).
 */

#if TIVA_NSSI == 0
#  undef CONFIG_TIVA_SSI0
#endif
#undef CONFIG_TIVA_SSI1

/* LM3S6432 MDL-S2E *********************************************************/

/* GPIO Usage
 *
 * PIN SIGNAL            S2E Function
 * --- ----------------- ---------------------------------------
 *  L3 PA0/U0RX          Virtual COM port receive
 *  M3 PA1/U0TX          Virtual COM port transmit
 * E12 PB0/U0CTS         Virtual COM port CTS
 * D12 PB1/U0RTS         Virtual COM port RTS
 *  L5 PA4/SPIRX         SPI receive
 *  M5 PA5/SPITX         SPI transmit
 *  H2 PD2/U1RX          Virtual COM port receive
 *  H1 PD3/U1TX          Virtual COM port transmit
 *  L4 PA3/U1CTS/SPICLK  Virtual COM port CTS
 *  M4 PA2/U1RTS/SPISEL  Virtual COM port RTS
 * J11 PF0/LED1          Ethernet LED1 (green)
 * J12 PF1/LED0          Ethernet LED0 (yellow)
 * C11 PB2               Transceiver #INVALID
 * C12 PB3               Transceiver #ENABLE
 *  A6 PB4               Transceiver ON
 *  B7 PB5               Transceiver #OFF
 */

/* GPIO for LEDs:
 * - PF0: User LED
 */

#define LED1_GPIO     (GPIO_FUNC_OUTPUT | GPIO_VALUE_ONE  | GPIO_PORTF | 2)
#define LED0_GPIO     (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTF | 3)

/* GPIO for SSI0 select
 */
#define SSICS_GPIO    (GPIO_FUNC_OUTPUT | GPIO_VALUE_ONE | GPIO_PORTA | 3)

/* GPIOs for the RS-232 transceiver enable/disable.
 * Default state for these enables the transceiver.
 */
#define XCVR_INV_GPIO (GPIO_FUNC_INPUT | GPIO_PORTB | 2)
#define XCVR_ENA_GPIO (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTB | 3)
#define XCVR_ON_GPIO  (GPIO_FUNC_OUTPUT | GPIO_VALUE_ONE  | GPIO_PORTB | 4)
#define XCVR_OFF_GPIO (GPIO_FUNC_OUTPUT | GPIO_VALUE_ONE  | GPIO_PORTB | 5)

/****************************************************************************
 * Public Functions Definitions
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Name: lm_ssidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the MDL-S2E.
 *
 ****************************************************************************/

void weak_function lm_ssidev_initialize(void);

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_TIVA_LM3S6432_S2E_SRC_LM3S6432_S2E_H */
