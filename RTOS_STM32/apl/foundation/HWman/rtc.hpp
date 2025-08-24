#ifndef RTC_HPP_INCLUDED
#define RTC_HPP_INCLUDED
extern "C"
{
  #include "stm32f4xx_hal.h" ///Must include for stm32f4xx_hal_gpio.h 
  #include "stm32f4xx_hal_rtc.h" 
}

namespace ComplexDriver
{
    class RTCHandler
    {
    public:
        explicit RTCHandler(RTC_HandleTypeDef* hrtc) : m_hrtc(hrtc) {}

        /**
         * \brief      Get the internal RTC handle reference.
         * \note       This method exposes the internal RTC handle for secure purpose.
         *             Hence usage of this function can't mutate the referenced RTC handle
         */
        const RTC_HandleTypeDef* const getInternalHwRef(void)
        {
            return m_hrtc;
        }

        /**
         * \brief      Set the RTC time.
         * \details    Wraps HAL_RTC_SetTime to set the RTC peripheral time.
         * \param[in]  time   Reference to RTC_TimeTypeDef structure with time values.
         * \param[in]  format Format of the time values (RTC_FORMAT_BIN or RTC_FORMAT_BCD).
         * \return     true if successful, false otherwise.
         */
        bool setTime(const RTC_TimeTypeDef& time, uint32_t format = RTC_FORMAT_BIN)
        {
		    if(m_hrtc == nullptr) return false;
		    return (HAL_RTC_SetTime(m_hrtc, const_cast<RTC_TimeTypeDef*>(&time), format) == HAL_OK);
        }

        /**
         * \brief      Set the RTC date.
         * \details    Wraps HAL_RTC_SetDate to set the RTC peripheral date.
         * \param[in]  date   Reference to RTC_DateTypeDef structure with date values.
         * \param[in]  format Format of the date values (RTC_FORMAT_BIN or RTC_FORMAT_BCD).
         * \return     true if successful, false otherwise.
         */
        bool setDate(const RTC_DateTypeDef& date, uint32_t format = RTC_FORMAT_BIN)
        {
            if(m_hrtc == nullptr) return false;
            return (HAL_RTC_SetDate(m_hrtc, const_cast<RTC_DateTypeDef*>(&date), format) == HAL_OK);
        }

        /**
         * \brief      Get the RTC time.
         * \details    Wraps HAL_RTC_GetTime to retrieve the RTC peripheral time.
         * \param[out] time   Reference to RTC_TimeTypeDef structure to store time values.
         * \param[in]  format Format of the time values (RTC_FORMAT_BIN or RTC_FORMAT_BCD).
         * \return     true if successful, false otherwise.
         */
        bool getTime(RTC_TimeTypeDef& time, uint32_t format = RTC_FORMAT_BIN)
        {
            if(m_hrtc == nullptr) return false;
            return (HAL_RTC_GetTime(m_hrtc, &time, format) == HAL_OK);
        }

        /**
         * \brief      Get the RTC date.
         * \details    Wraps HAL_RTC_GetDate to retrieve the RTC peripheral date.
         * \param[out] date   Reference to RTC_DateTypeDef structure to store date values.
         * \param[in]  format Format of the date values (RTC_FORMAT_BIN or RTC_FORMAT_BCD).
         * \return     true if successful, false otherwise.
         */
        bool getDate(RTC_DateTypeDef& date, uint32_t format = RTC_FORMAT_BIN)
        {
            if(m_hrtc == nullptr) return false;
            return (HAL_RTC_GetDate(m_hrtc, &date, format) == HAL_OK);
        }

    private:
        RTC_HandleTypeDef* m_hrtc;
    };

    ///\brief factory method to handle and deliver RTCHandler instance
    ///\note  if no handler found, nullptr is returned
    RTCHandler* getRTCHandlerInstance(uint8_t l_instanceidx_u8=0U);
}//end of namespace ComplexDriver

#endif

