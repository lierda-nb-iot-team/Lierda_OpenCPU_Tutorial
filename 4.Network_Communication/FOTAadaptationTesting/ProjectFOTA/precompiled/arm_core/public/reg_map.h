#ifndef REG_MAP_APPS_H
#define REG_MAP_APPS_H

/** @addtogroup HI21XX_ARMCORE_APPS
 * @{
 * */

// apps_regs register definitions
#define TIMER0_LOAD (*(volatile unsigned long *)(0x40004000))
#define TIMER0_LOAD_BITSET (*(volatile unsigned long *)(0x40004400))
#define TIMER0_LOAD_BITCLR (*(volatile unsigned long *)(0x40004800))
#define TIMER0_LOAD_BITTOG (*(volatile unsigned long *)(0x40004C00))
#define TIMER0_CTRL (*(volatile unsigned long *)(0x40004004))
#define TIMER0_CTRL_BITSET (*(volatile unsigned long *)(0x40004404))
#define TIMER0_CTRL_BITCLR (*(volatile unsigned long *)(0x40004804))
#define TIMER0_CTRL_BITTOG (*(volatile unsigned long *)(0x40004C04))
#define TIMER0_TIME (*(volatile unsigned long *)(0x40004008))
#define TIMER0_SCALER (*(volatile unsigned long *)(0x4000400C))
#define TIMER0_SCALER_BITSET (*(volatile unsigned long *)(0x4000440C))
#define TIMER0_SCALER_BITCLR (*(volatile unsigned long *)(0x4000480C))
#define TIMER0_SCALER_BITTOG (*(volatile unsigned long *)(0x40004C0C))
#define ARM_IRQ_REG (*(volatile unsigned long *)(0x40004010))
#define ARM_IRQ_REG_BITSET (*(volatile unsigned long *)(0x40004410))
#define ARM_IRQ_REG_BITCLR (*(volatile unsigned long *)(0x40004810))
#define ARM_IRQ_REG_BITTOG (*(volatile unsigned long *)(0x40004C10))
#define WDT_INTERVAL (*(volatile unsigned long *)(0x40004014))
#define WDT_INTERVAL_BITSET (*(volatile unsigned long *)(0x40004414))
#define WDT_INTERVAL_BITCLR (*(volatile unsigned long *)(0x40004814))
#define WDT_INTERVAL_BITTOG (*(volatile unsigned long *)(0x40004C14))
#define WDT_CTRL (*(volatile unsigned long *)(0x40004018))
#define WDT_CTRL_BITSET (*(volatile unsigned long *)(0x40004418))
#define WDT_CTRL_BITCLR (*(volatile unsigned long *)(0x40004818))
#define WDT_CTRL_BITTOG (*(volatile unsigned long *)(0x40004C18))
#define WDT_TIME (*(volatile unsigned long *)(0x4000401C))
#define GPIO_VALUE (*(volatile unsigned long *)(0x40004020))
#define GPIO_VALUE_MS (*(volatile unsigned long *)(0x40004024))
#define GPIO_IRQ (*(volatile unsigned long *)(0x40004028))
#define GPIO_IRQ_MS (*(volatile unsigned long *)(0x4000402C))
#define RESET_CAUSE (*(volatile unsigned long *)(0x40004030))
#define PWM0_CTRL (*(volatile unsigned long *)(0x40004034))
#define PWM0_CTRL_BITSET (*(volatile unsigned long *)(0x40004434))
#define PWM0_CTRL_BITCLR (*(volatile unsigned long *)(0x40004834))
#define PWM0_CTRL_BITTOG (*(volatile unsigned long *)(0x40004C34))
#define PWM0_COUNT (*(volatile unsigned long *)(0x40004038))
#define PWM0_COUNT_BITSET (*(volatile unsigned long *)(0x40004438))
#define PWM0_COUNT_BITCLR (*(volatile unsigned long *)(0x40004838))
#define PWM0_COUNT_BITTOG (*(volatile unsigned long *)(0x40004C38))
#define PWM1_CTRL (*(volatile unsigned long *)(0x4000403C))
#define PWM1_CTRL_BITSET (*(volatile unsigned long *)(0x4000443C))
#define PWM1_CTRL_BITCLR (*(volatile unsigned long *)(0x4000483C))
#define PWM1_CTRL_BITTOG (*(volatile unsigned long *)(0x40004C3C))
#define PWM1_COUNT (*(volatile unsigned long *)(0x40004040))
#define PWM1_COUNT_BITSET (*(volatile unsigned long *)(0x40004440))
#define PWM1_COUNT_BITCLR (*(volatile unsigned long *)(0x40004840))
#define PWM1_COUNT_BITTOG (*(volatile unsigned long *)(0x40004C40))
#define PWM_STATUS (*(volatile unsigned long *)(0x40004044))
#define CLKEN_REG (*(volatile unsigned long *)(0x40004048))
#define CLKEN_REG_BITSET (*(volatile unsigned long *)(0x40004448))
#define CLKEN_REG_BITCLR (*(volatile unsigned long *)(0x40004848))
#define CLKEN_REG_BITTOG (*(volatile unsigned long *)(0x40004C48))
#define I2C0_INTERRUPT_STATUS (*(volatile unsigned long *)(0x4000404C))
#define I2C0_INTERRUPT_CLEAR (*(volatile unsigned long *)(0x40004050))
#define I2C0_INTERRUPT_CLEAR_BITSET (*(volatile unsigned long *)(0x40004450))
#define I2C0_INTERRUPT_CLEAR_BITCLR (*(volatile unsigned long *)(0x40004850))
#define I2C0_INTERRUPT_CLEAR_BITTOG (*(volatile unsigned long *)(0x40004C50))
#define I2C0_INTERRUPT_ENABLE (*(volatile unsigned long *)(0x40004054))
#define I2C0_INTERRUPT_ENABLE_BITSET (*(volatile unsigned long *)(0x40004454))
#define I2C0_INTERRUPT_ENABLE_BITCLR (*(volatile unsigned long *)(0x40004854))
#define I2C0_INTERRUPT_ENABLE_BITTOG (*(volatile unsigned long *)(0x40004C54))
#define I2C0_MODE (*(volatile unsigned long *)(0x40004058))
#define I2C0_MODE_BITSET (*(volatile unsigned long *)(0x40004458))
#define I2C0_MODE_BITCLR (*(volatile unsigned long *)(0x40004858))
#define I2C0_MODE_BITTOG (*(volatile unsigned long *)(0x40004C58))
#define I2C0_TX_DATA (*(volatile unsigned long *)(0x4000405C))
#define I2C0_TX_DATA_BITSET (*(volatile unsigned long *)(0x4000445C))
#define I2C0_TX_DATA_BITCLR (*(volatile unsigned long *)(0x4000485C))
#define I2C0_TX_DATA_BITTOG (*(volatile unsigned long *)(0x40004C5C))
#define I2C0_RX_DATA (*(volatile unsigned long *)(0x40004060))
#define I2C0_TX_RD_WRB (*(volatile unsigned long *)(0x40004064))
#define I2C0_TX_RD_WRB_BITSET (*(volatile unsigned long *)(0x40004464))
#define I2C0_TX_RD_WRB_BITCLR (*(volatile unsigned long *)(0x40004864))
#define I2C0_TX_RD_WRB_BITTOG (*(volatile unsigned long *)(0x40004C64))
#define I2C0_TX_NO_BYTES (*(volatile unsigned long *)(0x40004068))
#define I2C0_TX_NO_BYTES_BITSET (*(volatile unsigned long *)(0x40004468))
#define I2C0_TX_NO_BYTES_BITCLR (*(volatile unsigned long *)(0x40004868))
#define I2C0_TX_NO_BYTES_BITTOG (*(volatile unsigned long *)(0x40004C68))
#define I2C0_RX_NO_BYTES (*(volatile unsigned long *)(0x4000406C))
#define I2C0_RX_NO_BYTES_MASTER (*(volatile unsigned long *)(0x40004070))
#define I2C0_RX_NO_BYTES_MASTER_BITSET (*(volatile unsigned long *)(0x40004470))
#define I2C0_RX_NO_BYTES_MASTER_BITCLR (*(volatile unsigned long *)(0x40004870))
#define I2C0_RX_NO_BYTES_MASTER_BITTOG (*(volatile unsigned long *)(0x40004C70))
#define I2C0_GO (*(volatile unsigned long *)(0x40004074))
#define I2C0_GO_BITSET (*(volatile unsigned long *)(0x40004474))
#define I2C0_GO_BITCLR (*(volatile unsigned long *)(0x40004874))
#define I2C0_GO_BITTOG (*(volatile unsigned long *)(0x40004C74))
#define I2C0_RX_EARLY_THRESHOLD (*(volatile unsigned long *)(0x40004078))
#define I2C0_RX_EARLY_THRESHOLD_BITSET (*(volatile unsigned long *)(0x40004478))
#define I2C0_RX_EARLY_THRESHOLD_BITCLR (*(volatile unsigned long *)(0x40004878))
#define I2C0_RX_EARLY_THRESHOLD_BITTOG (*(volatile unsigned long *)(0x40004C78))
#define I2C0_RX_AUTO_NAG_BYTE_CNT (*(volatile unsigned long *)(0x4000407C))
#define I2C0_RX_AUTO_NAG_BYTE_CNT_BITSET (*(volatile unsigned long *)(0x4000447C))
#define I2C0_RX_AUTO_NAG_BYTE_CNT_BITCLR (*(volatile unsigned long *)(0x4000487C))
#define I2C0_RX_AUTO_NAG_BYTE_CNT_BITTOG (*(volatile unsigned long *)(0x40004C7C))
#define I2C0_HALF_TIME (*(volatile unsigned long *)(0x40004080))
#define I2C0_HALF_TIME_BITSET (*(volatile unsigned long *)(0x40004480))
#define I2C0_HALF_TIME_BITCLR (*(volatile unsigned long *)(0x40004880))
#define I2C0_HALF_TIME_BITTOG (*(volatile unsigned long *)(0x40004C80))
#define I2C0_ADDRESS (*(volatile unsigned long *)(0x40004084))
#define I2C0_ADDRESS_BITSET (*(volatile unsigned long *)(0x40004484))
#define I2C0_ADDRESS_BITCLR (*(volatile unsigned long *)(0x40004884))
#define I2C0_ADDRESS_BITTOG (*(volatile unsigned long *)(0x40004C84))
#define I2C0_ADDR_TYPE (*(volatile unsigned long *)(0x40004088))
#define I2C0_ADDR_TYPE_BITSET (*(volatile unsigned long *)(0x40004488))
#define I2C0_ADDR_TYPE_BITCLR (*(volatile unsigned long *)(0x40004888))
#define I2C0_ADDR_TYPE_BITTOG (*(volatile unsigned long *)(0x40004C88))
#define I2C0_SOFT_RESET (*(volatile unsigned long *)(0x4000408C))
#define I2C0_SOFT_RESET_BITSET (*(volatile unsigned long *)(0x4000448C))
#define I2C0_SOFT_RESET_BITCLR (*(volatile unsigned long *)(0x4000488C))
#define I2C0_SOFT_RESET_BITTOG (*(volatile unsigned long *)(0x40004C8C))
#define I2C0_SLAVE_RWB (*(volatile unsigned long *)(0x40004090))
#define I2C0_MASTER_SM (*(volatile unsigned long *)(0x40004094))
#define I2C0_SLAVE_SM (*(volatile unsigned long *)(0x40004098))
#define I2C0_SLAVE_ENABLE (*(volatile unsigned long *)(0x4000409C))
#define I2C0_SLAVE_ENABLE_BITSET (*(volatile unsigned long *)(0x4000449C))
#define I2C0_SLAVE_ENABLE_BITCLR (*(volatile unsigned long *)(0x4000489C))
#define I2C0_SLAVE_ENABLE_BITTOG (*(volatile unsigned long *)(0x40004C9C))
#define I2C0_MASTER_SEND_RESTART (*(volatile unsigned long *)(0x400040A0))
#define I2C0_MASTER_SEND_RESTART_BITSET (*(volatile unsigned long *)(0x400044A0))
#define I2C0_MASTER_SEND_RESTART_BITCLR (*(volatile unsigned long *)(0x400048A0))
#define I2C0_MASTER_SEND_RESTART_BITTOG (*(volatile unsigned long *)(0x40004CA0))
#define I2C0_RX_FIFO_LEVEL (*(volatile unsigned long *)(0x400040A4))
#define I2C1_INTERRUPT_STATUS (*(volatile unsigned long *)(0x400040A8))
#define I2C1_INTERRUPT_CLEAR (*(volatile unsigned long *)(0x400040AC))
#define I2C1_INTERRUPT_CLEAR_BITSET (*(volatile unsigned long *)(0x400044AC))
#define I2C1_INTERRUPT_CLEAR_BITCLR (*(volatile unsigned long *)(0x400048AC))
#define I2C1_INTERRUPT_CLEAR_BITTOG (*(volatile unsigned long *)(0x40004CAC))
#define I2C1_INTERRUPT_ENABLE (*(volatile unsigned long *)(0x400040B0))
#define I2C1_INTERRUPT_ENABLE_BITSET (*(volatile unsigned long *)(0x400044B0))
#define I2C1_INTERRUPT_ENABLE_BITCLR (*(volatile unsigned long *)(0x400048B0))
#define I2C1_INTERRUPT_ENABLE_BITTOG (*(volatile unsigned long *)(0x40004CB0))
#define I2C1_MODE (*(volatile unsigned long *)(0x400040B4))
#define I2C1_MODE_BITSET (*(volatile unsigned long *)(0x400044B4))
#define I2C1_MODE_BITCLR (*(volatile unsigned long *)(0x400048B4))
#define I2C1_MODE_BITTOG (*(volatile unsigned long *)(0x40004CB4))
#define I2C1_TX_DATA (*(volatile unsigned long *)(0x400040B8))
#define I2C1_TX_DATA_BITSET (*(volatile unsigned long *)(0x400044B8))
#define I2C1_TX_DATA_BITCLR (*(volatile unsigned long *)(0x400048B8))
#define I2C1_TX_DATA_BITTOG (*(volatile unsigned long *)(0x40004CB8))
#define I2C1_RX_DATA (*(volatile unsigned long *)(0x400040BC))
#define I2C1_TX_RD_WRB (*(volatile unsigned long *)(0x400040C0))
#define I2C1_TX_RD_WRB_BITSET (*(volatile unsigned long *)(0x400044C0))
#define I2C1_TX_RD_WRB_BITCLR (*(volatile unsigned long *)(0x400048C0))
#define I2C1_TX_RD_WRB_BITTOG (*(volatile unsigned long *)(0x40004CC0))
#define I2C1_TX_NO_BYTES (*(volatile unsigned long *)(0x400040C4))
#define I2C1_TX_NO_BYTES_BITSET (*(volatile unsigned long *)(0x400044C4))
#define I2C1_TX_NO_BYTES_BITCLR (*(volatile unsigned long *)(0x400048C4))
#define I2C1_TX_NO_BYTES_BITTOG (*(volatile unsigned long *)(0x40004CC4))
#define I2C1_RX_NO_BYTES (*(volatile unsigned long *)(0x400040C8))
#define I2C1_RX_NO_BYTES_MASTER (*(volatile unsigned long *)(0x400040CC))
#define I2C1_RX_NO_BYTES_MASTER_BITSET (*(volatile unsigned long *)(0x400044CC))
#define I2C1_RX_NO_BYTES_MASTER_BITCLR (*(volatile unsigned long *)(0x400048CC))
#define I2C1_RX_NO_BYTES_MASTER_BITTOG (*(volatile unsigned long *)(0x40004CCC))
#define I2C1_GO (*(volatile unsigned long *)(0x400040D0))
#define I2C1_GO_BITSET (*(volatile unsigned long *)(0x400044D0))
#define I2C1_GO_BITCLR (*(volatile unsigned long *)(0x400048D0))
#define I2C1_GO_BITTOG (*(volatile unsigned long *)(0x40004CD0))
#define I2C1_RX_EARLY_THRESHOLD (*(volatile unsigned long *)(0x400040D4))
#define I2C1_RX_EARLY_THRESHOLD_BITSET (*(volatile unsigned long *)(0x400044D4))
#define I2C1_RX_EARLY_THRESHOLD_BITCLR (*(volatile unsigned long *)(0x400048D4))
#define I2C1_RX_EARLY_THRESHOLD_BITTOG (*(volatile unsigned long *)(0x40004CD4))
#define I2C1_RX_AUTO_NAG_BYTE_CNT (*(volatile unsigned long *)(0x400040D8))
#define I2C1_RX_AUTO_NAG_BYTE_CNT_BITSET (*(volatile unsigned long *)(0x400044D8))
#define I2C1_RX_AUTO_NAG_BYTE_CNT_BITCLR (*(volatile unsigned long *)(0x400048D8))
#define I2C1_RX_AUTO_NAG_BYTE_CNT_BITTOG (*(volatile unsigned long *)(0x40004CD8))
#define I2C1_HALF_TIME (*(volatile unsigned long *)(0x400040DC))
#define I2C1_HALF_TIME_BITSET (*(volatile unsigned long *)(0x400044DC))
#define I2C1_HALF_TIME_BITCLR (*(volatile unsigned long *)(0x400048DC))
#define I2C1_HALF_TIME_BITTOG (*(volatile unsigned long *)(0x40004CDC))
#define I2C1_ADDRESS (*(volatile unsigned long *)(0x400040E0))
#define I2C1_ADDRESS_BITSET (*(volatile unsigned long *)(0x400044E0))
#define I2C1_ADDRESS_BITCLR (*(volatile unsigned long *)(0x400048E0))
#define I2C1_ADDRESS_BITTOG (*(volatile unsigned long *)(0x40004CE0))
#define I2C1_ADDR_TYPE (*(volatile unsigned long *)(0x400040E4))
#define I2C1_ADDR_TYPE_BITSET (*(volatile unsigned long *)(0x400044E4))
#define I2C1_ADDR_TYPE_BITCLR (*(volatile unsigned long *)(0x400048E4))
#define I2C1_ADDR_TYPE_BITTOG (*(volatile unsigned long *)(0x40004CE4))
#define I2C1_SOFT_RESET (*(volatile unsigned long *)(0x400040E8))
#define I2C1_SOFT_RESET_BITSET (*(volatile unsigned long *)(0x400044E8))
#define I2C1_SOFT_RESET_BITCLR (*(volatile unsigned long *)(0x400048E8))
#define I2C1_SOFT_RESET_BITTOG (*(volatile unsigned long *)(0x40004CE8))
#define I2C1_SLAVE_RWB (*(volatile unsigned long *)(0x400040EC))
#define I2C1_MASTER_SM (*(volatile unsigned long *)(0x400040F0))
#define I2C1_SLAVE_SM (*(volatile unsigned long *)(0x400040F4))
#define I2C1_SLAVE_ENABLE (*(volatile unsigned long *)(0x400040F8))
#define I2C1_SLAVE_ENABLE_BITSET (*(volatile unsigned long *)(0x400044F8))
#define I2C1_SLAVE_ENABLE_BITCLR (*(volatile unsigned long *)(0x400048F8))
#define I2C1_SLAVE_ENABLE_BITTOG (*(volatile unsigned long *)(0x40004CF8))
#define I2C1_MASTER_SEND_RESTART (*(volatile unsigned long *)(0x400040FC))
#define I2C1_MASTER_SEND_RESTART_BITSET (*(volatile unsigned long *)(0x400044FC))
#define I2C1_MASTER_SEND_RESTART_BITCLR (*(volatile unsigned long *)(0x400048FC))
#define I2C1_MASTER_SEND_RESTART_BITTOG (*(volatile unsigned long *)(0x40004CFC))
#define I2C1_RX_FIFO_LEVEL (*(volatile unsigned long *)(0x40004100))
#define DMA_MUX (*(volatile unsigned long *)(0x40004104))
#define DMA_MUX_BITSET (*(volatile unsigned long *)(0x40004504))
#define DMA_MUX_BITCLR (*(volatile unsigned long *)(0x40004904))
#define DMA_MUX_BITTOG (*(volatile unsigned long *)(0x40004D04))
#define DMA_CTRL_STAT (*(volatile unsigned long *)(0x40004108))
#define CORE_ENABLE_SWD_ACCESS_APPS (*(volatile unsigned long *)(0x4000410C))
#define CORE_ENABLE_SWD_ACCESS_APPS_BITSET (*(volatile unsigned long *)(0x4000450C))
#define CORE_ENABLE_SWD_ACCESS_APPS_BITCLR (*(volatile unsigned long *)(0x4000490C))
#define CORE_ENABLE_SWD_ACCESS_APPS_BITTOG (*(volatile unsigned long *)(0x40004D0C))
#define APPS_DEBUGGER_TO_CORE_DATA (*(volatile unsigned long *)(0x40004110))
#define APPS_CORE_TO_DEBUGGER_DATA (*(volatile unsigned long *)(0x40004114))
#define APPS_CORE_TO_DEBUGGER_DATA_BITSET (*(volatile unsigned long *)(0x40004514))
#define APPS_CORE_TO_DEBUGGER_DATA_BITCLR (*(volatile unsigned long *)(0x40004914))
#define APPS_CORE_TO_DEBUGGER_DATA_BITTOG (*(volatile unsigned long *)(0x40004D14))
#define APPS_DEBUG_DATA_TO_CORE_AVAILABLE (*(volatile unsigned long *)(0x40004118))
#define APPS_DEBUG_DATA_TO_CORE_ACCEPTED (*(volatile unsigned long *)(0x4000411C))
#define APPS_DEBUG_DATA_TO_CORE_ACCEPTED_BITSET (*(volatile unsigned long *)(0x4000451C))
#define APPS_DEBUG_DATA_TO_CORE_ACCEPTED_BITCLR (*(volatile unsigned long *)(0x4000491C))
#define APPS_DEBUG_DATA_TO_CORE_ACCEPTED_BITTOG (*(volatile unsigned long *)(0x40004D1C))
#define APPS_CORE_DATA_TO_DEBUGGER_AVAILABLE (*(volatile unsigned long *)(0x40004120))
#define APPS_CORE_DATA_TO_DEBUGGER_AVAILABLE_BITSET (*(volatile unsigned long *)(0x40004520))
#define APPS_CORE_DATA_TO_DEBUGGER_AVAILABLE_BITCLR (*(volatile unsigned long *)(0x40004920))
#define APPS_CORE_DATA_TO_DEBUGGER_AVAILABLE_BITTOG (*(volatile unsigned long *)(0x40004D20))
#define APPS_CORE_DATA_TO_DEBUGGER_ACCEPTED (*(volatile unsigned long *)(0x40004124))
#define SWD_REQUEST (*(volatile unsigned long *)(0x40004128))
#define RESET_REG (*(volatile unsigned long *)(0x4000412C))
#define RESET_REG_BITSET (*(volatile unsigned long *)(0x4000452C))
#define RESET_REG_BITCLR (*(volatile unsigned long *)(0x4000492C))
#define RESET_REG_BITTOG (*(volatile unsigned long *)(0x40004D2C))

