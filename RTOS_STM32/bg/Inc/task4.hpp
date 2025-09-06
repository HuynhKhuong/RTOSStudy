#ifndef __TASK4_HPP__
#define __TASK4_HPP__

#include "task.hpp"

namespace Task
{
    class Task4Handler : public TaskHandler 
    {
    public: 
        Task4Handler() : TaskHandler{convertTickFromMs(1000U)} {}
        explicit Task4Handler(UBaseType_t taskPriority) : TaskHandler{convertTickFromMs(1000U), taskPriority, "Task-4"} {}

        void run(void* param) override;
        static void task4Run(void* param);
    };

    extern Task4Handler task4; 

} //End of namespace Task

#endif
