#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../drivers/teclado.c ../drivers/ADS1147.c ../drivers/adquisicion.c ../drivers/sensores.c ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c ../flash/rtspApi.s ../FSIO-SPI-SD/FSIO.c ../FSIO-SPI-SD/SD-SPI.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c ../RTOS/os_q.c ../RTOS/os_sem.c ../RTOS/os_task.c ../RTOS/os_time.c ../RTOS/os_tmr.c ../RTOS/os_mem.c ../RTOS/os_mutex.c ../RTOS/os_mbox.c ../RTOS/os_flag.c ../RTOS/os_dbg.c ../RTOS/os_cpu_c.c ../RTOS/os_core.c ../RTOS/os_cpu_a.s ../RTOS/os_cpu_util_a.s ../RTOS/lib_mem.c ../RTOS/lib_str.c ../isr.s ../globals.c ../app_hooks.c ../app.c ../dsPIC_delay.c ../dsPIC_cfg.c ../eventotecla.c ../SD.c ../interfaz_cfg.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/239857660/teclado.o ${OBJECTDIR}/_ext/239857660/ADS1147.o ${OBJECTDIR}/_ext/239857660/adquisicion.o ${OBJECTDIR}/_ext/239857660/sensores.o ${OBJECTDIR}/_ext/1450017335/glcdK0108.o ${OBJECTDIR}/_ext/2116523295/rtspApi.o ${OBJECTDIR}/_ext/100683587/FSIO.o ${OBJECTDIR}/_ext/100683587/SD-SPI.o ${OBJECTDIR}/_ext/721076465/button.o ${OBJECTDIR}/_ext/721076465/checkbox.o ${OBJECTDIR}/_ext/721076465/interfaz.o ${OBJECTDIR}/_ext/721076465/label.o ${OBJECTDIR}/_ext/721076465/msgbox.o ${OBJECTDIR}/_ext/721076465/progbar.o ${OBJECTDIR}/_ext/721076465/spinedit.o ${OBJECTDIR}/_ext/761631083/os_q.o ${OBJECTDIR}/_ext/761631083/os_sem.o ${OBJECTDIR}/_ext/761631083/os_task.o ${OBJECTDIR}/_ext/761631083/os_time.o ${OBJECTDIR}/_ext/761631083/os_tmr.o ${OBJECTDIR}/_ext/761631083/os_mem.o ${OBJECTDIR}/_ext/761631083/os_mutex.o ${OBJECTDIR}/_ext/761631083/os_mbox.o ${OBJECTDIR}/_ext/761631083/os_flag.o ${OBJECTDIR}/_ext/761631083/os_dbg.o ${OBJECTDIR}/_ext/761631083/os_cpu_c.o ${OBJECTDIR}/_ext/761631083/os_core.o ${OBJECTDIR}/_ext/761631083/os_cpu_a.o ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o ${OBJECTDIR}/_ext/761631083/lib_mem.o ${OBJECTDIR}/_ext/761631083/lib_str.o ${OBJECTDIR}/_ext/1472/isr.o ${OBJECTDIR}/_ext/1472/globals.o ${OBJECTDIR}/_ext/1472/app_hooks.o ${OBJECTDIR}/_ext/1472/app.o ${OBJECTDIR}/_ext/1472/dsPIC_delay.o ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o ${OBJECTDIR}/_ext/1472/eventotecla.o ${OBJECTDIR}/_ext/1472/SD.o ${OBJECTDIR}/_ext/1472/interfaz_cfg.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/239857660/teclado.o.d ${OBJECTDIR}/_ext/239857660/ADS1147.o.d ${OBJECTDIR}/_ext/239857660/adquisicion.o.d ${OBJECTDIR}/_ext/239857660/sensores.o.d ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d ${OBJECTDIR}/_ext/2116523295/rtspApi.o.d ${OBJECTDIR}/_ext/100683587/FSIO.o.d ${OBJECTDIR}/_ext/100683587/SD-SPI.o.d ${OBJECTDIR}/_ext/721076465/button.o.d ${OBJECTDIR}/_ext/721076465/checkbox.o.d ${OBJECTDIR}/_ext/721076465/interfaz.o.d ${OBJECTDIR}/_ext/721076465/label.o.d ${OBJECTDIR}/_ext/721076465/msgbox.o.d ${OBJECTDIR}/_ext/721076465/progbar.o.d ${OBJECTDIR}/_ext/721076465/spinedit.o.d ${OBJECTDIR}/_ext/761631083/os_q.o.d ${OBJECTDIR}/_ext/761631083/os_sem.o.d ${OBJECTDIR}/_ext/761631083/os_task.o.d ${OBJECTDIR}/_ext/761631083/os_time.o.d ${OBJECTDIR}/_ext/761631083/os_tmr.o.d ${OBJECTDIR}/_ext/761631083/os_mem.o.d ${OBJECTDIR}/_ext/761631083/os_mutex.o.d ${OBJECTDIR}/_ext/761631083/os_mbox.o.d ${OBJECTDIR}/_ext/761631083/os_flag.o.d ${OBJECTDIR}/_ext/761631083/os_dbg.o.d ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d ${OBJECTDIR}/_ext/761631083/os_core.o.d ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d ${OBJECTDIR}/_ext/761631083/lib_mem.o.d ${OBJECTDIR}/_ext/761631083/lib_str.o.d ${OBJECTDIR}/_ext/1472/isr.o.d ${OBJECTDIR}/_ext/1472/globals.o.d ${OBJECTDIR}/_ext/1472/app_hooks.o.d ${OBJECTDIR}/_ext/1472/app.o.d ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d ${OBJECTDIR}/_ext/1472/eventotecla.o.d ${OBJECTDIR}/_ext/1472/SD.o.d ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/239857660/teclado.o ${OBJECTDIR}/_ext/239857660/ADS1147.o ${OBJECTDIR}/_ext/239857660/adquisicion.o ${OBJECTDIR}/_ext/239857660/sensores.o ${OBJECTDIR}/_ext/1450017335/glcdK0108.o ${OBJECTDIR}/_ext/2116523295/rtspApi.o ${OBJECTDIR}/_ext/100683587/FSIO.o ${OBJECTDIR}/_ext/100683587/SD-SPI.o ${OBJECTDIR}/_ext/721076465/button.o ${OBJECTDIR}/_ext/721076465/checkbox.o ${OBJECTDIR}/_ext/721076465/interfaz.o ${OBJECTDIR}/_ext/721076465/label.o ${OBJECTDIR}/_ext/721076465/msgbox.o ${OBJECTDIR}/_ext/721076465/progbar.o ${OBJECTDIR}/_ext/721076465/spinedit.o ${OBJECTDIR}/_ext/761631083/os_q.o ${OBJECTDIR}/_ext/761631083/os_sem.o ${OBJECTDIR}/_ext/761631083/os_task.o ${OBJECTDIR}/_ext/761631083/os_time.o ${OBJECTDIR}/_ext/761631083/os_tmr.o ${OBJECTDIR}/_ext/761631083/os_mem.o ${OBJECTDIR}/_ext/761631083/os_mutex.o ${OBJECTDIR}/_ext/761631083/os_mbox.o ${OBJECTDIR}/_ext/761631083/os_flag.o ${OBJECTDIR}/_ext/761631083/os_dbg.o ${OBJECTDIR}/_ext/761631083/os_cpu_c.o ${OBJECTDIR}/_ext/761631083/os_core.o ${OBJECTDIR}/_ext/761631083/os_cpu_a.o ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o ${OBJECTDIR}/_ext/761631083/lib_mem.o ${OBJECTDIR}/_ext/761631083/lib_str.o ${OBJECTDIR}/_ext/1472/isr.o ${OBJECTDIR}/_ext/1472/globals.o ${OBJECTDIR}/_ext/1472/app_hooks.o ${OBJECTDIR}/_ext/1472/app.o ${OBJECTDIR}/_ext/1472/dsPIC_delay.o ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o ${OBJECTDIR}/_ext/1472/eventotecla.o ${OBJECTDIR}/_ext/1472/SD.o ${OBJECTDIR}/_ext/1472/interfaz_cfg.o

