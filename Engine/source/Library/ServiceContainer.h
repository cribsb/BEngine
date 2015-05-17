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

#include "Common.h"

namespace Library
{
    class ServiceContainer
    {
    public:
        ServiceContainer();

        void AddService(UINT typeID, void* service);
        void RemoveService(UINT typeID);
        void* GetService(UINT typeID) const;

    private:
        ServiceContainer(const ServiceContainer& rhs);
        ServiceContainer& operator=(const ServiceContainer& rhs);

        std::map<UINT, void*> mServices;		
    };
}