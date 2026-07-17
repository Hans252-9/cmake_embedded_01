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

/* All architectural external IRQ slots use the safe default handler. */
__attribute__((section(".isr_vector"), used))
const isr_handler_t vector_table[] = {
    (isr_handler_t)&_estack, /* Initial stack pointer */
    Reset_Handler,          /* Reset */
    Default_Handler,        /* NMI */
    Default_Handler,        /* HardFault */
    Default_Handler,        /* MemManage */
    Default_Handler,        /* BusFault */
    Default_Handler,        /* UsageFault */
    0,
    0,
    0,
    0,
    Default_Handler,        /* SVCall */
    Default_Handler,        /* Debug monitor */
    0,
    Default_Handler,        /* PendSV */
    Default_Handler,        /* SysTick */
    DEFAULT_IRQ_128,
    DEFAULT_IRQ_64,
    DEFAULT_IRQ_32,
    DEFAULT_IRQ_16
};

void Reset_Handler(void)
{
    const uint32_t *source = &_sidata;
    uint32_t *destination = &_sdata;

    /* Kopie inicializovaných dat z Flash do RAM */
    while (destination < &_edata) {
        *destination = *source;
        ++destination;
        ++source;
    }

    /* Vynulování .bss */
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
