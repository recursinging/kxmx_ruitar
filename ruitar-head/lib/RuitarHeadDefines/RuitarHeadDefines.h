
#define RH_ADDR 0x66
#define RH_FREQ 400000

// Command definitions
#define RH_WRITE    0x10
#define RH_READ     0x20

// Register Map
#define RH_REG_LEN 45 // 45 Bytes for registers
// Read Write Registers
#define RH_K0LEDR   0x00  // RW uint16_t - 0-4095
#define RH_K0LEDG   0x02  // RW uint16_t - 0-4095
#define RH_K0LEDB   0x04  // RW uint16_t - 0-4095

#define RH_K1LEDR   0x06  // RW uint16_t - 0-4095
#define RH_K1LEDG   0x08  // RW uint16_t - 0-4095
#define RH_K1LEDB   0x0a  // RW uint16_t - 0-4095

#define RH_K2LEDR   0x0c  // RW uint16_t - 0-4095
#define RH_K2LEDG   0x0e  // RW uint16_t - 0-4095
#define RH_K2LEDB   0x10  // RW uint16_t - 0-4095

#define RH_K3LEDR   0x12  // RW uint16_t - 0-4095
#define RH_K3LEDG   0x14  // RW uint16_t - 0-4095
#define RH_K3LEDB   0x16  // RW uint16_t - 0-4095

#define RH_FLAGS    0x18  // RW uint8_t - Bit Coded
// 0x19 - 0x1f reserved
// 0x20 - Read Write boundary - no writes allowed past this index
// Read Only Registers
#define RH_STATE    0x20  // RO uint8_t - Bit Coded
#define RH_K0CNT    0x21  // RO int8_t - Knob 0 counter
#define RH_K1CNT    0x22  // RO int8_t - Knob 1 counter
#define RH_K2CNT    0x23  // RO int8_t - Knob 2 counter
#define RH_K3CNT    0x24  // RO int8_t - Knob 3 counter
#define RH_ACCLX    0x25  // RO int16_t
#define RH_ACCLY    0x27  // RO int16_t
#define RH_ACCLZ    0x29  // RO int16_t
#define RH_RFRSH    0x2b  // RO int16_t - Refresh rate in Hz

// State Bit Definitions
#define RH_SW0BIT   0
#define RH_SW1BIT   1
#define RH_SW2BIT   2
#define RH_SW3BIT   3
