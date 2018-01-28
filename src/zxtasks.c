#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
/* application includes. */
#include "zxtasks.h"
#include "led.h"

/***********************************************************************
 *
 * Function:    vTask1
 *
 * Description: FRTOS task working with green led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask1( void *pvParameters )
{
    portTickType xLastWakeTime;

    /* The xLastWakeTime variable needs to be initiated with the current ticks
     * count. Note that this is the only time the variable is written to
     * explicitly. After this xLastWakeTime is updated internally within
     * vTaskDelayUntil(). */
    xLastWakeTime = xTaskGetTickCount();

   /* Infinited loop */
    for( ;; )
    {
        ledToggle( GREEN_LED );
        vTaskDelayUntil( &xLastWakeTime, ( 500 / portTICK_RATE_MS ) );
    }
}

/***********************************************************************
 *
 * Function:    vTask2
 *
 * Description: FRTOS task working with yellow led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask2( void *pvParameters )
{
    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

        /* Infinited loop */
    for( ;; )
    {
        ledToggle( YELLOW_LED );
        vTaskDelayUntil( &xLastWakeTime, ( 800 / portTICK_RATE_MS ) );
    }
}

/***********************************************************************
 *
 * Function:    vTask3
 *
 * Description: FRTOS task working with red led
 *
 * Notes:
 *
 * Returns:     None
 *
 **********************************************************************/
void vTask3( void *pvParameters )
{
    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

   /* Infinited loop */
    for( ;; )
    {
        ledToggle( RED_LED );
        vTaskDelayUntil( &xLastWakeTime, ( 1200 / portTICK_RATE_MS ) );
    }
}
