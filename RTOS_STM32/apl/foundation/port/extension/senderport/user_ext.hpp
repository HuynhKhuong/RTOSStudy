/*
 * user_ext.hpp
 *
 *  Created on: Apr 10, 2025
 *      Author: Khuong
 */

#ifndef SENDERPORT_USER_EXT_HPP
#define SENDERPORT_USER_EXT_HPP

namespace extension
{

    template<typename MixinType, typename PortDataType>
    class User: public MixinType
    {
        public:
            using Mixin_t = MixinType;
            using PortDataBase_t = typename MixinType::PortDataBase_t; 

            User() = default;
            ~User() = default;

            PortDataType& reserve(void)
            {
                PortDataBase_t* l_retrievedPortData_ptr{nullptr};

                l_retrievedPortData_ptr = Mixin_t::reserve(); //is always return a valid pointer

                return *(static_cast<PortDataType*>(l_retrievedPortData_ptr));
            }

            void deliver(void)
            {
                Mixin_t::deliver();
            }
        private:
            User(const User&) = delete;
            User(User&&) = delete;
            User& operator=(User&) = delete;
            User& operator=(User&&) = delete;
    };

}//end of namespace extension

#endif /* FOUNDATION_PORT_EXTENSION_SENDERPORT_USER_EXT_HPP_ */
