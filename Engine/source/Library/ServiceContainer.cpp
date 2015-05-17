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
#include "ServiceContainer.h"

namespace Library
{
    ServiceContainer::ServiceContainer()
        : mServices()
    {
    }

    void ServiceContainer::AddService(UINT typeID, void* service)
    {
        mServices.insert(std::pair<UINT, void*>(typeID, service));
    }

    void ServiceContainer::RemoveService(UINT typeID)
    {
        mServices.erase(typeID);
    }

    void* ServiceContainer::GetService(UINT typeID) const
    {
        std::map<UINT, void*>::const_iterator it = mServices.find(typeID);
        
        return (it != mServices.end() ? it->second : nullptr);
    }
}
