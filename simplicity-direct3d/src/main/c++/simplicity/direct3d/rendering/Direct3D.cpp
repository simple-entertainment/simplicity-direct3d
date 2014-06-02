/*
* Copyright © 2014 Simple Entertainment Limited
*
* This file is part of The Simplicity Engine.
*
* The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
* Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
* <http://www.gnu.org/licenses/>.
*/
#include <simplicity/logging/Logs.h>

#include "Direct3D.h"

namespace simplicity
{
	namespace direct3d
	{
		namespace Direct3D
		{
			ID3D11DepthStencilView* depthStencilView = NULL;

			ID3D11Device* device = NULL;

			ID3D11DeviceContext* deviceContext = NULL;

			ID3D11RenderTargetView* renderTargetView = NULL;

			void checkError(HRESULT result)
			{
				if (result == S_FALSE)
				{
					Logs::log(Category::DEBUG_LOG, "Direct3D non-standard completion.");
				}
				else if (result == S_OK)
				{
					Logs::log(Category::TRACE_LOG, "Direct3D success!");
				}
				else
				{
					char* output;
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_IGNORE_INSERTS, NULL, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPTSTR) &output, 0, NULL);

					Logs::log(Category::ERROR_LOG, "Direct3D error: %s", output);

					delete[] output;
				}
			}
		}
	}
}