// copied from protocol_core/reg_map.h to make it build
#define COMP0_CLAIM (*(volatile unsigned long *)(0x40001A00))
#define COMP0_CTRL (*(volatile unsigned long *)(0x40001A04))
#define COMP0_STAT (*(volatile unsigned long *)(0x40001A08))
#define COMP0_CTRL_BITSET (*(volatile unsigned long *)(0x40001A14))
#define COMP0_CTRL_BITCLR (*(volatile unsigned long *)(0x40001A24))
#define COMP0_CTRL_BITTOG (*(volatile unsigned long *)(0x40001A34))
#define COMP1_CLAIM (*(volatile unsigned long *)(0x40001A40))
#define COMP1_CTRL (*(volatile unsigned long *)(0x40001A44))
#define COMP1_STAT (*(volatile unsigned long *)(0x40001A48))
#define COMP1_CTRL_BITSET (*(volatile unsigned long *)(0x40001A54))
#define COMP1_CTRL_BITCLR (*(volatile unsigned long *)(0x40001A64))
#define COMP1_CTRL_BITTOG (*(volatile unsigned long *)(0x40001A74))
#define EDGE0_CLAIM (*(volatile unsigned long *)(0x40001A80))
#define EDGE0_CTRL (*(volatile unsigned long *)(0x40001A84))
#define EDGE0_STAT (*(volatile unsigned long *)(0x40001A88))
#define EDGE0_CTRL_BITSET (*(volatile unsigned long *)(0x40001A94))
#define EDGE0_CTRL_BITCLR (*(volatile unsigned long *)(0x40001AA4))
#define EDGE0_CTRL_BITTOG (*(volatile unsigned long *)(0x40001AB4))
#define EDGE1_CLAIM (*(volatile unsigned long *)(0x40001AC0))
#define EDGE1_CTRL (*(volatile unsigned long *)(0x40001AC4))
#define EDGE1_STAT (*(volatile unsigned long *)(0x40001AC8))
#define EDGE1_CTRL_BITSET (*(volatile unsigned long *)(0x40001AD4))
#define EDGE1_CTRL_BITCLR (*(volatile unsigned long *)(0x40001AE4))
#define EDGE1_CTRL_BITTOG (*(volatile unsigned long *)(0x40001AF4))

