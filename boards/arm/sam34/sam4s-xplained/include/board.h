/****************************************************************************
 * boards/arm/sam34/sam4s-xplained/include/board.h
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

#ifndef __BOARDS_ARM_SAM34_SAM4S_XPLAINED_INCLUDE_BOARD_H
#define __BOARDS_ARM_SAM34_SAM4S_XPLAINED_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  ifdef CONFIG_SAM34_GPIO_IRQ
#    include <arch/irq.h>
#  endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* After power-on reset, the sam3u device is running on a 4MHz internal RC.
 * These definitions will configure clocking with MCK = 48MHz, PLLA = 96,
 * and CPU=120MHz.
 */

/* Main oscillator register settings */

#define BOARD_CKGR_MOR_MOSCXTST    (63 << PMC_CKGR_MOR_MOSCXTST_SHIFT) /* Start-up Time */

/* PLLA configuration:
 *
 * Source: 12MHz crystall at 12MHz
 * PLLdiv: 10
 * PLLmul: 1 (bypassed)
 * Fpll:   (12MHz * 10) / 1 = 120MHz
 */

#define BOARD_MAINOSC_FREQUENCY    (12000000)
#define BOARD_CKGR_PLLAR_MUL       (9 << PMC_CKGR_PLLAR_MUL_SHIFT)
#define BOARD_CKGR_PLLAR_DIV       PMC_CKGR_PLLAR_DIV_BYPASS
#define BOARD_CKGR_PLLAR_COUNT     (63 << PMC_CKGR_PLLAR_COUNT_SHIFT)
#define BOARD_PLLA_FREQUENCY       (10*BOARD_MAINOSC_FREQUENCY)

/* PMC master clock register settings */

#define BOARD_PMC_MCKR_CSS         PMC_MCKR_CSS_PLLA
#define BOARD_PMC_MCKR_PRES        PMC_MCKR_PRES_DIV1
#define BOARD_MCK_FREQUENCY        (BOARD_PLLA_FREQUENCY/1)
#define BOARD_CPU_FREQUENCY        (BOARD_PLLA_FREQUENCY/1)

/* USB UTMI PLL start-up time */

#define BOARD_CKGR_UCKR_UPLLCOUNT  (3 << PMC_CKGR_UCKR_UPLLCOUNT_SHIFT)

/* HSMCI clocking
 *
 * Multimedia Card Interface clock (MCCK or MCI_CK) is Master Clock (MCK)
 * divided by (2*(CLKDIV+1)).
 *
 *   MCI_SPEED = MCK / (2*(CLKDIV+1))
 *   CLKDIV = MCI / MCI_SPEED / 2 - 1
 */

/* MCK = 48MHz, CLKDIV = 59, MCI_SPEED = 48MHz / 2 * (59+1) = 400 KHz */

#define HSMCI_INIT_CLKDIV          (59 << HSMCI_MR_CLKDIV_SHIFT)

/* MCK = 48MHz, CLKDIV = 1, MCI_SPEED = 48MHz / 2 * (1+1) = 12 MHz */

#define HSMCI_MMCXFR_CLKDIV        (1 << HSMCI_MR_CLKDIV_SHIFT)

/* MCK = 48MHz, CLKDIV = 0, MCI_SPEED = 48MHz / 2 * (0+1) = 24 MHz */

#define HSMCI_SDXFR_CLKDIV         (0 << HSMCI_MR_CLKDIV_SHIFT)
#define HSMCI_SDWIDEXFR_CLKDIV     HSMCI_SDXFR_CLKDIV

/* FLASH wait states:
 *
 * DC Characteristics
 *
 * Parameter              Min   Typ  Max
 * ---------------------- ----- ----- ----
 * Vddcore DC Supply Core 1.08V 1.2V 1.32V
 * Vvddio  DC Supply I/Os 1.62V 3.3V 3.6V
 *
 *                     Wait   Maximum
 * Vddcore   Vvddio   States Frequency (MHz)
 * ------- ---------- ------ ---------------
 * 1.08V   1.62-3.6V    0        16
 * "   "   "  "-"  "    1        33
 * "   "   "  "-"  "    2        50
 * "   "   "  "-"  "    3        67
 * "   "   "  "-"  "    4        84
 * "   "   "  "-"  "    5       100
 * 1.08V   2.7-3.6V     0        20
 * "   "   " "-"  "     1        40
 * "   "   " "-"  "     2        60
 * "   "   " "-"  "     3        80
 * "   "   " "-"  "     4       100
 * 1.2V    1.62-3.6V    0        17
 * "  "    " "-"  "     1        34
 * "  "    " "-"  "     2        52
 * "  "    " "-"  "     3        69
 * "  "    " "-"  "     4        87
 * "  "    " "-"  "     5       104
 * "  "    " "-"  "     6       121
 * 1.2V    2.7-3.6V     0        21
 * "  "    " "-"  "     1        42
 * "  "    " "-"  "     2        63
 * "  "    " "-"  "     3        84
 * "  "    " "-"  "     4       105
 * "  "    " "-"  "     5       123 << SELECTION
 */

#define BOARD_FWS                  5

/* LED definitions **********************************************************/

/* There are four LEDs on board the SAM4S Xplained board, two of these can be
 * controlled by software in the SAM4S:
 *
 *   LED              GPIO
 *   ---------------- -----
 *   D9  Yellow LED   PC10
 *   D10 Yellow LED   PC17
 *
 * Both can be illuminated by driving the GPIO output to ground (low).
 */

/* LED index values for use with board_userled() */

#define BOARD_D9             0
#define BOARD_D10            1
#define BOARD_NLEDS          2

/* LED bits for use with board_userled_all() */

#define BOARD_D9_BIT         (1 << BOARD_D9)
#define BOARD_D10_BIT        (1 << BOARD_D10)

/* These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/up_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *   SYMBOL                Val  Meaning                      LED state
 *                                                          D9       D10
 * ----------------------- ---  -----------------------  -------- --------
 */

#define LED_STARTED          0 /* NuttX has been started    OFF      OFF      */
#define LED_HEAPALLOCATE     0 /* Heap has been allocated   OFF      OFF      */
#define LED_IRQSENABLED      0 /* Interrupts enabled        OFF      OFF      */
#define LED_STACKCREATED     0 /* Idle stack created        ON       OFF      */
#define LED_INIRQ            0 /* In an interrupt             No change       */
#define LED_SIGNAL           0 /* In a signal handler         No change       */
#define LED_ASSERTION        0 /* An assertion failed         No change       */
#define LED_PANIC            0 /* The system has crashed    OFF      Blinking */
#define LED_IDLE             0 /* MCU is is sleep mode        Not used        */

/* Thus if D9 is statically on, NuttX has successfully booted and is,
 * apparently, running normmally.  If D10 is flashing at approximately
 * 2Hz, then a fatal error has been detected and the system has halted.
 */

/* Button definitions *******************************************************/

/* Mechanical buttons:
 *
 * The SAM4S Xplained has two mechanical buttons.
 * One button is the RESET button connected to the SAM4S reset line and the
 * other is a generic user configurable button labeled BP2.
 * When a button is pressed it will drive the I/O line to GND.
 *
 *   PA5 BP2
 */

#define BUTTON_BP2           0
#define NUM_BUTTONS          1

#define BUTTON_BP2_BIT       (1 << BUTTON_BP2)

#endif /* __BOARDS_ARM_SAM34_SAM4S_XPLAINED_INCLUDE_BOARD_H */
