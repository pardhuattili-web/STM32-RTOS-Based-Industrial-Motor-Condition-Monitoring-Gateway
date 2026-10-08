# Architecture
Sensors -> ADC/DMA/I2C/SPI acquisition -> FreeRTOS queues -> signal processing -> health state machine -> Modbus register bank -> RS-485.

Recommended tasks: Acquisition (high priority), Processing, Health, Modbus RTU, Event Logger and Watchdog. Keep ISRs short and move computation to tasks.

The gateway is monitoring-only; it must not directly control mains power. Use isolated/current-limited interfaces appropriate to the motor test bench.