/*typedef struct {
   uint32 TIMER0_LOAD;
   uint32 TIMER0_CTRL;
   uint32 TIMER0_TIME;
   uint32 TIMER0_SCALER;
   uint32 ARM_IRQ_REG;
   uint32 WDT_INTERVAL;
   uint32 WDT_CTRL;
   uint32 WDT_TIME;
   uint32 GPIO_VALUE;
   uint32 GPIO_VALUE_MS;
   uint32 GPIO_IRQ;
   uint32 GPIO_IRQ_MS;
   uint32 PWM0_CTRL;
   uint32 PWM0_COUNT;
   uint32 PWM1_CTRL;
   uint32 PWM1_COUNT;
   uint32 PWM_STATUS;
   uint32 CLKEN_REG;
   uint32 I2C0_INTERRUPT_STATUS;
   uint32 I2C0_INTERRUPT_CLEAR;
   uint32 I2C0_INTERRUPT_ENABLE;
   uint32 I2C0_MODE;
   uint32 I2C0_TX_DATA;
   uint32 I2C0_TX_RD_WRB;
   uint32 I2C0_TX_NO_BYTES;
   uint32 I2C0_RX_NO_BYTES;
   uint32 I2C0_RX_NO_BYTES_MASTER;
   uint32 I2C0_GO;
   uint32 I2C0_RX_EARLY_THRESHOLD;
   uint32 I2C0_RX_AUTO_NAG_BYTE_CNT;
   uint32 I2C0_HALF_TIME;
   uint32 I2C0_ADDRESS;
   uint32 I2C0_ADDR_TYPE;
   uint32 I2C0_SOFT_RESET;
   uint32 I2C0_SLAVE_RWB;
   uint32 I2C0_MASTER_SM;
   uint32 I2C0_SLAVE_SM;
   uint32 I2C0_SLAVE_ENABLE;
   uint32 I2C0_MASTER_SEND_RESTART;
   uint32 I2C0_RX_FIFO_LEVEL;
   uint32 I2C1_INTERRUPT_STATUS;
   uint32 I2C1_INTERRUPT_CLEAR;
   uint32 I2C1_INTERRUPT_ENABLE;
   uint32 I2C1_MODE;
   uint32 I2C1_TX_DATA;
   uint32 I2C1_TX_RD_WRB;
   uint32 I2C1_TX_NO_BYTES;
   uint32 I2C1_RX_NO_BYTES;
   uint32 I2C1_RX_NO_BYTES_MASTER;
   uint32 I2C1_GO;
   uint32 I2C1_RX_EARLY_THRESHOLD;
   uint32 I2C1_RX_AUTO_NAG_BYTE_CNT;
   uint32 I2C1_HALF_TIME;
   uint32 I2C1_ADDRESS;
   uint32 I2C1_ADDR_TYPE;
   uint32 I2C1_SOFT_RESET;
   uint32 I2C1_SLAVE_RWB;
   uint32 I2C1_MASTER_SM;
   uint32 I2C1_SLAVE_SM;
   uint32 I2C1_SLAVE_ENABLE;
   uint32 I2C1_MASTER_SEND_RESTART;
   uint32 I2C1_RX_FIFO_LEVEL;
   uint32 DMA_MUX;
   uint32 DMA_CTRL_STAT;
   uint32 CORE_ENABLE_SWD_ACCESS_APPS;
   uint32 APPS_DEBUGGER_TO_CORE_DATA;
   uint32 APPS_CORE_TO_DEBUGGER_DATA;
   uint32 APPS_DEBUG_DATA_TO_CORE_AVAILABLE;
   uint32 APPS_DEBUG_DATA_TO_CORE_ACCEPTED;
   uint32 APPS_CORE_DATA_TO_DEBUGGER_AVAILABLE;
   uint32 APPS_CORE_DATA_TO_DEBUGGER_ACCEPTED;
   uint32 SWD_REQUEST;
   uint32 RESET_REG;
   uint32 empty0;
   uint32 empty1;
   uint32 empty2;
   uint32 RESET_CAUSE;
   uint32 empty3;
   uint32 empty4;
   uint32 empty5;
   uint32 I2C0_RX_DATA;
   uint32 empty6;
   uint32 empty7;
   uint32 empty8;
   uint32 I2C1_RX_DATA;
} apps_regs_t;*/

