#ifndef _SHARED_MEMORY_H_
#define _SHARED_MEMORY_H_

#ifdef __linux__
#elif _WIN32
#include <windows.h>
#endif

#include <string>
#include <cstddef>


namespace memory
{

    class SharedMemory
    {
        public:
            SharedMemory();
            ~SharedMemory();

            bool open(std::string name, std::size_t maxSize = 4192, bool createFile = false);
            void write(void* buffer , std::size_t size);
            void close();

            std::size_t getSize() const { return m_size;  }
            bool is_open() const
            {
                bool ret = false;
#ifdef __linux__
                ret = m_buffer != nullptr;
#elif _WIN32
                ret = m_handle != INVALID_HANDLE_VALUE;
#endif
                return ret;
            }

            static std::size_t getPageSize();
            static std::size_t adjustSizeToPageSize(std::size_t size);

        private :
            char* m_buffer;
            std::size_t m_size;
            std::size_t m_writtenSize;
#ifdef __linux__
            int m_fileDescriptor;
#elif _WIN32
            HANDLE m_handle;
            HANDLE m_fileHandle;
#endif
    };

} // namespace

#endif