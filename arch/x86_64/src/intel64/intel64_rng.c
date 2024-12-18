/****************************************************************************
 * arch/x86_64/src/intel64/intel64_rng.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/fs/fs.h>
#include <nuttx/drivers/drivers.h>

#include <arch/io.h>

#include "x86_64_internal.h"

#if defined(CONFIG_DEV_RANDOM) || defined(CONFIG_DEV_URANDOM_ARCH)

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int x86_rng_initialize(void);
static ssize_t x86_rngread(struct file *filep, char *buffer, size_t);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations g_rngops =
{
  NULL,            /* open */
  NULL,            /* close */
  x86_rngread,     /* read */
};

/****************************************************************************
 * Private functions
 ****************************************************************************/

/****************************************************************************
 * Name: x86_rng_initialize
 ****************************************************************************/

static int x86_rng_initialize(void)
{
  _info("Initializing RNG\n");
  return OK;
}

/****************************************************************************
 * Name: x86_rngread
 ****************************************************************************/

static ssize_t x86_rngread(struct file *filep, char *buffer, size_t buflen)
{
  size_t reqlen = buflen;
  for (; buflen > 8; buflen -= 8)
    {
      while (__builtin_ia32_rdrand64_step((unsigned long long *)buffer) == 0)
        {
          sched_yield();
        }

      buffer += 8;
    }

  for (; buflen > 4; buflen -= 4)
    {
      while (__builtin_ia32_rdrand32_step((unsigned int *)buffer) == 0)
        {
          sched_yield();
        }

      buffer += 4;
    }

  for (; buflen > 2; buflen -= 2)
    {
      while (__builtin_ia32_rdrand16_step((unsigned short *)buffer) == 0)
        {
          sched_yield();
        }

      buffer += 2;
    }

  if (buflen != 0)
    {
      unsigned short temp = 0;

      while (__builtin_ia32_rdrand16_step(&temp) == 0)
        {
          sched_yield();
        }

      *buffer = (temp & 0xff);
      buffer++;
    }

  return reqlen;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: devrandom_register
 *
 * Description:
 *   Initialize the RNG hardware and register the /dev/random driver.
 *   Must be called BEFORE devurandom_register.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_DEV_RANDOM
void devrandom_register(void)
{
  x86_rng_initialize();
  register_driver("/dev/random", &g_rngops, 0444, NULL);
}
#endif

/****************************************************************************
 * Name: devurandom_register
 *
 * Description:
 *   Register /dev/urandom
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_DEV_URANDOM_ARCH
void devurandom_register(void)
{
#ifndef CONFIG_DEV_RANDOM
  x86_rng_initialize();
#endif
  register_driver("/dev/urandom", &g_rngops, 0444, NULL);
}
#endif

#endif /* CONFIG_DEV_RANDOM || CONFIG_DEV_URANDOM_ARCH */
