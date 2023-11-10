/*
 * ranging_service.h
 *
 *  Created on: 2023年3月31日
 *      Author: snowball
 */

#ifndef RANGING_SERVICE_H_
#define RANGING_SERVICE_H_
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "gatt_db_handles.h"
/*! Ranging Service - Configuration */
typedef struct rasConfig_tag
{
    uint16_t    serviceHandle;
    uint16_t    len;
    uint8_t*	data;
    bool_t*     aValidSubscriberList;
    uint8_t     validSubscriberListSize;
}rasConfig_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
* \brief        Starts Battery Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Ras_Start(rasConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops Battery Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Ras_Stop(rasConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the Battery service
*
* \param[in]    pServiceConfig  Pointer to service configuration structure
* \param[in]    pClient  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Ras_Subscribe(rasConfig_t* pServiceConfig, deviceId_t clientDeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the Battery service
*
* \param[in]    pServiceConfig  Pointer to service configuration structure
* \param[in]    pClient  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Ras_Unsubscribe(rasConfig_t* pServiceConfig, deviceId_t clientDeviceId);

/*!**********************************************************************************
* \brief        Records battery measurement on a specified service handle.
*
* \param[in]    pServiceConfig  pointer to service configuration structure
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Ras_RecordBatteryMeasurement (rasConfig_t* pServiceConfig);

#ifdef __cplusplus
}
#endif




#endif /* RANGING_SERVICE_H_ */
