# 🎛️ Signal Plotter

Real-time signal visualization on an ESP8266 with OLED output. Explore signal behavior, frequency response, and waveform dynamics directly from embedded hardware.

---

<h2 id="index">🗂️ Index</h2>

1. [📛 Project Title](#project-title)  
2. [📝 Description](#description)  
3. [👤 Author](#author)  
4. [🔗 GitHub Repository](#github-repository)  
5. [🧱 Project Structure](#project-structure)    
6. [📚 Datasheets](#datasheets)  
7. [🧰 Compiler](#compiler)
8. [📦 Products](#products) 
9. [📄 License](#license)

<h2 id="description">📝 Description</h2>
An embedded C project for real-time signal visualization using an ESP8266 microcontroller and a 128x64 OLED display. Designed to plot waveforms and analyze signal behavior directly on hardware, ideal for educational and experimental signal processing tasks.
[🔝 Back to Index](#index)

<h2 id="author">👤 Author</h2>
- Name: Jesus Salvador Lopez Ortega
- GitHub: [chucholoport](https://github.com/chucholoport)
[🔝 Back to Index](#index)

<h2 id="github-repository">🔗 GitHub Repository</h2>
[Signal Plotter Repository](https://github.com/chucholoport/signal_plotter)
[🔝 Back to Index](#index)

<h2 id="project-structure">🧱 Project Structure</h2>

The following layout outlines the organization of the `signal_plotter` project:
└── signal_plotter/

    ├── Source/
    │   ├── Hal/
    │   │   ├── HalAdc/
    │   │   │   ├── HalAdc_Cfg.h
    │   │   │   └── HalAdc.c
    │   │   ├── HalCom/
    │   │   │   ├── HalCom_Cfg.h
    │   │   │   └── HalCom.c
    │   │   ├── HalDio/
    │   │   │   ├── HalDio_Cfg.h
    │   │   │   └── HalDio.c
    │   │   ├── HalTmr/
    │   │   │   ├── HalTmr_Cfg.h
    │   │   │   └── HalTmr.c
    │   │   └── HalHmi/
    │   │       ├── HalHmi_Cfg.h
    │   │       └── HalHmi.c
    │   ├── Drv/
    │   │   ├── DrvAdc/
    │   │   │   ├── DrvAdc_Cfg.h
    │   │   │   └── DrvAdc.c
    │   │   ├── DrvCom/
    │   │   │   ├── DrvCom_Cfg.h
    │   │   │   └── DrvCom.c
    │   │   ├── DrvDio/
    │   │   │   ├── DrvDio_Cfg.h
    │   │   │   └── DrvDio.c
    │   │   ├── DrvTmr/
    │   │   │   ├── DrvTmr_Cfg.h
    │   │   │   └── DrvTmr.c
    │   │   └── DrvHmi/
    │   │       ├── DrvHmi_Cfg.h
    │   │       └── DrvHmi.c
    │   ├── Dsp/
    │   │   ├── Atcrrltn/
    │   │   │   ├── Atcrrltn_Cfg.h
    │   │   │   └── Atcrrltn.c
    │   │   └── SgnlRtrvr/
    │   │       ├── SgnlRtrvr_Cfg.h
    │   │       └── SgnlRtrvr.c
    │   ├── Hmi/
    │   │   ├── HmiFrq/
    │   │   │   ├── HmiFrq_Cfg.h
    │   │   │   └── HmiFrq.c
    │   │   ├── HmiSgnlPlttr/
    │   │   │   ├── HmiSgnlPlttr_Cfg.h
    │   │   │   └── HmiSgnlPlttr.c
    │   │   ├── HmiSgnlAdjstr/
    │   │   │   ├── HmiSgnlAdjstr_Cfg.h
    │   │   │   └── HmiSgnlAdjstr.c
    │   │   ├── HmiMscNt/
    │   │   │   ├── HmiMscNt_Cfg.h
    │   │   │   └── HmiMscNt.c
    │   │   └── HmiMscCnt/
    │   │       ├── HmiMscCnt_Cfg.h
    │   │       └── HmiMscCnt.c
    │   ├── StMchn/
    │   │   ├── StMchn_Cfg.h
    │   │   └── StMchn.c
    │   └── main.c
    └── BuildTools/
        └── Makefile
[🔝 Back to Index](#index)

<h2 id="datasheets">📚 Datasheets</h2>

The following components are used in this project. Their respective datasheets provide technical specifications and operational details:

- **ESP8266 NodeMCU**  
  [ESP8266 Datasheet (PDF)](https://components101.com/sites/default/files/component_datasheet/ESP8266%20NodeMCU%20Datasheet.pdf)

- **OLED Display — SSD1306 Driver**  
  [SSD1306 Datasheet (PDF)](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)

- **Microphone — MAX4466**  
  [MAX4465–MAX4469 Series Datasheet (PDF)](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX4465-MAX4469.pdf)

[🔝 Back to Index](#index)

<h2 id="compiler">🧰 Compiler</h2>

### 🔧 ESP8266 RTOS SDK Setup

To compile and flash the firmware using the ESP8266 RTOS SDK toolchain, run the setup script located in the `BuildTools` directory:

```bash
source BuildTools/esp-env.sh
```

This script configures the environment variables, activates the virtual environment, and prepares the toolchain paths for building the project.
Make sure you have cloned the customized SDK and mbedtls repositories:
- [ESP8266_RTOS_SDK fork](https://github.com/chucholoport/ESP8266_RTOS_SDK)
- [mbedtls fork](https://github.com/chucholoport/mbedtls)

Future updates to esp-env.sh will include full automation of SDK setup, submodule initialization, and environment provisioning.

[🔝 Back to Index](#index)

<h2 id="products">📦 Products</h2>

Compiled outputs and build artifacts are organized in the `Target` directory:

- **Target/build/**  
  Contains object files generated during compilation:  
  - `.o` files

- **Target/release/**  
  Contains final binary and debug outputs for flashing and analysis:  
  - `.elf` file — Executable and Linkable Format used for linking and flashing  
  - `.hex` file — Intel HEX format used for programming microcontrollers  
  - `.bin` file — Raw binary image, commonly used for direct flashing  
  - `.map` file — Memory map detailing address layout and symbol locations  
  - `.lst` file — Disassembled listing showing instruction-level breakdown  
  - `.out` file — Symbol and source-level analysis combining object code and mappings

[🔝 Back to Index](#index)

<h2 id="license">📄 License</h2>

This project is licensed under the **MIT License**.

You can find the full license text in the following file:  
[LICENSE](LICENSE)

This license permits reuse, modification, distribution, and private use, provided that the original copyright and license notice are included.
[🔝 Back to Index](#index)