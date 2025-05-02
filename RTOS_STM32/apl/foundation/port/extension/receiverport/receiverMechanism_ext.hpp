#ifndef RECEIVERMECHANISM_HPP
#define RECEIVERMECHANISM_HPP

#include <stdint.h>
extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <queue.h>
}
#include <string.h>

        
namespace extension
{
  template<typename MixinType>
  class ReceiverMechanism: public MixinType
  {
    private:
      enum{IDLE = 0U, CHUNK_NOT_PROCESSED = 1U, CHUNK_PROCESSED = 2U};
    public:
      using PortDataBase_t = typename MixinType::PortDataBase_t;
      using PortDataBasePoinerType_t = PortDataBase_t*;  
      using MediumType_t = QueueHandle_t;

      ReceiverMechanism() = default;
      ~ReceiverMechanism() = default;
      ///\brief isReleased indicates collector from sendport whether receiver port is asking  
      ///       for returning a chunk
      ///\return TRUE: receiver port is not locking a chunk
      ///        FALSE: receiver port is locking a chunk and doesn't return any chunk
      ///\note  In case isReleased is called while Receiver Port is empty, receiver port is not locking any chunk
      ///       But is not returning any chunk, In this case: receiver port returns true, and param *depositChunk = nullptr
      inline bool isReleased(void* depositChunk) 
      {
        switch(m_isChunkProcessed) 
        {
          case static_cast<uint8_t>(CHUNK_PROCESSED):
          {
            //data container has already been processed 
            static_cast<void>(memcpy(depositChunk, static_cast<void*>(&m_internalDataContainer), sizeof(void*)));
            m_internalDataContainer = nullptr;
            m_isChunkProcessed = IDLE;
            return true;
          }
          case static_cast<uint8_t>(IDLE):
          {
            //Since last release, receiver port hasn't received any new data
            depositChunk = nullptr; //must return something
            return true;
          }
          case static_cast<uint8_t>(CHUNK_NOT_PROCESSED):
          default:
          {
            //data container is received and locked, not processed
            //or receiver port is empty
            depositChunk = nullptr; //must return something
            return false;
          }
        }
      }

      inline bool assign(const void* const portData, const void* depositChunk) 
      {
        bool retVal_bo{false};
        bool isReceiverPortReleasing_bo = isReleased(const_cast<void*>(depositChunk)); 
        //if current portdata isn't ready to be released, can't receive new data
        if(isReceiverPortReleasing_bo == false) 
        {
          //do nothing
        }
        else
        {
          if((m_internalTransporter != nullptr)&&(uxQueueSpacesAvailable(m_internalTransporter) != 0U))
          {
            static_cast<void>(xQueueSend(m_internalTransporter, portData, 0U));
            m_isChunkProcessed = CHUNK_NOT_PROCESSED;
            retVal_bo = true;
          }
        }

				return retVal_bo;
      }

      bool hasNewData(void) const
      {
		return m_isChunkProcessed == CHUNK_NOT_PROCESSED;
      }

      bool hasData(void) const
      {
		return m_isChunkProcessed != IDLE;
      }

      bool update(void)
      {
		bool retStatus = xQueueReceive(m_internalTransporter, &m_internalDataContainer, 0U);
		m_isChunkProcessed = CHUNK_PROCESSED;
		return retStatus;
      }

    protected:
      MediumType_t* getTransporter(void)
      {
        return &m_internalTransporter;
      }

      const PortDataBasePoinerType_t getDataContainer(void) const
      {
        return m_internalDataContainer;
      }

    private:
      ReceiverMechanism(const ReceiverMechanism&) = delete;
      ReceiverMechanism(ReceiverMechanism&&) = delete;
      ReceiverMechanism& operator=(ReceiverMechanism&) = delete;
      ReceiverMechanism& operator=(ReceiverMechanism&&) = delete;

      PortDataBasePoinerType_t m_internalDataContainer{nullptr};
      MediumType_t m_internalTransporter{nullptr};
      uint8_t m_isChunkProcessed{IDLE};
  };
}//end of namespace extension

#endif

