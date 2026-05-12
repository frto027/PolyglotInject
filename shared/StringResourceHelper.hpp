#pragma once

#include "PolyglotInject.hpp"
#include "beatsaber-hook/shared/utils/typedefs-array.hpp"
#include "beatsaber-hook/shared/utils/typedefs-string.hpp"
#include <fmt/base.h>
#include <il2cpp-api-types.h>
#include <il2cpp-api.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Utils.hpp"

namespace PolyglotInject {
    class StringResourceBuilder{
        std::map<std::string, std::vector<std::string>> values;
        int currentLanguage = -1;
    public:
        StringResourceBuilder(){
            currentLanguage = indexForLanguage(L_English);
        }
        StringResourceBuilder & forLanguage(Language language){
            currentLanguage = indexForLanguage(language);
            return *this;
        }
        StringResourceBuilder & p(const std::string& key, const std::string& value){
            if(currentLanguage == -1)
                return *this;
            auto it = values.find(key);
            if(it == values.end()){
                values[key] = {32, ""};
                it = values.find(key);
            }
            it->second[currentLanguage] = value;
            return *this;
        }

        
        StringResourceBuilder & operator << (std::pair<std::string, std::string> pair){
            return p(pair.first, pair.second);
        }

        void submit(){
            if(values.size() == 0)
                return;
            std::stringstream ss;
            ss << "Polyglot,100,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\r\n";
            for(auto & kv : values){
                ss << escape(kv.first).value_or(kv.first) << ",";
                ss << ",";
                for(auto & v : kv.second){
                    ss << escape(v).value_or(v) << ",";
                }
                ss << "\r\n";
            }
            std::string str = ss.str();
            PolyglotInject::AddTextBeforeInstall((uint8_t*)str.data(), str.size());
            values.clear();
        }
        ~StringResourceBuilder(){
            submit();
        }
    private:
        int indexForLanguage(Language lang){
            switch(lang){
                case L_English:              return 0;
                case L_French:               return 1;
                case L_Spanish:              return 2;
                case L_German:               return 3;
                case L_Italian:              return 4;
                case L_Portuguese_Brazil:    return 5;
                case L_Portuguese:           return 6;
                case L_Russian:              return 7;
                case L_Greek:                return 8;
                case L_Turkish:              return 9;
                case L_Danish:               return 10;
                case L_Norwegian:            return 11;
                case L_Swedish:              return 12;
                case L_Dutch:                return 13;
                case L_Polish:               return 14;
                case L_Finnish:              return 15;
                case L_Japanese:             return 16;
                case L_Simplified_Chinese:   return 17;
                case L_Traditional_Chinese:  return 18;
                case L_Korean:               return 19;
                case L_Czech:                return 20;
                case L_Hungarian:            return 21;
                case L_Romanian:             return 22;
                case L_Thai:                 return 23;
                case L_Bulgarian:            return 24;
                case L_Hebrew:               return 25;
                case L_Arabic:               return 26;
                case L_Bosnian:              return 27;
                default: return -1;
            }
        }

        std::optional<std::string> escape(const std::string& input){
            bool need_escape = false;
            for(char ch : input){
                switch (ch) {
                    case ',':
                    case '\n':
                    case '\r':
                    case '\\':
                    case '"':
                        need_escape = true;
                        break;
                    default:
                        break;
                }
                if(need_escape)
                    break;
            }
            if(!need_escape)
                return {};
            
            std::stringstream ss;
            ss << '"';
            for(char ch : input){
                if(ch == '"'){
                    ss << '"';
                }
                ss << ch;
            }
            ss << '"';
            return ss.str();
        }
    };
    
    namespace Formatter{
        template<typename T1>
        ::StringW Format(::StringW fmt, T1 arg1){
            return ::System::String::Format(fmt, PolyglotInject::Utils::convert(arg1));
        }
        template<typename T1,typename T2>
        ::StringW Format(::StringW fmt, T1 arg1, T2 arg2){
            return ::System::String::Format(fmt, PolyglotInject::Utils::convert(arg1), PolyglotInject::Utils::convert(arg2));
        }
        template<typename T1,typename T2,typename T3>
        ::StringW Format(::StringW fmt, T1 arg1, T2 arg2, T3 arg3){
            return ::System::String::Format(fmt, PolyglotInject::Utils::convert(arg1), PolyglotInject::Utils::convert(arg2), PolyglotInject::Utils::convert(arg3));
        }

        template<typename T1, typename T2, typename T3, typename T4, typename... Args>
        ::StringW Format(::StringW fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, Args... args){
            std::vector<::System::Object*> arr;
            PolyglotInject::Utils::ToArgumentArray(arr, arg1, arg2, arg3, arg4, args...);
            return ::System::String::Format(fmt, ArrayW(arr));
        }
    };

    template<typename... Args>
    ::StringW FormatKey(::StringW key, Args... args){
        return Formatter::Format(Get(key), args...);
    }
}