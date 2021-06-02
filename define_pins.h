#define NVIC_ST_CTRL_R (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile uint32_t *)0xE000E018))

#define SYSCTL_RCGCGPIO_R (*((volatile uint32_t *)0x400FE608))

#define GPIO_PORTA_DIR_R (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_DATA_R (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DEN_R (*((volatile uint32_t *)0x4000451C))

#define GPIO_PORTB_DIR_R (*((volatile uint32_t *)0x40005400))
#define GPIO_PORTB_DATA_R (*((volatile uint32_t *)0x400053FC))
#define GPIO_PORTB_DEN_R (*((volatile uint32_t *)0x4000551C))
