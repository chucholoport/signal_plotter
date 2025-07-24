# 🧱 Configuration
TARGET      := signal_plotter
PORT        := COM3
BAUDRATE    := 500000

# 🛠️ Compilation Tools
DEVICE     := xtensa-lx106-elf
CC         := $(DEVICE)-gcc
OBJCOPY    := $(DEVICE)-objcopy
OBJDUMP    := $(DEVICE)-objdump
CFLAGS     := -Os -Wall -std=c99

# 🚩 Base Directories
SRC_DIR       := ../Source
TARGET_DIR    := ../Target
BUILD_DIR     := $(TARGET_DIR)/build
RELEASE_DIR   := $(TARGET_DIR)/release
HAL_MODULE    := $(SRC_DIR)/Hal
DRV_MODULE    := $(SRC_DIR)/Drv
DSP_MODULE    := $(SRC_DIR)/Dsp
HMI_MODULE    := $(SRC_DIR)/Hmi
STMCHN_MODULE := $(SRC_DIR)/StMchn
MAIN_FILE     := $(SRC_DIR)/main.c

HAL_SOURCES := \
  $(HAL_MODULE)/HalAdc/HalAdc.c \
  $(HAL_MODULE)/HalCom/HalCom.c \
  $(HAL_MODULE)/HalDio/HalDio.c \
  $(HAL_MODULE)/HalTmr/HalTmr.c \
  $(HAL_MODULE)/HalHmi/HalHmi.c

DRV_SOURCES := \
  $(DRV_MODULE)/DrvAdc/DrvAdc.c \
  $(DRV_MODULE)/DrvCom/DrvCom.c \
  $(DRV_MODULE)/DrvDio/DrvDio.c \
  $(DRV_MODULE)/DrvTmr/DrvTmr.c \
  $(DRV_MODULE)/DrvHmi/DrvHmi.c

DSP_SOURCES := \
  $(DSP_MODULE)/Atcrrltn/Atcrrltn.c \
  $(DSP_MODULE)/SgnlRtrvr/SgnlRtrvr.c

HMI_SOURCES := \
  $(HMI_MODULE)/HmiFrq/HmiFrq.c \
  $(HMI_MODULE)/HmiSgnlPlttr/HmiSgnlPlttr.c \
  $(HMI_MODULE)/HmiSgnlAdjstr/HmiSgnlAdjstr.c \
  $(HMI_MODULE)/HmiMscNt/HmiMscNt.c \
  $(HMI_MODULE)/HmiMscCnt/HmiMscCnt.c

STMCHN_SOURCES := \
  $(STMCHN_MODULE)/StMchn.c

MAIN_FILE := $(SRC_DIR)/main.c

# 📦 List of .c files
C_SOURCES := \
  $(HAL_SOURCES) \
  $(DRV_SOURCES) \
  $(DSP_SOURCES) \
  $(HMI_SOURCES) \
  $(STMCHN_SOURCES) \
  $(MAIN_FILE)

OBJS := $(foreach src, $(C_SOURCES), $(BUILD_DIR)/$(subst .c,.o,$(subst $(SRC_DIR)/,,$(src))))

# 📁 Includes
INCLUDES := -I$(SRC_DIR) -I$(SRC_DIR)/Hal -I$(SRC_DIR)/Drv -I$(SRC_DIR)/Dsp -I$(SRC_DIR)/Hmi -I$(SRC_DIR)/StMchn

# 🔧 Link flags
LDFLAGS :=

# 🗂️ Out files
MAP_FILE := $(RELEASE_DIR)/$(TARGET).map
ELF_FILE := $(RELEASE_DIR)/$(TARGET).elf
HEX_FILE := $(RELEASE_DIR)/$(TARGET).hex
BIN_FILE := $(RELEASE_DIR)/$(TARGET).bin
LST_FILE := $(RELEASE_DIR)/$(TARGET).lst
OUT_FILE := $(RELEASE_DIR)/$(TARGET).out

# 🧱 Compile each .c → .o
define compile_template
$(BUILD_DIR)/$(subst .c,.o,$(subst $(SRC_DIR)/,,$(1))): $(1)
	@if not exist "$(subst /,\,$(dir $(BUILD_DIR)/$(subst .c,.o,$(subst $(SRC_DIR)/,,$(1)))))" mkdir "$(subst /,\,$(dir $(BUILD_DIR)/$(subst .c,.o,$(subst $(SRC_DIR)/,,$(1)))))"
	@echo Compiling $(1)...
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(1) -o $(BUILD_DIR)/$(subst .c,.o,$(subst $(SRC_DIR)/,,$(1)))
	@echo done.
	@echo.

endef

$(foreach file,$(C_SOURCES),$(eval $(call compile_template,$(file))))

# 📂 Create release folder
$(RELEASE_DIR):
	@echo Creating release directory...
	@if not exist "$(subst /,\,$(RELEASE_DIR))" mkdir "$(subst /,\,$(RELEASE_DIR))"
	@echo done.
	@echo.

# 🧙‍♂️ Generate .elf file
$(ELF_FILE): $(RELEASE_DIR) $(OBJS)
	@echo Linking object files...
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@
	@echo done.
	@echo.

# 📦 Generate .hex file
$(HEX_FILE): $(ELF_FILE)
	@echo Generating hex file...
	@$(OBJCOPY) -O ihex $< $@
	@echo done.
	@echo.

# 🗺️ Generate .map file
$(MAP_FILE): $(ELF_FILE)
	@echo Generating map file...
	@$(OBJDUMP) -x $< > $@
	@echo done.
	@echo.

# 🖥️ Generate .bin file
$(BIN_FILE): $(ELF_FILE)
	@echo Generating binary file...
	@$(OBJCOPY) -O binary $< $@
	@echo done.
	@echo.

# 📜 Generate .lst file
$(LST_FILE): $(ELF_FILE)
	@echo Generating list file...
	@$(OBJDUMP) -d $< > $@
	@echo done.	
	@echo.

# 🗃️ Generate .out file
$(OUT_FILE): $(ELF_FILE)
	@echo Generating .out file...
	@$(OBJCOPY) -O binary $< $@
	@echo done.
	@echo.

# 📃 Common tasks
.PHONY: all clean flash bin hex map elf lst out

# 🏗️ Build all
all: $(ELF_FILE) $(HEX_FILE) $(MAP_FILE) $(BIN_FILE) $(LST_FILE) $(OUT_FILE)
	@echo Build completed successfully.
	@echo Output files are located in the $(RELEASE_DIR) directory.
	@echo.

# 🗑️ Cleanup output files
clean:
	@echo Cleaning build and release directories...
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(RELEASE_DIR)" rmdir /S /Q "$(RELEASE_DIR)"
	@echo done.
	@echo.

# 🔥 Flash device
flash: $(ELF_FILE)
	@echo Flashing $(TARGET) to $(PORT)...
	@echo Using baud rate: $(BAUDRATE)	
	@esptool.py --port $(PORT) --baud $(BAUDRATE) write_flash 0x00000 $<
	@echo Flashing completed. Please reset the device to start the program.
	@echo.