// man_regs register definitions
#define DIGITAL_VERSION (*(volatile unsigned long *)(0x40000000))
#define CLK_FREQ_DAC (*(volatile unsigned long *)(0x40000004))
#define CLK_FREQ_SET (*(volatile unsigned long *)(0x40000008))
#define CLK_FREQ_SET_BITSET (*(volatile unsigned long *)(0x40000408))
#define CLK_FREQ_SET_BITCLR (*(volatile unsigned long *)(0x40000808))
#define CLK_FREQ_SET_BITTOG (*(volatile unsigned long *)(0x40000C08))
#define CLK_FREQ_NREFCLKS (*(volatile unsigned long *)(0x4000000C))
#define CLK_FREQ_NREFCLKS_BITSET (*(volatile unsigned long *)(0x4000040C))
#define CLK_FREQ_NREFCLKS_BITCLR (*(volatile unsigned long *)(0x4000080C))
#define CLK_FREQ_NREFCLKS_BITTOG (*(volatile unsigned long *)(0x40000C0C))
#define CLK_FREQ_REF_SEL (*(volatile unsigned long *)(0x40000010))
#define CLK_FREQ_REF_SEL_BITSET (*(volatile unsigned long *)(0x40000410))
#define CLK_FREQ_REF_SEL_BITCLR (*(volatile unsigned long *)(0x40000810))
#define CLK_FREQ_REF_SEL_BITTOG (*(volatile unsigned long *)(0x40000C10))
#define CLK_FREQ_DIG_CLKS (*(volatile unsigned long *)(0x40000014))
#define CLK_FREQ_HIGHTARGET (*(volatile unsigned long *)(0x40000018))
#define CLK_FREQ_HIGHTARGET_BITSET (*(volatile unsigned long *)(0x40000418))
#define CLK_FREQ_HIGHTARGET_BITCLR (*(volatile unsigned long *)(0x40000818))
#define CLK_FREQ_HIGHTARGET_BITTOG (*(volatile unsigned long *)(0x40000C18))
#define CLK_FREQ_LOWTARGET (*(volatile unsigned long *)(0x4000001C))
#define CLK_FREQ_LOWTARGET_BITSET (*(volatile unsigned long *)(0x4000041C))
#define CLK_FREQ_LOWTARGET_BITCLR (*(volatile unsigned long *)(0x4000081C))
#define CLK_FREQ_LOWTARGET_BITTOG (*(volatile unsigned long *)(0x40000C1C))
#define CLK_FREQ_LP_BACKOFF (*(volatile unsigned long *)(0x40000020))
#define CLK_FREQ_LP_BACKOFF_BITSET (*(volatile unsigned long *)(0x40000420))
#define CLK_FREQ_LP_BACKOFF_BITCLR (*(volatile unsigned long *)(0x40000820))
#define CLK_FREQ_LP_BACKOFF_BITTOG (*(volatile unsigned long *)(0x40000C20))
#define CLK_FREQ_ENABLE (*(volatile unsigned long *)(0x40000024))
#define CLK_FREQ_ENABLE_BITSET (*(volatile unsigned long *)(0x40000424))
#define CLK_FREQ_ENABLE_BITCLR (*(volatile unsigned long *)(0x40000824))
#define CLK_FREQ_ENABLE_BITTOG (*(volatile unsigned long *)(0x40000C24))
#define CLK_GATE_SYS (*(volatile unsigned long *)(0x40000028))
#define CLK_GATE_SYS_BITSET (*(volatile unsigned long *)(0x40000428))
#define CLK_GATE_SYS_BITCLR (*(volatile unsigned long *)(0x40000828))
#define CLK_GATE_SYS_BITTOG (*(volatile unsigned long *)(0x40000C28))
#define CLK_GATE_MODEM (*(volatile unsigned long *)(0x4000002C))
#define CLK_GATE_MODEM_BITSET (*(volatile unsigned long *)(0x4000042C))
#define CLK_GATE_MODEM_BITCLR (*(volatile unsigned long *)(0x4000082C))
#define CLK_GATE_MODEM_BITTOG (*(volatile unsigned long *)(0x40000C2C))
#define CLK_GATE_RADIO (*(volatile unsigned long *)(0x40000030))
#define CLK_GATE_RADIO_BITSET (*(volatile unsigned long *)(0x40000430))
#define CLK_GATE_RADIO_BITCLR (*(volatile unsigned long *)(0x40000830))
#define CLK_GATE_RADIO_BITTOG (*(volatile unsigned long *)(0x40000C30))
#define CLK_GATE_DEBUG (*(volatile unsigned long *)(0x40000034))
#define CLK_GATE_DEBUG_BITSET (*(volatile unsigned long *)(0x40000434))
#define CLK_GATE_DEBUG_BITCLR (*(volatile unsigned long *)(0x40000834))
#define CLK_GATE_DEBUG_BITTOG (*(volatile unsigned long *)(0x40000C34))
#define LPC_CTRL (*(volatile unsigned long *)(0x40000038))
#define LPC_CTRL_BITSET (*(volatile unsigned long *)(0x40000438))
#define LPC_CTRL_BITCLR (*(volatile unsigned long *)(0x40000838))
#define LPC_CTRL_BITTOG (*(volatile unsigned long *)(0x40000C38))
#define LPC_TEST (*(volatile unsigned long *)(0x4000003C))
#define LPC_TEST_BITSET (*(volatile unsigned long *)(0x4000043C))
#define LPC_TEST_BITCLR (*(volatile unsigned long *)(0x4000083C))
#define LPC_TEST_BITTOG (*(volatile unsigned long *)(0x40000C3C))
#define PMU_CTRL0 (*(volatile unsigned long *)(0x40000040))
#define PMU_CTRL0_BITSET (*(volatile unsigned long *)(0x40000440))
#define PMU_CTRL0_BITCLR (*(volatile unsigned long *)(0x40000840))
#define PMU_CTRL0_BITTOG (*(volatile unsigned long *)(0x40000C40))
#define PMU_CTRL1 (*(volatile unsigned long *)(0x40000044))
#define PMU_CTRL1_BITSET (*(volatile unsigned long *)(0x40000444))
#define PMU_CTRL1_BITCLR (*(volatile unsigned long *)(0x40000844))
#define PMU_CTRL1_BITTOG (*(volatile unsigned long *)(0x40000C44))
#define APP_CTRL0 (*(volatile unsigned long *)(0x40000048))
#define APP_CTRL0_BITSET (*(volatile unsigned long *)(0x40000448))
#define APP_CTRL0_BITCLR (*(volatile unsigned long *)(0x40000848))
#define APP_CTRL0_BITTOG (*(volatile unsigned long *)(0x40000C48))
#define APP_CTRL1 (*(volatile unsigned long *)(0x4000004C))
#define APP_CTRL1_BITSET (*(volatile unsigned long *)(0x4000044C))
#define APP_CTRL1_BITCLR (*(volatile unsigned long *)(0x4000084C))
#define APP_CTRL1_BITTOG (*(volatile unsigned long *)(0x40000C4C))
#define APP_CTRL2 (*(volatile unsigned long *)(0x40000050))
#define APP_CTRL2_BITSET (*(volatile unsigned long *)(0x40000450))
#define APP_CTRL2_BITCLR (*(volatile unsigned long *)(0x40000850))
#define APP_CTRL2_BITTOG (*(volatile unsigned long *)(0x40000C50))
#define IO_LIN_CTRL (*(volatile unsigned long *)(0x40000054))
#define IO_LIN_CTRL_BITSET (*(volatile unsigned long *)(0x40000454))
#define IO_LIN_CTRL_BITCLR (*(volatile unsigned long *)(0x40000854))
#define IO_LIN_CTRL_BITTOG (*(volatile unsigned long *)(0x40000C54))
#define SMPA_CLK_CTRL (*(volatile unsigned long *)(0x40000058))
#define SMPA_CLK_CTRL_BITSET (*(volatile unsigned long *)(0x40000458))
#define SMPA_CLK_CTRL_BITCLR (*(volatile unsigned long *)(0x40000858))
#define SMPA_CLK_CTRL_BITTOG (*(volatile unsigned long *)(0x40000C58))
#define PMU_STAT (*(volatile unsigned long *)(0x4000005C))
#define PMUBIST_ADC_CONF (*(volatile unsigned long *)(0x40000060))
#define PMUBIST_ADC_CONF_BITSET (*(volatile unsigned long *)(0x40000460))
#define PMUBIST_ADC_CONF_BITCLR (*(volatile unsigned long *)(0x40000860))
#define PMUBIST_ADC_CONF_BITTOG (*(volatile unsigned long *)(0x40000C60))
#define PMUBIST_ADC_DATA (*(volatile unsigned long *)(0x40000064))
#define STATUS (*(volatile unsigned long *)(0x40000068))
#define LPC_STATUS (*(volatile unsigned long *)(0x4000006C))
#define LPC_PDTIMER (*(volatile unsigned long *)(0x40000070))
#define LPC_PDTIMER_BITSET (*(volatile unsigned long *)(0x40000470))
#define LPC_PDTIMER_BITCLR (*(volatile unsigned long *)(0x40000870))
#define LPC_PDTIMER_BITTOG (*(volatile unsigned long *)(0x40000C70))
#define PIO_OWNER0 (*(volatile unsigned long *)(0x40000074))
#define PIO_OWNER1 (*(volatile unsigned long *)(0x40000078))
#define PIO_OWNER2 (*(volatile unsigned long *)(0x4000007C))
#define RTC_TIME_LSBS (*(volatile unsigned long *)(0x40000080))
#define RTC_TIME_MSBS (*(volatile unsigned long *)(0x40000084))
#define DEBUG_SEL (*(volatile unsigned long *)(0x40000088))
#define DEBUG_SEL_BITSET (*(volatile unsigned long *)(0x40000488))
#define DEBUG_SEL_BITCLR (*(volatile unsigned long *)(0x40000888))
#define DEBUG_SEL_BITTOG (*(volatile unsigned long *)(0x40000C88))
#define FLASH_STATUS (*(volatile unsigned long *)(0x4000008C))
#define CHIP_RESET (*(volatile unsigned long *)(0x40000090))
#define CHIP_RESET_BITSET (*(volatile unsigned long *)(0x40000490))
#define CHIP_RESET_BITCLR (*(volatile unsigned long *)(0x40000890))
#define CHIP_RESET_BITTOG (*(volatile unsigned long *)(0x40000C90))
#define SWD_PIN_CFG (*(volatile unsigned long *)(0x40000094))
#define SWD_PIN_CFG_BITSET (*(volatile unsigned long *)(0x40000494))
#define SWD_PIN_CFG_BITCLR (*(volatile unsigned long *)(0x40000894))
#define SWD_PIN_CFG_BITTOG (*(volatile unsigned long *)(0x40000C94))
#define LPC_SLEEP_CNT (*(volatile unsigned long *)(0x40000098))
#define SEC_RTC_IRQ_TIME_LSBS (*(volatile unsigned long *)(0x4000009C))
#define SEC_RTC_IRQ_TIME_LSBS_BITSET (*(volatile unsigned long *)(0x4000049C))
#define SEC_RTC_IRQ_TIME_LSBS_BITCLR (*(volatile unsigned long *)(0x4000089C))
#define SEC_RTC_IRQ_TIME_LSBS_BITTOG (*(volatile unsigned long *)(0x40000C9C))
#define SEC_RTC_IRQ_TIME_MSBS (*(volatile unsigned long *)(0x400000A0))
#define SEC_RTC_IRQ_TIME_MSBS_BITSET (*(volatile unsigned long *)(0x400004A0))
#define SEC_RTC_IRQ_TIME_MSBS_BITCLR (*(volatile unsigned long *)(0x400008A0))
#define SEC_RTC_IRQ_TIME_MSBS_BITTOG (*(volatile unsigned long *)(0x40000CA0))
#define SEC_RTC_IRQ_CLR (*(volatile unsigned long *)(0x400000A4))
#define SEC_RTC_IRQ_CLR_BITSET (*(volatile unsigned long *)(0x400004A4))
#define SEC_RTC_IRQ_CLR_BITCLR (*(volatile unsigned long *)(0x400008A4))
#define SEC_RTC_IRQ_CLR_BITTOG (*(volatile unsigned long *)(0x40000CA4))
#define RAD_RTC_IRQ_TIME_LSBS (*(volatile unsigned long *)(0x400000A8))
#define RAD_RTC_IRQ_TIME_LSBS_BITSET (*(volatile unsigned long *)(0x400004A8))
#define RAD_RTC_IRQ_TIME_LSBS_BITCLR (*(volatile unsigned long *)(0x400008A8))
#define RAD_RTC_IRQ_TIME_LSBS_BITTOG (*(volatile unsigned long *)(0x40000CA8))
#define RAD_RTC_IRQ_TIME_MSBS (*(volatile unsigned long *)(0x400000AC))
#define RAD_RTC_IRQ_TIME_MSBS_BITSET (*(volatile unsigned long *)(0x400004AC))
#define RAD_RTC_IRQ_TIME_MSBS_BITCLR (*(volatile unsigned long *)(0x400008AC))
#define RAD_RTC_IRQ_TIME_MSBS_BITTOG (*(volatile unsigned long *)(0x40000CAC))
#define RAD_RTC_IRQ_CLR (*(volatile unsigned long *)(0x400000B0))
#define RAD_RTC_IRQ_CLR_BITSET (*(volatile unsigned long *)(0x400004B0))
#define RAD_RTC_IRQ_CLR_BITCLR (*(volatile unsigned long *)(0x400008B0))
#define RAD_RTC_IRQ_CLR_BITTOG (*(volatile unsigned long *)(0x40000CB0))
#define APP_RTC_IRQ_TIME_LSBS (*(volatile unsigned long *)(0x400000B4))
#define APP_RTC_IRQ_TIME_LSBS_BITSET (*(volatile unsigned long *)(0x400004B4))
#define APP_RTC_IRQ_TIME_LSBS_BITCLR (*(volatile unsigned long *)(0x400008B4))
#define APP_RTC_IRQ_TIME_LSBS_BITTOG (*(volatile unsigned long *)(0x40000CB4))
#define APP_RTC_IRQ_TIME_MSBS (*(volatile unsigned long *)(0x400000B8))
#define APP_RTC_IRQ_TIME_MSBS_BITSET (*(volatile unsigned long *)(0x400004B8))
#define APP_RTC_IRQ_TIME_MSBS_BITCLR (*(volatile unsigned long *)(0x400008B8))
#define APP_RTC_IRQ_TIME_MSBS_BITTOG (*(volatile unsigned long *)(0x40000CB8))
#define APP_RTC_IRQ_CLR (*(volatile unsigned long *)(0x400000BC))
#define APP_RTC_IRQ_CLR_BITSET (*(volatile unsigned long *)(0x400004BC))
#define APP_RTC_IRQ_CLR_BITCLR (*(volatile unsigned long *)(0x400008BC))
#define APP_RTC_IRQ_CLR_BITTOG (*(volatile unsigned long *)(0x40000CBC))
#define CAP_ANA_CTRL (*(volatile unsigned long *)(0x400000C0))
#define CAP_ANA_CTRL_BITSET (*(volatile unsigned long *)(0x400004C0))
#define CAP_ANA_CTRL_BITCLR (*(volatile unsigned long *)(0x400008C0))
#define CAP_ANA_CTRL_BITTOG (*(volatile unsigned long *)(0x40000CC0))
#define CAP_FILT_CONF (*(volatile unsigned long *)(0x400000C4))
#define CAP_FILT_CONF_BITSET (*(volatile unsigned long *)(0x400004C4))
#define CAP_FILT_CONF_BITCLR (*(volatile unsigned long *)(0x400008C4))
#define CAP_FILT_CONF_BITTOG (*(volatile unsigned long *)(0x40000CC4))
#define CAP_IRQ_CONF (*(volatile unsigned long *)(0x400000C8))
#define CAP_IRQ_CONF_BITSET (*(volatile unsigned long *)(0x400004C8))
#define CAP_IRQ_CONF_BITCLR (*(volatile unsigned long *)(0x400008C8))
#define CAP_IRQ_CONF_BITTOG (*(volatile unsigned long *)(0x40000CC8))
#define CAP_STATUS (*(volatile unsigned long *)(0x400000CC))

