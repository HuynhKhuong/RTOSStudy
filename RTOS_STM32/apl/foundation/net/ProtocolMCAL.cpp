#include "ProtocolMCAL.hpp"
#include "ProtocolInterface.hpp"
#include "MessageListDefine.hpp"

extern "C"
{
    #include "portmacro.h"
    #include "projdefs.h"
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_uart.h"
}

extern UART_HandleTypeDef huart2;

namespace // unknown namespace for private scope access
{
    /// uxQueueLength The maximum number of items that the queue can contain.
    /// uxItemSize The number of bytes each item in the queue will require.
    constexpr UBaseType_t uxQueueLength{2U};
    constexpr UBaseType_t uxItemSize{sizeof(NetCom::ProtocolHardwareObjHandler)};
}

namespace NetCom
{
    QueueHandle_t g_MCALQueueHandler_st{nullptr};

    void netComTransmitInfrasInit(void)
    {
        g_MCALQueueHandler_st = xQueueCreate(uxQueueLength, uxItemSize);
    }

    void netComRequestTransmit(uint8_t* dataBuffer, const uint16_t& size)
    {
        ProtocolHardwareObjHandler obj{dataBuffer, size};
        xQueueSend(g_MCALQueueHandler_st, static_cast<const void*>(&obj), 0U);
    }

    /// \todo to draw a sequence diagram for this design
    void netComProcessTransmitRequest(void)
    {
        BaseType_t retVal{pdFALSE};
        ProtocolHardwareObjHandler curObj_st{nullptr, 0U};

        retVal = xQueuePeek(g_MCALQueueHandler_st, &curObj_st, 0U);
        if (retVal == pdTRUE)
        {
            portENTER_CRITICAL();
            portable::userDefinedTxTransmit(curObj_st.m_dataBuffer_u8, curObj_st.m_BufferSize_u16);
            portEXIT_CRITICAL();
        }
    }

    /// \todo Should Rx implement queueing mechanism as well?
    void netComReceive(uint8_t* dataBuffer, uint16_t bufferSize_u16)
    {
        const uint8_t messageIDIndex{0U};
        // get messageID
        const uint8_t messageID{dataBuffer[messageIDIndex]};

        bool messageIDMatched{false};
        bool messageDLCProtectPassed{false};

        // hook to get matched message handler
        MessageHandlerInterface* msgHandlerPtr{nullptr};

        for (MessageHandlerInterface* const messageHandler : g_messageConfigureTable)
        {
            if (messageHandler->m_messageID == messageID)
            {
                messageDLCProtectPassed = netProtect_DLCCheck((*messageHandler), &dataBuffer[0U], bufferSize_u16);
                messageIDMatched = true;
                msgHandlerPtr = messageHandler;
                break;
            }
        }

        if (messageIDMatched && messageDLCProtectPassed)
        {
            // set indication flag to true
            msgHandlerPtr->setNewMessageEventFlag(true);
        }
        else
        {
            // In case no match message ID, do nothing
        }
    }
}
