#pragma once

#include <fstream>
#include <ctime>


    class Log {

        public:  

        /**** Log size of obj in bytes ***/

            template <typename T> static void get_size(T obj)
            {
                std::ofstream m_Log;
                m_Log.open("Logs.txt", std::ofstream::app | std::ofstream::out);
                m_Log << "object is: " << sizeof(obj) << " bytes.\n" << "object is of type: " << typeid(&obj).name()<< "." << "\n";
                m_Log.close();
            } 

            template <typename T> static void error(T error)
            {
                std::ofstream m_Log;
                m_Log.open("Logs.txt", std::ofstream::app | std::ofstream::out);
                m_Log << "Error" << typeid(&error).name() << "\n";
                m_Log.close();
            }

        /**** Log generic ****/
        
            template <typename T> static void write(T arg)
            {
                std::ofstream m_Log;
                std::time_t m_time_stamp = std::time(nullptr);
                m_Log.open("Logs.txt", std::ofstream::app | std::ofstream::out);
                m_Log << arg << "\n"<< "Time stamp: " << std::ctime(&m_time_stamp) << "\n";
                m_Log.close();
            } 
    };
