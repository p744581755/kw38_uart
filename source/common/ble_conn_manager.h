/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef BLE_CONN_MANAGER_H
#define BLE_CONN_MANAGER_H

/************************************************************************************
*************************************************************************************
* Includes
*************************************************************************************
************************************************************************************/
#include "gap_types.h"

/************************************************************************************
*************************************************************************************
* Public Macros
*************************************************************************************
************************************************************************************/

/*! Enable / Disable Connection Update procedure on Peripheral */
#ifndef gConnUpdateAlwaysAccept_d
#define gConnUpdateAlwaysAccept_d               1
#endif

/*! Minimum connection interval for accepting an update */
#ifndef gConnUpdateIntervalMin_d
#define gConnUpdateIntervalMin_d                gGapConnIntervalMin_d
#endif

/*! Maximum connection interval for accepting an update */
#ifndef gConnUpdateIntervalMax_d
#define gConnUpdateIntervalMax_d                gGapConnIntervalMax_d
#endif

/*! Minimum latency for accepting an update */
#ifndef gConnUpdateLatencyMin_d
#define gConnUpdateLatencyMin_d                 gGapConnLatencyMin_d
#endif

/*! Maximum latency for accepting an update */
#ifndef gConnUpdateLatencyMax_d
#define gConnUpdateLatencyMax_d                 gGapConnLatencyMax_d
#endif

/*! Minimum supervision timeout for accepting an update */
#ifndef gConnUpdateSuperTimeoutMin_d
#define gConnUpdateSuperTimeoutMin_d            gGapConnSuperTimeoutMin_d
#endif

/*! Maximum supervision timeout for accepting an update */
#ifndef gConnUpdateSuperTimeoutMax_d
#define gConnUpdateSuperTimeoutMax_d            gGapConnSuperTimeoutMax_d
#endif

/*! Change ECDH public-private key pair after this number of failed pairing attempts */
#ifndef gConnPairFailChangeKeyThreshold_d
#define gConnPairFailChangeKeyThreshold_d       (3U)
#endif

/*! Change ECDH public-private key pair after this number of successful pairing attempts */
#ifndef gConnPairSuccessChangeKeyThreshold_d
#define gConnPairSuccessChangeKeyThreshold_d    (10U)
#endif

/*! One failed pairing counts as this number of successful pairings */
#ifndef gConnPairFailToSucessCount_c
#define gConnPairFailToSucessCount_c            (3U)
#endif

/*! Controller privacy, default enabled */
#ifndef gBleEnableControllerPrivacy_d
#define gBleEnableControllerPrivacy_d           (1U)
#endif

/*! specifies host preferred values for the transmitter PHY to be used for all
subsequent connections over the LE transport */

#ifndef gConnDefaultTxPhySettings_c
#define gConnDefaultTxPhySettings_c            (gLePhy1MFlag_c | gLePhy2MFlag_c)
#endif

/*! specifies host preferred values for the receiver PHY to be used for all
subsequent connections over the LE transport */
#ifndef gConnDefaultRxPhySettings_c
#define gConnDefaultRxPhySettings_c            (gLePhy1MFlag_c | gLePhy2MFlag_c)
#endif

/*! specifies whether the phy update procedure is going to be initiated in connection or not */
#ifndef gConnInitiatePhyUpdateRequest_c
#define gConnInitiatePhyUpdateRequest_c            (0U)
#endif

/*! specifies preferred Tx Phy Settings for the phy update procedure*/
#ifndef gConnPhyUpdateReqTxPhySettings_c
#define gConnPhyUpdateReqTxPhySettings_c            (gLePhy1MFlag_c | gLePhy2MFlag_c)
#endif

/*! specifies preferred Rx Phy Settings for the phy update procedure*/
#ifndef gConnPhyUpdateReqRxPhySettings_c
#define gConnPhyUpdateReqRxPhySettings_c            (gLePhy1MFlag_c | gLePhy2MFlag_c)
#endif

/*! specifies preferred Phy Options coding when transmitting on the LE Coded PHY*/
#ifndef gConnPhyUpdateReqPhyOptions_c
#define gConnPhyUpdateReqPhyOptions_c               (gLeCodingNoPreference_c)
#endif

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern gapSmpKeys_t                     gSmpKeys;
#if (defined(gAppUseBonding_d) && (gAppUseBonding_d == 1U))
extern uint8_t gcBondedDevices;
#endif
#if (defined(gAppUsePairing_d) && (gAppUsePairing_d == 1U))
extern gapPairingParameters_t           gPairingParameters;
extern gapDeviceSecurityRequirements_t  deviceSecurityRequirements;
#endif

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief  Performs common operations on the BLE stack on the generic callback.
*
* \param[in] pGenericEvent  GAP Generic event from the Host Stack .
*
*
********************************************************************************** */
void BleConnManager_GenericEvent(gapGenericEvent_t* pGenericEvent);

/*! *********************************************************************************
* \brief  Performs common GAP Peripheral and Central configurations of the BLE stack.
*
*
********************************************************************************** */
void BleConnManager_GapCommonConfig(void);

/*! *********************************************************************************
* \brief  Performs GAP Peripheral operations on the BLE stack on the connection callback.
*
* \param[in] peerDeviceId      The GAP peer Id.
*
* \param[in] pConnectionEvent  GAP Connection event from the Host Stack.
*
********************************************************************************** */
void BleConnManager_GapPeripheralEvent(deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);

/*! *********************************************************************************
* \brief  Performs GAP Central operations on the BLE stack on the connection callback.
*
* \param[in] peerDeviceId      The GAP peer Id.
*
* \param[in] pConnectionEvent  GAP Connection event from the Host Stack.
*
********************************************************************************** */
void BleConnManager_GapCentralEvent(deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);

/*! *********************************************************************************
* \brief  Checks bonding devices and enables controller/host privacy.
*
*
********************************************************************************** */
bleResult_t BleConnManager_EnablePrivacy(void);

/*! *********************************************************************************
* \brief  Checks enabled privacy and disables controller/host privacy.
*
*
********************************************************************************** */
bleResult_t BleConnManager_DisablePrivacy(void);

#endif /* BLE_CONN_MANAGER_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