/*typedef struct {
   uint32 DIGITAL_VERSION;
   uint32 CLK_FREQ_DAC;
   uint32 CLK_FREQ_SET;
   uint32 CLK_FREQ_NREFCLKS;
   uint32 CLK_FREQ_REF_SEL;
   uint32 CLK_FREQ_DIG_CLKS;
   uint32 CLK_FREQ_HIGHTARGET;
   uint32 CLK_FREQ_LOWTARGET;
   uint32 CLK_FREQ_LP_BACKOFF;
   uint32 CLK_FREQ_ENABLE;
   uint32 CLK_GATE_SYS;
   uint32 CLK_GATE_MODEM;
   uint32 CLK_GATE_RADIO;
   uint32 CLK_GATE_DEBUG;
   uint32 LPC_CTRL;
   uint32 LPC_TEST;
   uint32 PMU_CTRL0;
   uint32 PMU_CTRL1;
   uint32 APP_CTRL0;
   uint32 APP_CTRL1;
   uint32 APP_CTRL2;
   uint32 IO_LIN_CTRL;
   uint32 SMPA_CLK_CTRL;
   uint32 PMU_STAT;
   uint32 PMUBIST_ADC_CONF;
   uint32 PMUBIST_ADC_DATA;
   uint32 STATUS;
   uint32 LPC_STATUS;
   uint32 LPC_PDTIMER;
   uint32 PIO_OWNER0;
   uint32 PIO_OWNER1;
   uint32 PIO_OWNER2;
   uint32 RTC_TIME_LSBS;
   uint32 RTC_TIME_MSBS;
   uint32 DEBUG_SEL;
   uint32 FLASH_STATUS;
   uint32 CHIP_RESET;
   uint32 SWD_PIN_CFG;
   uint32 LPC_SLEEP_CNT;
   uint32 SEC_RTC_IRQ_TIME_LSBS;
   uint32 SEC_RTC_IRQ_TIME_MSBS;
   uint32 SEC_RTC_IRQ_CLR;
   uint32 RAD_RTC_IRQ_TIME_LSBS;
   uint32 RAD_RTC_IRQ_TIME_MSBS;
   uint32 RAD_RTC_IRQ_CLR;
   uint32 APP_RTC_IRQ_TIME_LSBS;
   uint32 APP_RTC_IRQ_TIME_MSBS;
   uint32 APP_RTC_IRQ_CLR;
   uint32 CAP_ANA_CTRL;
   uint32 CAP_FILT_CONF;
   uint32 CAP_IRQ_CONF;
   uint32 CAP_STATUS;
} man_regs_t;*/