# Source Files
SOURCEFILES=../drivers/teclado.c ../drivers/ADS1147.c ../drivers/adquisicion.c ../drivers/sensores.c ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c ../flash/rtspApi.s ../FSIO-SPI-SD/FSIO.c ../FSIO-SPI-SD/SD-SPI.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c ../RTOS/os_q.c ../RTOS/os_sem.c ../RTOS/os_task.c ../RTOS/os_time.c ../RTOS/os_tmr.c ../RTOS/os_mem.c ../RTOS/os_mutex.c ../RTOS/os_mbox.c ../RTOS/os_flag.c ../RTOS/os_dbg.c ../RTOS/os_cpu_c.c ../RTOS/os_core.c ../RTOS/os_cpu_a.s ../RTOS/os_cpu_util_a.s ../RTOS/lib_mem.c ../RTOS/lib_str.c ../isr.s ../globals.c ../app_hooks.c ../app.c ../dsPIC_delay.c ../dsPIC_cfg.c ../eventotecla.c ../SD.c ../interfaz_cfg.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP804
MP_LINKER_FILE_OPTION=,--script="..\p33FJ128GP804.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2116523295/rtspApi.o: ../flash/rtspApi.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2116523295 
	@${RM} ${OBJECTDIR}/_ext/2116523295/rtspApi.o.d 
	@${RM} ${OBJECTDIR}/_ext/2116523295/rtspApi.o.ok ${OBJECTDIR}/_ext/2116523295/rtspApi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2116523295/rtspApi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../flash/rtspApi.s -o ${OBJECTDIR}/_ext/2116523295/rtspApi.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 --defsym=__MPLAB_DEBUG=1 --defsym=__ICD2RAM=1 --defsym=__DEBUG=1 --defsym=__MPLAB_DEBUGGER_ICD3=1 -g  -MD "${OBJECTDIR}/_ext/2116523295/rtspApi.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/761631083/os_cpu_a.o: ../RTOS/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../RTOS/os_cpu_a.s -o ${OBJECTDIR}/_ext/761631083/os_cpu_a.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 --defsym=__MPLAB_DEBUG=1 --defsym=__ICD2RAM=1 --defsym=__DEBUG=1 --defsym=__MPLAB_DEBUGGER_ICD3=1 -g  -MD "${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o: ../RTOS/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../RTOS/os_cpu_util_a.s -o ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 --defsym=__MPLAB_DEBUG=1 --defsym=__ICD2RAM=1 --defsym=__DEBUG=1 --defsym=__MPLAB_DEBUGGER_ICD3=1 -g  -MD "${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/1472/isr.o: ../isr.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/isr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/isr.o.ok ${OBJECTDIR}/_ext/1472/isr.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/isr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../isr.s -o ${OBJECTDIR}/_ext/1472/isr.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 --defsym=__MPLAB_DEBUG=1 --defsym=__ICD2RAM=1 --defsym=__DEBUG=1 --defsym=__MPLAB_DEBUGGER_ICD3=1 -g  -MD "${OBJECTDIR}/_ext/1472/isr.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
else
${OBJECTDIR}/_ext/2116523295/rtspApi.o: ../flash/rtspApi.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2116523295 
	@${RM} ${OBJECTDIR}/_ext/2116523295/rtspApi.o.d 
	@${RM} ${OBJECTDIR}/_ext/2116523295/rtspApi.o.ok ${OBJECTDIR}/_ext/2116523295/rtspApi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2116523295/rtspApi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../flash/rtspApi.s -o ${OBJECTDIR}/_ext/2116523295/rtspApi.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 -g  -MD "${OBJECTDIR}/_ext/2116523295/rtspApi.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/761631083/os_cpu_a.o: ../RTOS/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../RTOS/os_cpu_a.s -o ${OBJECTDIR}/_ext/761631083/os_cpu_a.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 -g  -MD "${OBJECTDIR}/_ext/761631083/os_cpu_a.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o: ../RTOS/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../RTOS/os_cpu_util_a.s -o ${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 -g  -MD "${OBJECTDIR}/_ext/761631083/os_cpu_util_a.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
${OBJECTDIR}/_ext/1472/isr.o: ../isr.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/isr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/isr.o.ok ${OBJECTDIR}/_ext/1472/isr.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/isr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../isr.s -o ${OBJECTDIR}/_ext/1472/isr.o -omf=elf -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 -g  -MD "${OBJECTDIR}/_ext/1472/isr.o.d" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/NanoGUI_RTOS_v2.1" -I"../../../../proyecto5r1/firmware/v0.1" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I".." -g$(MP_EXTRA_AS_POST)
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/239857660/teclado.o: ../drivers/teclado.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/teclado.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/teclado.o.ok ${OBJECTDIR}/_ext/239857660/teclado.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/teclado.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/teclado.o.d" -o ${OBJECTDIR}/_ext/239857660/teclado.o ../drivers/teclado.c    
	
${OBJECTDIR}/_ext/239857660/ADS1147.o: ../drivers/ADS1147.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/ADS1147.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/ADS1147.o.ok ${OBJECTDIR}/_ext/239857660/ADS1147.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/ADS1147.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/ADS1147.o.d" -o ${OBJECTDIR}/_ext/239857660/ADS1147.o ../drivers/ADS1147.c    
	
${OBJECTDIR}/_ext/239857660/adquisicion.o: ../drivers/adquisicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/adquisicion.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/adquisicion.o.ok ${OBJECTDIR}/_ext/239857660/adquisicion.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/adquisicion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/adquisicion.o.d" -o ${OBJECTDIR}/_ext/239857660/adquisicion.o ../drivers/adquisicion.c    
	
${OBJECTDIR}/_ext/239857660/sensores.o: ../drivers/sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/sensores.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/sensores.o.ok ${OBJECTDIR}/_ext/239857660/sensores.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/sensores.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/sensores.o.d" -o ${OBJECTDIR}/_ext/239857660/sensores.o ../drivers/sensores.c    
	
${OBJECTDIR}/_ext/1450017335/glcdK0108.o: ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1450017335 
	@${RM} ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d 
	@${RM} ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.ok ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d" -o ${OBJECTDIR}/_ext/1450017335/glcdK0108.o ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c    
	
${OBJECTDIR}/_ext/100683587/FSIO.o: ../FSIO-SPI-SD/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/100683587 
	@${RM} ${OBJECTDIR}/_ext/100683587/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/100683587/FSIO.o.ok ${OBJECTDIR}/_ext/100683587/FSIO.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/100683587/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/100683587/FSIO.o.d" -o ${OBJECTDIR}/_ext/100683587/FSIO.o ../FSIO-SPI-SD/FSIO.c    
	
${OBJECTDIR}/_ext/100683587/SD-SPI.o: ../FSIO-SPI-SD/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/100683587 
	@${RM} ${OBJECTDIR}/_ext/100683587/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/100683587/SD-SPI.o.ok ${OBJECTDIR}/_ext/100683587/SD-SPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/100683587/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/100683587/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/100683587/SD-SPI.o ../FSIO-SPI-SD/SD-SPI.c    
	
${OBJECTDIR}/_ext/721076465/button.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/button.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/button.o.ok ${OBJECTDIR}/_ext/721076465/button.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/button.o.d" -o ${OBJECTDIR}/_ext/721076465/button.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c    
	
${OBJECTDIR}/_ext/721076465/checkbox.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/checkbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/checkbox.o.ok ${OBJECTDIR}/_ext/721076465/checkbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/checkbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/checkbox.o.d" -o ${OBJECTDIR}/_ext/721076465/checkbox.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c    
	
${OBJECTDIR}/_ext/721076465/interfaz.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/interfaz.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/interfaz.o.ok ${OBJECTDIR}/_ext/721076465/interfaz.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/interfaz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/interfaz.o.d" -o ${OBJECTDIR}/_ext/721076465/interfaz.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c    
	
${OBJECTDIR}/_ext/721076465/label.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/label.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/label.o.ok ${OBJECTDIR}/_ext/721076465/label.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/label.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/label.o.d" -o ${OBJECTDIR}/_ext/721076465/label.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c    
	
${OBJECTDIR}/_ext/721076465/msgbox.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/msgbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/msgbox.o.ok ${OBJECTDIR}/_ext/721076465/msgbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/msgbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/msgbox.o.d" -o ${OBJECTDIR}/_ext/721076465/msgbox.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c    
	
${OBJECTDIR}/_ext/721076465/progbar.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/progbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/progbar.o.ok ${OBJECTDIR}/_ext/721076465/progbar.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/progbar.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/progbar.o.d" -o ${OBJECTDIR}/_ext/721076465/progbar.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c    
	
${OBJECTDIR}/_ext/721076465/spinedit.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/spinedit.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/spinedit.o.ok ${OBJECTDIR}/_ext/721076465/spinedit.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/spinedit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/spinedit.o.d" -o ${OBJECTDIR}/_ext/721076465/spinedit.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c    
	
${OBJECTDIR}/_ext/761631083/os_q.o: ../RTOS/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_q.o.ok ${OBJECTDIR}/_ext/761631083/os_q.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_q.o.d" -o ${OBJECTDIR}/_ext/761631083/os_q.o ../RTOS/os_q.c    
	
${OBJECTDIR}/_ext/761631083/os_sem.o: ../RTOS/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_sem.o.ok ${OBJECTDIR}/_ext/761631083/os_sem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_sem.o.d" -o ${OBJECTDIR}/_ext/761631083/os_sem.o ../RTOS/os_sem.c    
	
${OBJECTDIR}/_ext/761631083/os_task.o: ../RTOS/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_task.o.ok ${OBJECTDIR}/_ext/761631083/os_task.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_task.o.d" -o ${OBJECTDIR}/_ext/761631083/os_task.o ../RTOS/os_task.c    
	
${OBJECTDIR}/_ext/761631083/os_time.o: ../RTOS/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_time.o.ok ${OBJECTDIR}/_ext/761631083/os_time.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_time.o.d" -o ${OBJECTDIR}/_ext/761631083/os_time.o ../RTOS/os_time.c    
	
${OBJECTDIR}/_ext/761631083/os_tmr.o: ../RTOS/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_tmr.o.ok ${OBJECTDIR}/_ext/761631083/os_tmr.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_tmr.o.d" -o ${OBJECTDIR}/_ext/761631083/os_tmr.o ../RTOS/os_tmr.c    
	
${OBJECTDIR}/_ext/761631083/os_mem.o: ../RTOS/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mem.o.ok ${OBJECTDIR}/_ext/761631083/os_mem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mem.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mem.o ../RTOS/os_mem.c    
	
${OBJECTDIR}/_ext/761631083/os_mutex.o: ../RTOS/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mutex.o.ok ${OBJECTDIR}/_ext/761631083/os_mutex.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mutex.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mutex.o ../RTOS/os_mutex.c    
	
${OBJECTDIR}/_ext/761631083/os_mbox.o: ../RTOS/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mbox.o.ok ${OBJECTDIR}/_ext/761631083/os_mbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mbox.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mbox.o ../RTOS/os_mbox.c    
	
${OBJECTDIR}/_ext/761631083/os_flag.o: ../RTOS/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_flag.o.ok ${OBJECTDIR}/_ext/761631083/os_flag.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_flag.o.d" -o ${OBJECTDIR}/_ext/761631083/os_flag.o ../RTOS/os_flag.c    
	
${OBJECTDIR}/_ext/761631083/os_dbg.o: ../RTOS/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_dbg.o.ok ${OBJECTDIR}/_ext/761631083/os_dbg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_dbg.o.d" -o ${OBJECTDIR}/_ext/761631083/os_dbg.o ../RTOS/os_dbg.c    
	
${OBJECTDIR}/_ext/761631083/os_cpu_c.o: ../RTOS/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/761631083/os_cpu_c.o ../RTOS/os_cpu_c.c    
	
${OBJECTDIR}/_ext/761631083/os_core.o: ../RTOS/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_core.o.ok ${OBJECTDIR}/_ext/761631083/os_core.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_core.o.d" -o ${OBJECTDIR}/_ext/761631083/os_core.o ../RTOS/os_core.c    
	
${OBJECTDIR}/_ext/761631083/lib_mem.o: ../RTOS/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_mem.o.ok ${OBJECTDIR}/_ext/761631083/lib_mem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/lib_mem.o.d" -o ${OBJECTDIR}/_ext/761631083/lib_mem.o ../RTOS/lib_mem.c    
	
${OBJECTDIR}/_ext/761631083/lib_str.o: ../RTOS/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_str.o.ok ${OBJECTDIR}/_ext/761631083/lib_str.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/lib_str.o.d" -o ${OBJECTDIR}/_ext/761631083/lib_str.o ../RTOS/lib_str.c    
	
${OBJECTDIR}/_ext/1472/globals.o: ../globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/globals.o.ok ${OBJECTDIR}/_ext/1472/globals.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/globals.o.d" -o ${OBJECTDIR}/_ext/1472/globals.o ../globals.c    
	
${OBJECTDIR}/_ext/1472/app_hooks.o: ../app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.ok ${OBJECTDIR}/_ext/1472/app_hooks.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/app_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/app_hooks.o ../app_hooks.c    
	
${OBJECTDIR}/_ext/1472/app.o: ../app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.ok ${OBJECTDIR}/_ext/1472/app.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/app.o.d" -o ${OBJECTDIR}/_ext/1472/app.o ../app.c    
	
${OBJECTDIR}/_ext/1472/dsPIC_delay.o: ../dsPIC_delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.ok ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d" -o ${OBJECTDIR}/_ext/1472/dsPIC_delay.o ../dsPIC_delay.c    
	
${OBJECTDIR}/_ext/1472/dsPIC_cfg.o: ../dsPIC_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.ok ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o ../dsPIC_cfg.c    
	
${OBJECTDIR}/_ext/1472/eventotecla.o: ../eventotecla.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/eventotecla.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/eventotecla.o.ok ${OBJECTDIR}/_ext/1472/eventotecla.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/eventotecla.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/eventotecla.o.d" -o ${OBJECTDIR}/_ext/1472/eventotecla.o ../eventotecla.c    
	
${OBJECTDIR}/_ext/1472/SD.o: ../SD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SD.o.ok ${OBJECTDIR}/_ext/1472/SD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/SD.o.d" -o ${OBJECTDIR}/_ext/1472/SD.o ../SD.c    
	
${OBJECTDIR}/_ext/1472/interfaz_cfg.o: ../interfaz_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.ok ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/interfaz_cfg.o ../interfaz_cfg.c    
	
else
${OBJECTDIR}/_ext/239857660/teclado.o: ../drivers/teclado.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/teclado.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/teclado.o.ok ${OBJECTDIR}/_ext/239857660/teclado.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/teclado.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/teclado.o.d" -o ${OBJECTDIR}/_ext/239857660/teclado.o ../drivers/teclado.c    
	
${OBJECTDIR}/_ext/239857660/ADS1147.o: ../drivers/ADS1147.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/ADS1147.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/ADS1147.o.ok ${OBJECTDIR}/_ext/239857660/ADS1147.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/ADS1147.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/ADS1147.o.d" -o ${OBJECTDIR}/_ext/239857660/ADS1147.o ../drivers/ADS1147.c    
	
${OBJECTDIR}/_ext/239857660/adquisicion.o: ../drivers/adquisicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/adquisicion.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/adquisicion.o.ok ${OBJECTDIR}/_ext/239857660/adquisicion.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/adquisicion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/adquisicion.o.d" -o ${OBJECTDIR}/_ext/239857660/adquisicion.o ../drivers/adquisicion.c    
	
${OBJECTDIR}/_ext/239857660/sensores.o: ../drivers/sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/sensores.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/sensores.o.ok ${OBJECTDIR}/_ext/239857660/sensores.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/sensores.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/239857660/sensores.o.d" -o ${OBJECTDIR}/_ext/239857660/sensores.o ../drivers/sensores.c    
	
${OBJECTDIR}/_ext/1450017335/glcdK0108.o: ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1450017335 
	@${RM} ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d 
	@${RM} ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.ok ${OBJECTDIR}/_ext/1450017335/glcdK0108.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1450017335/glcdK0108.o.d" -o ${OBJECTDIR}/_ext/1450017335/glcdK0108.o ../../../../Piuke/trunk/proyectos/drivers/Display/glcdK0108.c    
	
${OBJECTDIR}/_ext/100683587/FSIO.o: ../FSIO-SPI-SD/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/100683587 
	@${RM} ${OBJECTDIR}/_ext/100683587/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/100683587/FSIO.o.ok ${OBJECTDIR}/_ext/100683587/FSIO.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/100683587/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/100683587/FSIO.o.d" -o ${OBJECTDIR}/_ext/100683587/FSIO.o ../FSIO-SPI-SD/FSIO.c    
	
${OBJECTDIR}/_ext/100683587/SD-SPI.o: ../FSIO-SPI-SD/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/100683587 
	@${RM} ${OBJECTDIR}/_ext/100683587/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/100683587/SD-SPI.o.ok ${OBJECTDIR}/_ext/100683587/SD-SPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/100683587/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/100683587/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/100683587/SD-SPI.o ../FSIO-SPI-SD/SD-SPI.c    
	
${OBJECTDIR}/_ext/721076465/button.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/button.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/button.o.ok ${OBJECTDIR}/_ext/721076465/button.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/button.o.d" -o ${OBJECTDIR}/_ext/721076465/button.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/button.c    
	
${OBJECTDIR}/_ext/721076465/checkbox.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/checkbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/checkbox.o.ok ${OBJECTDIR}/_ext/721076465/checkbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/checkbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/checkbox.o.d" -o ${OBJECTDIR}/_ext/721076465/checkbox.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/checkbox.c    
	
${OBJECTDIR}/_ext/721076465/interfaz.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/interfaz.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/interfaz.o.ok ${OBJECTDIR}/_ext/721076465/interfaz.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/interfaz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/interfaz.o.d" -o ${OBJECTDIR}/_ext/721076465/interfaz.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/interfaz.c    
	
${OBJECTDIR}/_ext/721076465/label.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/label.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/label.o.ok ${OBJECTDIR}/_ext/721076465/label.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/label.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/label.o.d" -o ${OBJECTDIR}/_ext/721076465/label.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/label.c    
	
${OBJECTDIR}/_ext/721076465/msgbox.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/msgbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/msgbox.o.ok ${OBJECTDIR}/_ext/721076465/msgbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/msgbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/msgbox.o.d" -o ${OBJECTDIR}/_ext/721076465/msgbox.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/msgbox.c    
	
${OBJECTDIR}/_ext/721076465/progbar.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/progbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/progbar.o.ok ${OBJECTDIR}/_ext/721076465/progbar.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/progbar.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/progbar.o.d" -o ${OBJECTDIR}/_ext/721076465/progbar.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/progbar.c    
	
${OBJECTDIR}/_ext/721076465/spinedit.o: ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/721076465 
	@${RM} ${OBJECTDIR}/_ext/721076465/spinedit.o.d 
	@${RM} ${OBJECTDIR}/_ext/721076465/spinedit.o.ok ${OBJECTDIR}/_ext/721076465/spinedit.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/721076465/spinedit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/721076465/spinedit.o.d" -o ${OBJECTDIR}/_ext/721076465/spinedit.o ../../../../Piuke/trunk/proyectos/03_nanoGUI/v2.2/spinedit.c    
	
${OBJECTDIR}/_ext/761631083/os_q.o: ../RTOS/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_q.o.ok ${OBJECTDIR}/_ext/761631083/os_q.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_q.o.d" -o ${OBJECTDIR}/_ext/761631083/os_q.o ../RTOS/os_q.c    
	
${OBJECTDIR}/_ext/761631083/os_sem.o: ../RTOS/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_sem.o.ok ${OBJECTDIR}/_ext/761631083/os_sem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_sem.o.d" -o ${OBJECTDIR}/_ext/761631083/os_sem.o ../RTOS/os_sem.c    
	
${OBJECTDIR}/_ext/761631083/os_task.o: ../RTOS/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_task.o.ok ${OBJECTDIR}/_ext/761631083/os_task.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_task.o.d" -o ${OBJECTDIR}/_ext/761631083/os_task.o ../RTOS/os_task.c    
	
${OBJECTDIR}/_ext/761631083/os_time.o: ../RTOS/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_time.o.ok ${OBJECTDIR}/_ext/761631083/os_time.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_time.o.d" -o ${OBJECTDIR}/_ext/761631083/os_time.o ../RTOS/os_time.c    
	
${OBJECTDIR}/_ext/761631083/os_tmr.o: ../RTOS/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_tmr.o.ok ${OBJECTDIR}/_ext/761631083/os_tmr.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_tmr.o.d" -o ${OBJECTDIR}/_ext/761631083/os_tmr.o ../RTOS/os_tmr.c    
	
${OBJECTDIR}/_ext/761631083/os_mem.o: ../RTOS/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mem.o.ok ${OBJECTDIR}/_ext/761631083/os_mem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mem.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mem.o ../RTOS/os_mem.c    
	
${OBJECTDIR}/_ext/761631083/os_mutex.o: ../RTOS/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mutex.o.ok ${OBJECTDIR}/_ext/761631083/os_mutex.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mutex.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mutex.o ../RTOS/os_mutex.c    
	
${OBJECTDIR}/_ext/761631083/os_mbox.o: ../RTOS/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_mbox.o.ok ${OBJECTDIR}/_ext/761631083/os_mbox.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_mbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_mbox.o.d" -o ${OBJECTDIR}/_ext/761631083/os_mbox.o ../RTOS/os_mbox.c    
	
${OBJECTDIR}/_ext/761631083/os_flag.o: ../RTOS/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_flag.o.ok ${OBJECTDIR}/_ext/761631083/os_flag.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_flag.o.d" -o ${OBJECTDIR}/_ext/761631083/os_flag.o ../RTOS/os_flag.c    
	
${OBJECTDIR}/_ext/761631083/os_dbg.o: ../RTOS/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_dbg.o.ok ${OBJECTDIR}/_ext/761631083/os_dbg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_dbg.o.d" -o ${OBJECTDIR}/_ext/761631083/os_dbg.o ../RTOS/os_dbg.c    
	
${OBJECTDIR}/_ext/761631083/os_cpu_c.o: ../RTOS/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.ok ${OBJECTDIR}/_ext/761631083/os_cpu_c.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/761631083/os_cpu_c.o ../RTOS/os_cpu_c.c    
	
${OBJECTDIR}/_ext/761631083/os_core.o: ../RTOS/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/os_core.o.ok ${OBJECTDIR}/_ext/761631083/os_core.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/os_core.o.d" -o ${OBJECTDIR}/_ext/761631083/os_core.o ../RTOS/os_core.c    
	
${OBJECTDIR}/_ext/761631083/lib_mem.o: ../RTOS/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_mem.o.ok ${OBJECTDIR}/_ext/761631083/lib_mem.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/lib_mem.o.d" -o ${OBJECTDIR}/_ext/761631083/lib_mem.o ../RTOS/lib_mem.c    
	
${OBJECTDIR}/_ext/761631083/lib_str.o: ../RTOS/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761631083 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/761631083/lib_str.o.ok ${OBJECTDIR}/_ext/761631083/lib_str.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761631083/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/761631083/lib_str.o.d" -o ${OBJECTDIR}/_ext/761631083/lib_str.o ../RTOS/lib_str.c    
	
${OBJECTDIR}/_ext/1472/globals.o: ../globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/globals.o.ok ${OBJECTDIR}/_ext/1472/globals.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/globals.o.d" -o ${OBJECTDIR}/_ext/1472/globals.o ../globals.c    
	
${OBJECTDIR}/_ext/1472/app_hooks.o: ../app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app_hooks.o.ok ${OBJECTDIR}/_ext/1472/app_hooks.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/app_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/app_hooks.o ../app_hooks.c    
	
${OBJECTDIR}/_ext/1472/app.o: ../app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/app.o.ok ${OBJECTDIR}/_ext/1472/app.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/app.o.d" -o ${OBJECTDIR}/_ext/1472/app.o ../app.c    
	
${OBJECTDIR}/_ext/1472/dsPIC_delay.o: ../dsPIC_delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.ok ${OBJECTDIR}/_ext/1472/dsPIC_delay.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/dsPIC_delay.o.d" -o ${OBJECTDIR}/_ext/1472/dsPIC_delay.o ../dsPIC_delay.c    
	
${OBJECTDIR}/_ext/1472/dsPIC_cfg.o: ../dsPIC_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.ok ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/dsPIC_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/dsPIC_cfg.o ../dsPIC_cfg.c    
	
${OBJECTDIR}/_ext/1472/eventotecla.o: ../eventotecla.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/eventotecla.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/eventotecla.o.ok ${OBJECTDIR}/_ext/1472/eventotecla.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/eventotecla.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/eventotecla.o.d" -o ${OBJECTDIR}/_ext/1472/eventotecla.o ../eventotecla.c    
	
${OBJECTDIR}/_ext/1472/SD.o: ../SD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SD.o.ok ${OBJECTDIR}/_ext/1472/SD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/SD.o.d" -o ${OBJECTDIR}/_ext/1472/SD.o ../SD.c    
	
${OBJECTDIR}/_ext/1472/interfaz_cfg.o: ../interfaz_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.ok ${OBJECTDIR}/_ext/1472/interfaz_cfg.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../../../../piuke/trunk/proyectos/drivers/Display" -I"../../../../piuke/trunk/proyectos/03_nanoGUI/v2.2" -I"../../../../proyecto5r1/firmware/v0.1/flash" -I"../../../../proyecto5r1/firmware/v0.1/FSIO-SPI-SD" -I"E:/proyecto5r1/firmware/v0.1" -I"E:/proyecto5r1/firmware/v0.1/RTOS" -I"E:/proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/drivers" -I"../../../../proyecto5r1/firmware/v0.1/RTOS" -I"../../../../proyecto5r1/firmware/v0.1" -I".." -I"../RTOS" -I"../drivers" -I"../FSIO-SPI-SD" -I"../flash" -mlarge-code -mlarge-data -mlarge-scalar -MMD -MF "${OBJECTDIR}/_ext/1472/interfaz_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/interfaz_cfg.o ../interfaz_cfg.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../p33FJ128GP804.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"C:/Program Files/Microchip/MPLAB C30/lib",-L"..",-Map="${DISTDIR}/MeDEf.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../p33FJ128GP804.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"C:/Program Files/Microchip/MPLAB C30/lib",-L"..",-Map="${DISTDIR}/MeDEf.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MeDEf.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
