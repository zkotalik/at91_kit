/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* application includes */
#include "zxtasks.h"
#include "led.h"

/*
 * Configure the processor for use with the AT91RM9200 board.  This includes
 * setup for the I/O, system clock, and access timings.
 */
static void prvSetupHardware( void );

/*-----------------------------------------------------------*/


/***********************************************************************
 *
 * Function:    main
 *
 * Description: main function
 *
 * Notes:
 *
 * Returns:
 *
 **********************************************************************/
int main( void )
{

    prvSetupHardware();
    /* Create one of three tasks. Note that a real application should check
     * the return value of the xTaskCreate() call to ensure the task was
     * created successfully. */
    xTaskCreate( vTask1,    /* Pointer to function that implements the task. */
                 "vTask1",  /* Text name of the task. For debugging only. */
                 1000,      /* Stack depth. */
                 NULL,      /* Not using task parameters. */
                 1,         /* Will run at priority 1. */
                 NULL );    /* Not going to use task handle. */

    /* Create the others two tasks in exactly the same way. */
    xTaskCreate( vTask2, "vTask2", 1000, NULL, 1, NULL);
    xTaskCreate( vTask3, "vTask3", 1000, NULL, 1, NULL);

    /* Start the sheduler so tasks start executing. */
    vTaskStartScheduler();

    /* If all is well then main() will never reach here as the sheduler will
     * now be running tasks. If main() does reach here then it is likely that
     * there was insufficient heap memory available for idle task to be
     * created. */
     for( ;; );
}

/***********************************************************************
 *
 * Function:    prvSetupHardware
 *
 * Description: Setup the hardware for use with AT91RM9200 board.
 *
 * Notes:
 *
 * Returns:     Note
 *
 **********************************************************************/
void prvSetupHardware( void )
{
long lCount;

	/* Disable all interrupts at the AIC level initially... */
	AT91C_BASE_AIC->AIC_IDCR = 0xFFFFFFFF;

	/* Set all SVR and SMR entries to default values (start with a clean slate)... */
	for( lCount = 0; lCount < 32; lCount++ )
	{
		AT91C_BASE_AIC->AIC_SVR[ lCount ] = (unsigned long) 0;
		AT91C_BASE_AIC->AIC_SMR[ lCount ] = AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED;
	}

	/* Disable clocks to all peripherals initially... */
	AT91C_BASE_PMC->PMC_PCDR = 0xFFFFFFFF;

	/* Clear all interrupts at the AIC level initially... */
	AT91C_BASE_AIC->AIC_ICCR = 0xFFFFFFFF;

	/* Perform 8 "End Of Interrupt" cmds to make sure AIC will not Lock out
	nIRQ */
	for( lCount = 0; lCount < 8; lCount++ )
	{
		AT91C_BASE_AIC->AIC_EOICR = 0;
	}

    /* Initialise LED outputs. */
    ledInit();

}
