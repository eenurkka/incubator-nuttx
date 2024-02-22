# ##############################################################################
# arch/x86_64/src/intel64/CMakeLists.txt
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS
    intel64_saveusercontext.S
    intel64_fullcontextrestore.S
    intel64_vectors.S
    intel64_head.S
    intel64_createstack.c
    intel64_initialstate.c
    intel64_irq.c
    intel64_map_region.c
    intel64_regdump.c
    intel64_releasestack.c
    intel64_rtc.c
    intel64_restore_auxstate.c
    intel64_savestate.c
    intel64_stackframe.c
    intel64_schedulesigaction.c
    intel64_sigdeliver.c
    intel64_usestack.c
    intel64_handlers.c
    intel64_idle.c
    intel64_lowsetup.c
    intel64_serial.c
    intel64_rng.c
    intel64_check_capability.c)

if(CONFIG_MULTBOOT2_FB_TERM)
  list(APPEND SRCS intel64_mbfb.c)
endif()

if(CONFIG_SCHED_TICKLESS)
  list(APPEND SRCS intel64_tickless.c)
else()
  list(APPEND SRCS intel64_timerisr.c)
endif()

target_sources(arch PRIVATE ${SRCS})