// lpuart_regs register definitions
#define LP_UART_CLAIM (*(volatile unsigned long *)(0x40002000))
#define LP_UART_CLAIM_BITSET (*(volatile unsigned long *)(0x40002020))
#define LP_UART_CLAIM_BITCLR (*(volatile unsigned long *)(0x40002040))
#define LP_UART_CLAIM_BITTOG (*(volatile unsigned long *)(0x40002060))
#define LP_UART_CTRL (*(volatile unsigned long *)(0x40002004))
#define LP_UART_CTRL_BITSET (*(volatile unsigned long *)(0x40002024))
#define LP_UART_CTRL_BITCLR (*(volatile unsigned long *)(0x40002044))
#define LP_UART_CTRL_BITTOG (*(volatile unsigned long *)(0x40002064))
#define LP_UART_STATUS (*(volatile unsigned long *)(0x40002008))
#define LP_UART_IRQ_CLR (*(volatile unsigned long *)(0x4000200C))
#define LP_UART_IRQ_CLR_BITSET (*(volatile unsigned long *)(0x4000202C))
#define LP_UART_IRQ_CLR_BITCLR (*(volatile unsigned long *)(0x4000204C))
#define LP_UART_IRQ_CLR_BITTOG (*(volatile unsigned long *)(0x4000206C))
#define LP_UART_TX_DATA (*(volatile unsigned long *)(0x40002010))
#define LP_UART_TX_DATA_BITSET (*(volatile unsigned long *)(0x40002030))
#define LP_UART_TX_DATA_BITCLR (*(volatile unsigned long *)(0x40002050))
#define LP_UART_TX_DATA_BITTOG (*(volatile unsigned long *)(0x40002070))
#define LP_UART_RX_DATA (*(volatile unsigned long *)(0x40002014))

