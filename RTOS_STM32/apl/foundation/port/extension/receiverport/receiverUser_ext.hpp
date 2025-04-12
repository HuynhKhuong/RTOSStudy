#ifndef RECEIVERUSER_HPP
#define RECEIVERUSER_HPP

namespace extension
{
  template<typename MixinType , typename PortDataType>
  class ReceiverUser: public MixinType
  {
    public:
      using PortData_t = PortDataType;
      using PortDataBase_t = typename MixinType::PortDataBase_t;
      using PortDataBasePoinerType_t = typename MixinType::PortDataBasePoinerType_t;
      using MediumType_t = typename MixinType::MediumType_t;

      ReceiverUser() = default;
      ~ReceiverUser() = default;

      bool hasNewData(void) const
			{
				return MixinType::hasNewData();
			}

      bool hasData(void) const
			{
				return MixinType::hasData();
			}

      bool update(void)
			{
        bool retStatus{false};

        if(MixinType::isConnected())
        {
          retStatus = MixinType::update(); 
        }
    
        return retStatus;
			}
       
      const PortData_t* getData(void) const
      {
        const PortDataType* retVal{nullptr};

        if(MixinType::hasNewData())
        {
          retVal = reinterpret_cast<const PortDataType*>(MixinType::getDataContainer());
        }
            
        return retVal;
      }

    private:
      ReceiverUser(const ReceiverUser&) = delete;
      ReceiverUser(ReceiverUser&&) = delete;
      ReceiverUser& operator=(ReceiverUser&) = delete;
      ReceiverUser& operator=(ReceiverUser&&) = delete;
  };
}

#endif

