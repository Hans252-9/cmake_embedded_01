#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);

typedef void (*isr_handler_t)(void);

#define DEFAULT_IRQ_1   Default_Handler
#define DEFAULT_IRQ_2   DEFAULT_IRQ_1, DEFAULT_IRQ_1
#define DEFAULT_IRQ_4   DEFAULT_IRQ_2, DEFAULT_IRQ_2
#define DEFAULT_IRQ_8   DEFAULT_IRQ_4, DEFAULT_IRQ_4
#define DEFAULT_IRQ_16  DEFAULT_IRQ_8, DEFAULT_IRQ_8
#define DEFAULT_IRQ_32  DEFAULT_IRQ_16, DEFAULT_IRQ_16
#define DEFAULT_IRQ_64  DEFAULT_IRQ_32, DEFAULT_IRQ_32
#define DEFAULT_IRQ_128 DEFAULT_IRQ_64, DEFAULT_IRQ_64

#define SCB_CPACR (*(volatile uint32_t *)0xE000ED88UL)
#define CP10_CP11_FULL_ACCESS (0xFU << 20U)

__attribute__((section(".isr_vector"), used))
/* All architectural external IRQ slots use the safe default handler. */
const isr_handler_t vector_table[] = {
    (isr_handler_t)&_estack,
    Reset_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    0,
    0,
    0,
    0,
    Default_Handler,
    Default_Handler,
    0,
    Default_Handler,
    Default_Handler,
    DEFAULT_IRQ_128,
    DEFAULT_IRQ_64,
    DEFAULT_IRQ_32,
    DEFAULT_IRQ_16
};

void Reset_Handler(void)
{
    const uint32_t *source;
    uint32_t *destination;

    /* Povolit FPU CP10 a CP11 */
    SCB_CPACR |= CP10_CP11_FULL_ACCESS;
    __asm__ volatile ("dsb" ::: "memory");
    __asm__ volatile ("isb" ::: "memory");

    source = &_sidata;
    destination = &_sdata;

    while (destination < &_edata) {
        *destination = *source;
        ++destination;
        ++source;
    }

    destination = &_sbss;

    while (destination < &_ebss) {
        *destination = 0U;
        ++destination;
    }

    (void)main();

    while (1) {
    }
}

void Default_Handler(void)
{
    while (1) {
    }
}
