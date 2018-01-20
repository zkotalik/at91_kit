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

   /* Infinited loop */
    for( ;; )
    {
        ledToggle( GREEN_LED );
        vTaskDelay( 500 / portTICK_RATE_MS );
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

        /* Infinited loop */
    for( ;; )
    {
        ledToggle( YELLOW_LED );
        vTaskDelay( 800 / portTICK_RATE_MS );
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

   /* Infinited loop */
    for( ;; )
    {
        ledToggle( RED_LED );
        vTaskDelay( 1200 / portTICK_RATE_MS );
    }
}
