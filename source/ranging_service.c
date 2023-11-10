/*
 * ranging_service.c
 *
 *  Created on: 2023年3月31日
 *      Author: snowball
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ranging_service.h"


/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

static bleResult_t Ras_SendNotifications(rasConfig_t *pServiceConfig, uint16_t handle);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

bleResult_t Ras_Start(rasConfig_t *pServiceConfig)
{
    uint8_t mClientId = 0;

    /* reset all slots for valid subscribers */
    for (mClientId = 0; mClientId < pServiceConfig->validSubscriberListSize; mClientId++)
    {
        pServiceConfig->aValidSubscriberList[mClientId] = FALSE;
    }

    /* Record initial battery level measurement */
    return gBleSuccess_c;
}

bleResult_t Ras_Stop(rasConfig_t *pServiceConfig)
{
    uint8_t mClientId = 0;

    /* reset all slots for valid subscribers */
    for (mClientId = 0; mClientId < pServiceConfig->validSubscriberListSize; mClientId++)
    {
        pServiceConfig->aValidSubscriberList[mClientId] = FALSE;
    }

    return gBleSuccess_c;
}

bleResult_t Ras_Subscribe(rasConfig_t *pServiceConfig, deviceId_t clientDeviceId)
{
    bleResult_t result = gBleSuccess_c;

    if (clientDeviceId >= pServiceConfig->validSubscriberListSize)
    {
        result = gBleInvalidParameter_c;
    }
    else
    {
        pServiceConfig->aValidSubscriberList[clientDeviceId] = TRUE;
    }

    return result;
}

bleResult_t Ras_Unsubscribe(rasConfig_t *pServiceConfig, deviceId_t clientDeviceId)
{
    bleResult_t result = gBleSuccess_c;

    if (clientDeviceId >= pServiceConfig->validSubscriberListSize)
    {
        result = gBleInvalidParameter_c;
    }
    else
    {
        pServiceConfig->aValidSubscriberList[clientDeviceId] = FALSE;
    }

    return result;
}

bleResult_t Ras_RecordBatteryMeasurement(rasConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
    		 gBleUuidType128_c, (bleUuid_t *)uuid_uart_stream_tx, &handle);

    if (result == gBleSuccess_c)
    {
        /* Update characteristic value and send notification */
        //result = GattDb_WriteAttribute(handle, pServiceConfig->len, pServiceConfig->data);

        //if (result == gBleSuccess_c)
        //{
        	Ras_SendNotifications(pServiceConfig, handle);
        //}
    }

    return result;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static bleResult_t Ras_SendNotifications
(
    rasConfig_t *pServiceConfig,
    uint16_t     handle
)
{
    uint16_t  handleCccd;
    bool_t    isNotifActive;
    uint8_t   mClientId = 0;
    bleResult_t result = gBleSuccess_c;
    uint16_t ehandle = handle;

    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(ehandle, &handleCccd) == gBleSuccess_c)
    {
        for (mClientId = 0; mClientId < pServiceConfig->validSubscriberListSize; mClientId++)
        {
            if (pServiceConfig->aValidSubscriberList[mClientId])
            {
            	result = Gap_CheckNotificationStatus(mClientId, handleCccd, &isNotifActive);
                if (gBleSuccess_c == result && TRUE == isNotifActive)
                {
                	//result = GattServer_SendNotification(mClientId, handle);
                	result = GattServer_SendInstantValueNotification(mClientId, ehandle, pServiceConfig->len, pServiceConfig->data);
                }
            }
        }
    }
    return result;
}
/*! *********************************************************************************
* @}
********************************************************************************** */
