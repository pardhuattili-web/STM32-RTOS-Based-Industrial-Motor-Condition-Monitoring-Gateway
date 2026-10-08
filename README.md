# STM32 RTOS-Based Industrial Motor Condition Monitoring Gateway

![MCU](https://img.shields.io/badge/MCU-STM32G4%2FF4-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-informational)
![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-brightgreen)
![Protocol](https://img.shields.io/badge/Protocol-Modbus%20RTU-orange)
![Interface](https://img.shields.io/badge/Physical%20Layer-RS--485-purple)

A portfolio-grade embedded monitoring gateway that samples motor vibration, temperature and current, processes the measurements with deterministic firmware modules, classifies motor health, and exposes diagnostic values through an RS-485 Modbus RTU register model.

## What it demonstrates

- Embedded C modular architecture
- FreeRTOS task decomposition
- ADC/DMA/I2C/SPI acquisition architecture
- Vibration RMS and peak calculations
- Configurable warning/fault health states
- Modbus RTU CRC-16
- RS-485 gateway architecture
- Host-side unit tests
- Fault and sensor-error handling
- Hardware-abstraction boundaries

## Architecture

```
Vibration / Temperature / Current Sensors
                 |
          ADC / DMA / I2C / SPI
                 |
          Acquisition Task
                 |
          FreeRTOS Queue
                 |
       Signal Processing Task
                 |
        Motor Health Engine
          /             \
     Warning           Fault
          \             /
           Modbus Register Bank
                    |
              Modbus RTU Task
                    |
                  RS-485
                    |
                PLC / HMI
```

## Health model

| State | Meaning |
|---|---|
| NORMAL | All monitored values within nominal range |
| WARNING | One or more measurements exceed warning limits |
| FAULT | Critical threshold or sensor error detected |

The reference health engine uses conservative example thresholds; calibrate them for the actual motor, sensor and test bench.

## Modbus register map

| Register | Description | Scaling |
|---|---|---|
| 40001 | Motor state | enum |
| 40002 | Temperature | x10 °C |
| 40003 | RMS current | x100 A |
| 40004 | Vibration RMS | x100 g |
| 40005 | Vibration peak | x100 g |
| 40006 | Warning flags | bit field |
| 40007 | Fault flags | bit field |

CRC-16 follows the standard Modbus polynomial `0xA001` with initial value `0xFFFF`.

## Repository structure

```text
Application/
  Inc/ motor_health.h, system_tasks.h
  Src/ motor_health.c, system_tasks.c
Core/
  Inc/ signal_processing.h
  Src/ signal_processing.c
Protocol/
  Inc/ modbus_crc.h, modbus_map.h
  Src/ modbus_crc.c, modbus_map.c
tests/
tools/
docs/
Makefile.host
```

## Host validation

Run:

```bash
make -f Makefile.host test
```

The test suite checks RMS/peak calculations, normal/fault health classification and the Modbus CRC known vector.

Generate a sample Modbus request:

```bash
python3 tools/modbus_probe.py
```

## STM32 integration

The repository intentionally separates hardware-independent logic from the board layer. Connect the generated STM32CubeMX/HAL drivers for ADC+DMA, I2C/SPI sensors, UART/RS-485 and FreeRTOS task creation in `system_tasks.c`.

Recommended task model:

1. **Acquisition Task** — collect sensor samples.
2. **Processing Task** — calculate RMS/peak/features.
3. **Health Task** — evaluate thresholds and events.
4. **Modbus Task** — service RS-485 requests.
5. **Logger Task** — persist important events.
6. **Watchdog Task** — supervise system liveness.

## Safety boundary

This is a monitoring gateway, not a motor protection relay. Do not connect GPIO/ADC inputs directly to mains voltage. Use appropriately rated isolation, current sensing and signal conditioning, and keep contactor/VFD control outside this reference project unless a properly engineered safety architecture is added.

## Portfolio talking points

**Problem:** detect early signs of motor degradation without continuously streaming raw data.

**Engineering:** separate acquisition, processing, health classification and industrial communications into deterministic modules.

**Interview discussion:** explain RMS vs peak vibration, FreeRTOS queues, DMA buffering, Modbus CRC, RS-485 direction control, threshold hysteresis, fault latching, sensor validation and watchdog recovery.
