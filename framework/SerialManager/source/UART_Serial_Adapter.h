/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017, 2019 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef __UART_SERIAL_ADAPTER_H__
#define __UART_SERIAL_ADAPTER_H__

#include "EmbeddedTypes.h"
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_os_abstraction.h"
#include "pin_mux.h"
#include "board.h"
#include "SerialManager.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#include "clock_config.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#ifndef gUartIsrPrio_c
#define gUartIsrPrio_c (0x40)
#endif

/*******************************************************************************
 * Lpuart_dma Definitions
 ******************************************************************************/
#define DEMO_LPUART LPUART0
#define DEMO_LPUART_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPUART_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define LPUART_TX_DMA_CHANNEL 0U
#define LPUART_RX_DMA_CHANNEL 1U
#define EXAMPLE_LPUART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_LPUART_DMA_BASEADDR DMA0
#define LPUART_TX_DMA_REQUEST kDmaRequestMux0LPUART0Tx
#define LPUART_RX_DMA_REQUEST kDmaRequestMux0LPUART0Rx
#define ECHO_BUFFER_LENGTH 8

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
typedef struct uartState_tag uartState_t;

typedef void (*uartCallback_t)(uartState_t* state);

struct uartState_tag {
    uartCallback_t txCb;
    uartCallback_t rxCb;
    uint32_t txCbParam;
    uint32_t rxCbParam;
    uint8_t *pTxData;
    uint8_t *pRxData;
    volatile uint32_t txSize;
    volatile uint32_t rxSize;
};

enum uartStatus_tag {
    gUartSuccess_c,
    gUartInvalidParameter_c,
    gUartBusy_c
};

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
uint32_t UART_Initialize(uint32_t instance, uartState_t *pState);
uint32_t UART_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t UART_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t UART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t UART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t UART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t UART_IsTxActive(uint32_t instance);
uint32_t UART_EnableLowPowerWakeup(uint32_t instance);
uint32_t UART_DisableLowPowerWakeup(uint32_t instance);
uint32_t UART_IsWakeupSource(uint32_t instance);

uint32_t LPUART_Initialize(uint32_t instance, uartState_t *pState);
uint32_t LPUART_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t LPUART_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPUART_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPUART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPUART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPUART_IsTxActive(uint32_t instance);
uint32_t LPUART_EnableLowPowerWakeup(uint32_t instance);
uint32_t LPUART_DisableLowPowerWakeup(uint32_t instance);
uint32_t LPUART_IsWakeupSource(uint32_t instance);

uint32_t LPSCI_Initialize(uint32_t instance, uartState_t *pState);
uint32_t LPSCI_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t LPSCI_SendData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPSCI_ReceiveData(uint32_t instance, uint8_t* pData, uint32_t size);
uint32_t LPSCI_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPSCI_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t LPSCI_IsTxActive(uint32_t instance);
uint32_t LPSCI_EnableLowPowerWakeup(uint32_t instance);
uint32_t LPSCI_DisableLowPowerWakeup(uint32_t instance);
uint32_t LPSCI_IsWakeupSource(uint32_t instance);

uint32_t USART_Initialize(uint32_t instance, uartState_t *pState);
uint32_t USART_SetBaudrate(uint32_t instance, uint32_t baudrate);
uint32_t USART_SendData(uint32_t instance, uint8_t *pData, uint32_t size);
uint32_t USART_ReceiveData(uint32_t instance, uint8_t *pData, uint32_t size);
uint32_t USART_InstallRxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t USART_InstallTxCalback(uint32_t instance, uartCallback_t cb, uint32_t cbParam);
uint32_t USART_IsTxActive(uint32_t instance);
uint32_t USART_EnableLowPowerWakeup(uint32_t instance);
uint32_t USART_DisableLowPowerWakeup(uint32_t instance);
uint32_t USART_IsWakeupSource(uint32_t instance);
void LPUART_UserCallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData);
uint32_t LPUART_DMA_Initialize(uint32_t instance, uartState_t *pState);
void test_case();

#if FSL_FEATURE_LPUART_HAS_SHARED_IRQ0_IRQ1
void LPUART0_LPUART1_IRQHandler(void);
#endif
#endif /* __UART_SERIAL_ADAPTER_H__ */
