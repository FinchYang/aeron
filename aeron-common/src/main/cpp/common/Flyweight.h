/*
 * Copyright 2014 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef INCLUDED_AERON_COMMON_FLYWEIGHT__
#define INCLUDED_AERON_COMMON_FLYWEIGHT__

#include <string>
#include <concurrent/AtomicBuffer.h>

namespace aeron { namespace common { namespace common {

template<typename struct_t>
class Flyweight
{
public:
    Flyweight (concurrent::AtomicBuffer& buffer, size_t offset)
        : m_struct(buffer.overlayStruct<struct_t>(offset)),
          m_buffer(buffer), m_baseOffset(offset)
    {
    }

protected:
    struct_t& m_struct;

    inline std::string stringGet(size_t offset) const
    {
        return m_buffer.getStringUtf8(m_baseOffset + offset);
    }

    inline std::int32_t stringPut(std::int32_t offset, const std::string& s)
    {
        return m_buffer.putStringUtf8(m_baseOffset + offset, s);
    }

    inline std::int32_t stringPutWithoutLength(std::int32_t offset, const std::string& s)
    {
        return m_buffer.putStringUtf8WithoutLength(m_baseOffset + offset, s);
    }

    inline std::string stringGetWithoutLength(std::int32_t offset, std::int32_t size) const
    {
        return m_buffer.getStringUtf8WithoutLength(m_baseOffset + offset, size);
    }

    template <typename struct_t2>
    inline struct_t2& overlayStruct (size_t offset)
    {
        return m_buffer.overlayStruct<struct_t2>(m_baseOffset + offset);
    }

private:
    concurrent::AtomicBuffer m_buffer;
    size_t m_baseOffset;
};

}}}

#endif