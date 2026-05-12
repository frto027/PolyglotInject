#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "System/Char.hpp"
#include "System/Int16.hpp"
#include "System/UInt16.hpp"
#include "System/Int32.hpp"
#include "System/Int64.hpp"
#include "System/UInt32.hpp"
#include "System/UInt64.hpp"
#include "System/Single.hpp"
#include "System/Double.hpp"
#include "System/Char.hpp"
#include "System/Double.hpp"
#include "System/Int32.hpp"
#include "System/Object.hpp"
#include "System/String.hpp"
#include <il2cpp-api-types.h>

namespace PolyglotInject{
    namespace Utils {
            template<typename T> struct BoxedType{ /*Invalid type*/ };
            template<> struct BoxedType<char> { using type = ::System::Char; };
            template<> struct BoxedType<int16_t> { using type = ::System::Int16; };
            template<> struct BoxedType<uint16_t> { using type = ::System::UInt16; };
            template<> struct BoxedType<int32_t> { using type = ::System::Int32; };
            template<> struct BoxedType<int64_t> { using type = ::System::Int64; };
            template<> struct BoxedType<uint32_t> { using type = ::System::UInt32; };
            template<> struct BoxedType<uint64_t> { using type = ::System::UInt64; };
            template<> struct BoxedType<unsigned long long> { using type = ::System::UInt64; };
            template<> struct BoxedType<float> { using type = ::System::Single; };
            template<> struct BoxedType<double> { using type = ::System::Double; };

            template<typename T>
            inline ::System::Object * convert(T arg){
                decltype(BoxedType<T>::type::m_value) v = arg;
                static_assert(sizeof(T) <= sizeof(v) );
                return il2cpp_utils::down_cast<::System::Object>(il2cpp_functions::value_box(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class
                    <typename BoxedType<T>::type>
                    ::get(), (void*)&v));
            }

            template<>
            inline ::System::Object * convert(const std::string& arg){
                return il2cpp_utils::down_cast<::System::Object>(&il2cpp_utils::newcsstr(arg)->object);
            }
            template<>
            inline ::System::Object * convert(const char * arg){
                return il2cpp_utils::down_cast<::System::Object>(&il2cpp_utils::newcsstr(arg)->object);
            }

            template<typename T>
            inline void ToArgumentArray(std::vector<::System::Object*> &arr, T arg){
                arr.push_back(convert(arg));
            }
            template<typename T, typename... Args>
            inline void ToArgumentArray(std::vector<::System::Object*> &arr, T arg, Args... args){
                arr.push_back(convert(arg));
                ToArgumentArray(arr, args...);
            }

    }
}