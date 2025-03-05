#ifndef PORTINTERFACE_HPP
#define PORTINTERFACE_HPP

#include <stdint.h>

namespace Port
{

enum class SignalStateDef: uint8_t
{
  SignalInitState, 
  SignalReceivedState,
  SiganlFailureState,
};

class ContainerInterface
{
public:
  ContainerInterface() = default;
  uint32_t getSequenceCounter(void) const
  {
    return m_sequenceCounter;
  }

  void increaseSequenceCounter(void)
  {
    m_sequenceCounter++;
  }

  void resetSequenceCounter(void)
  {
    m_sequenceCounter = 0U;
  }

private:
  uint32_t m_sequenceCounter{0U};
};

template <typename PhysicalType, typename RawType>
class CSignalDescription
{
public:
  struct MetaData
  {
    SignalStateDef m_state_en;
  };

  template <typename SignalType>
  struct RawDataInfo
  {
    SignalType m_maxVal;
    SignalType m_minVal;
    float m_factor_f32;
    float m_offset_f32;
  };

  CSignalDescription(const RawDataInfo<RawType>& rawDataInfo):m_rawDataInfo{rawDataInfo}///move data into member
  {
    //do nothing
  }
  
  MetaData getRawVal(RawType& retrieveVal)
  {
    retrieveVal = m_rawData;
    return m_metaData_st;
  }

  MetaData getPhysVal(PhysicalType& retrieveVal)
  {
    retrieveVal = m_physData;
    return m_metaData_st;
  }

  void setSignalVal(RawType rawData)
  {
    setRawSignalVal(rawData);
    m_physData = static_cast<PhysicalType>(m_rawData*m_rawDataInfo.m_factor_f32 + m_rawDataInfo.m_offset_f32);
    m_metaData_st.m_state_en = SignalStateDef::SignalReceivedState;

    ///\todo perform boundary check
  }

  void setRawSignalVal(RawType rawData)
  {
    m_rawData = rawData;  
  }

private:
  MetaData m_metaData_st{SignalStateDef::SignalInitState};
  PhysicalType m_physData{0U};
  RawType m_rawData{0U};
  const RawDataInfo<RawType> m_rawDataInfo;
};

///Force explicit instantiation
template class CSignalDescription<uint8_t, uint8_t>;
template struct CSignalDescription<uint8_t, uint8_t>::RawDataInfo<uint8_t>;
}//end of namespace Port
#endif


