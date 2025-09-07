#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdint.h>
namespace vfc
{
	///re-alias the ptrdiff_t for local usage
	using ptrdiff_t = uint32_t; ///process on 32-bit architecture so ptr type shall be 32bit long

	template<typename ElementDataType, uint16_t ContainerSize>
	struct array
	{
		static_assert(ContainerSize != 0, "Size can't be 0");
		using const_iterator = const ElementDataType*;

		inline ElementDataType*	begin()
		{
			return &m_Container[0U];
		}

		inline ElementDataType*	end()
		{
			ElementDataType* value = &m_Container[ContainerSize - 1U]; 
			return (++value);
		}

		inline const ElementDataType*	begin() const
		{
			return &m_Container[0U];
		}

		inline const ElementDataType*	end() const
		{
			const ElementDataType* value = &m_Container[ContainerSize - 1U]; 
			return (++value);
		}

		const ElementDataType& operator[](const uint16_t pos) const
		{
			if(pos >= ContainerSize)
			{
				return m_Container[0U];
			}
			else 
			{
				return m_Container[pos];
			}
		}

		ElementDataType& operator[](const uint16_t pos)
		{
			if(pos >= ContainerSize)
			{
				return m_Container[0U];
			}
			else 
			{
				return m_Container[pos];
			}
		}

		ElementDataType m_Container[ContainerSize];
	};
} //end of namespace vfc

namespace portable 
{
	///\brief function userDefinedTxTransmit is used to invoke desired communication protocol servered by particular MCU via specific peripherals
	///\param dataPtr: data container in arrays of uint8_t 
	///\param dataSize: size (of uint8_t s) of data container
	///\note  this function is platform specific, to be defined differently in different MCUs
	///       In current usecase, this function shall be defined in the same place with (hardware) callbacks (main.cpp)
	void userDefinedTxTransmit(const uint8_t* dataPtr_pu8, const uint8_t dataSize_cu8);

} //end of namespace portable

#endif
