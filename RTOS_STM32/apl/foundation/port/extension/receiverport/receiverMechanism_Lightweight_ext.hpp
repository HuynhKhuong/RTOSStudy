#ifndef RECEIVERMECHANISM_LIGHTWEIGHT_HPP
#define RECEIVERMECHANISM_LIGHTWEIGHT_HPP

#include <stdint.h>
extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include task.h
#include "task.h"                      
}
#include <string.h>

        
namespace extension
{
  template<typename MixinType>
  class LightWeightReceiverMechanism: public MixinType
  {
    public:
      using PortDataBase_t = typename MixinType::PortDataBase_t;
      using PortDataBasePoinerType_t = PortDataBase_t*;  
      using ConstantPortDataBasePoinerType_t = const PortDataBase_t*;
      using MediumType_t = TaskHandle_t;

      LightWeightReceiverMechanism() = default;
      ~LightWeightReceiverMechanism() = default;

      inline bool assign(const void* const portData, const void* depositChunk) 
      {
        bool retVal_bo{false};

        ///\note The mechanism of port connection is to deliver the address of the chunk
        ///      What the parameter portData represents is the temporary address of the container containing 
        ///      the actual address of the chunk
        ///      
        PortDataBase_t* ulValue_ptr{nullptr};
        memcpy(static_cast<void*>(&ulValue_ptr), portData, sizeof(void*));

        if((m_internalTransporter != nullptr) && (ulValue_ptr != nullptr))
        {
          static_cast<void>(xTaskNotify(m_internalTransporter, *(ulValue_ptr), eSetValueWithOverwrite));
          retVal_bo = true;
        }

        return retVal_bo;
      }

      bool hasNewData(void) const
      {return true;}

      bool hasData(void) const
      {return true;}

      bool update(void)
      {
        bool retStatus{xTaskNotifyWait(0U, 0U, &m_internalDataContainer, portMAX_DELAY) != pdFALSE};
        return retStatus;
      }

    protected:
      MediumType_t* getTransporter(void)
      {
        return &m_internalTransporter;
      }

      ConstantPortDataBasePoinerType_t getDataContainer(void) const
      {
    	return &m_internalDataContainer;
      }

    private:
      LightWeightReceiverMechanism(const LightWeightReceiverMechanism&) = delete;
      LightWeightReceiverMechanism(LightWeightReceiverMechanism&&) = delete;
      LightWeightReceiverMechanism& operator=(LightWeightReceiverMechanism&) = delete;
      LightWeightReceiverMechanism& operator=(LightWeightReceiverMechanism&&) = delete;

      PortDataBase_t m_internalDataContainer{0U};
      MediumType_t m_internalTransporter{nullptr};
  };
}//end of namespace extension

#endif

