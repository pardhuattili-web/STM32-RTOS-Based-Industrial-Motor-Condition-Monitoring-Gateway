# Modbus RTU register map
| Register | Value |
|---|---|
| 40001 | Motor state |
| 40002 | Temperature x10 C |
| 40003 | RMS current x100 A |
| 40004 | Vibration RMS x100 g |
| 40005 | Vibration peak x100 g |
| 40006 | Warning flags |
| 40007 | Fault flags |

CRC-16 uses polynomial 0xA001 and initial value 0xFFFF. RS-485 transceiver direction control belongs in the board/HAL layer.
