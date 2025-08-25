ADC_COMPONENT := Adc
DIO_COMPONENT := Dio
DSP_COMPONENT := Dsp
HMI_COMPONENT := Hmi
TST_COMPONENT := Tst

SUBCOMPONENTS := \
	$(ADC_COMPONENT) \
	$(DIO_COMPONENT) \
	$(DSP_COMPONENT)/common \
	$(DSP_COMPONENT)/Autocorrelation \
	$(HMI_COMPONENT)/common \
	$(HMI_COMPONENT)/Bitmap \
	$(HMI_COMPONENT)/Message \
	$(HMI_COMPONENT)/Plot \
	$(HMI_COMPONENT)/Symbol \
	$(HMI_COMPONENT)/Ruler \
	$(HMI_COMPONENT)/Needle \
 	$(TST_COMPONENT)/Common \
 	$(TST_COMPONENT)/Trngl
#	$(DSP_COMPONENT)/common \
#	$(DSP_COMPONENT)/AtCrrltn \
#	$(HMI_COMPONENT)/common \
#	$(HMI_COMPONENT)/Message \
#	$(HMI_COMPONENT)/Tuner \
# 	$(TST_COMPONENT)/Common \
# 	$(TST_COMPONENT)/Trngl
# 	$(DSP_COMPONENT)/SgnlBffr \
# 	$(DSP_COMPONENT)/AtCrrltn \
# 	$(HMI_COMPONENT)/common \
# 	$(HMI_COMPONENT)/SgnlPlttr \


COMPONENT_SRCDIRS := $(SUBCOMPONENTS)

COMPONENT_ADD_INCLUDEDIRS := $(SUBCOMPONENTS)