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
#ifndef DIRECT3D_H_
#define DIRECT3D_H_

#include <D3D11.h>

namespace simplicity
{
	namespace direct3d
	{
		namespace Direct3D
		{
			extern ID3D11DepthStencilView* depthStencilView;

			extern ID3D11Device* device;

			extern ID3D11DeviceContext* deviceContext;

			extern ID3D11RenderTargetView* renderTargetView;

			void checkError(HRESULT result);
		}
	}
}

#endif /* DIRECT3D_H_ */