/*typedef struct {
   uint32 LP_UART_CLAIM;
   uint32 LP_UART_CTRL;
   uint32 LP_UART_STATUS;
   uint32 LP_UART_IRQ_CLR;
   uint32 LP_UART_TX_DATA;
   uint32 empty0;
   uint32 empty1;
   uint32 empty2;
   uint32 LP_UART_RX_DATA;
} lpuart_regs_t;*/


// Aliases to conform to RTC driver expectations
#define RTC_IRQ_TIME_LSBS          APP_RTC_IRQ_TIME_LSBS
#define RTC_IRQ_TIME_LSBS_BITSET   APP_RTC_IRQ_TIME_LSBS_BITSET
#define RTC_IRQ_TIME_LSBS_BITCLR   APP_RTC_IRQ_TIME_LSBS_BITCLR
#define RTC_IRQ_TIME_LSBS_BITTOG   APP_RTC_IRQ_TIME_LSBS_BITTOG
#define RTC_IRQ_TIME_MSBS          APP_RTC_IRQ_TIME_MSBS
#define RTC_IRQ_TIME_MSBS_BITSET   APP_RTC_IRQ_TIME_MSBS_BITSET
#define RTC_IRQ_TIME_MSBS_BITCLR   APP_RTC_IRQ_TIME_MSBS_BITCLR
#define RTC_IRQ_TIME_MSBS_BITTOG   APP_RTC_IRQ_TIME_MSBS_BITTOG
#define RTC_IRQ_CLR                APP_RTC_IRQ_CLR
#define RTC_IRQ_CLR_BITSET         APP_RTC_IRQ_CLR_BITSET
#define RTC_IRQ_CLR_BITCLR         APP_RTC_IRQ_CLR_BITCLR
#define RTC_IRQ_CLR_BITTOG         APP_RTC_IRQ_CLR_BITTOG

/** @} end of group HI21XX_ARMCORE_APPS */

#endif
