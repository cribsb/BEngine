/*
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <string>

namespace Library
{
    class RTTI
    {
    public:
        virtual const unsigned int& TypeIdInstance() const = 0;
        
        virtual RTTI* QueryInterface(const unsigned id) const
        {
            return nullptr;
        }

        virtual bool Is(const unsigned int id) const
        {
            return false;
        }

        virtual bool Is(const std::string& name) const
        {
            return false;
        }

        template <typename T>
        T* As() const
        {
            if (Is(T::TypeIdClass()))
            {
                return (T*)this;
            }

            return nullptr;
        }
    };

    #define RTTI_DECLARATIONS(Type, ParentType)                                                              \
        public:                                                                                              \
            static std::string TypeName() { return std::string(#Type); }                                     \
            virtual const unsigned int& TypeIdInstance() const { return Type::TypeIdClass(); }               \
            static  const unsigned int& TypeIdClass() { return sRunTimeTypeId; }                             \
            virtual Library::RTTI* QueryInterface( const unsigned int id ) const                             \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return (RTTI*)this; }                                                                  \
                else                                                                                         \
					{ return ParentType::QueryInterface(id); }                                               \
            }                                                                                                \
            virtual bool Is(const unsigned int id) const                                                     \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return ParentType::Is(id); }                                                           \
            }                                                                                                \
            virtual bool Is(const std::string& name) const                                                   \
            {                                                                                                \
                if (name == TypeName())                                                                      \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return ParentType::Is(name); }                                                         \
            }                                                                                                \
	   private:                                                                                              \
            static unsigned int sRunTimeTypeId;

    #define RTTI_DEFINITIONS(Type) unsigned int Type::sRunTimeTypeId = (unsigned int)& Type::sRunTimeTypeId;
}