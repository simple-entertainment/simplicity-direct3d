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
#include "FreeImagePlus.h"

#include "Direct3D.h"
#include "Direct3DTexture.h"

using namespace std;

namespace simplicity
{
	namespace direct3d
	{
		Direct3DTexture::Direct3DTexture(const char* data, unsigned int length) :
			data(data, length),
			height(0),
			initialized(false),
			rawData(NULL),
			shaderResourceView(NULL),
			texture(NULL),
			width(0)
		{
		}

		Direct3DTexture::Direct3DTexture(const char* rawData, unsigned int width, unsigned int height) :
			data(),
			height(height),
			initialized(false),
			rawData(rawData),
			shaderResourceView(NULL),
			texture(NULL),
			width(width)
		{
		}

		Direct3DTexture::Direct3DTexture(Resource& image) :
			data(image.getData()),
			height(0),
			initialized(false),
			rawData(NULL),
			shaderResourceView(NULL),
			texture(NULL),
			width(0)
		{
		}

		Direct3DTexture::~Direct3DTexture()
		{
			if (shaderResourceView != NULL)
			{
				shaderResourceView->Release();
			}

			if (texture != NULL)
			{
				texture->Release();
			}
		}

		void Direct3DTexture::apply(Pipeline& /* pipeline */)
		{
			if (!initialized)
			{
				init();
			}

			Direct3D::deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
		}

		unsigned int Direct3DTexture::getHeight()
		{
			return height;
		}

		unsigned int Direct3DTexture::getWidth()
		{
			return width;
		}

		void Direct3DTexture::init()
		{
			fipImage image;
			if (rawData == NULL)
			{
				fipMemoryIO memory(reinterpret_cast<BYTE*>(&data[0]), data.size());
				image.loadFromMemory(memory);

				height = image.getHeight();
				width = image.getWidth();

				rawData = reinterpret_cast<char*>(image.accessPixels());

				data.resize(0);
			}

			D3D11_TEXTURE2D_DESC description;
			memset(&description, 0, sizeof(D3D11_TEXTURE2D_DESC));
			description.ArraySize = 1;
			description.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			description.Format = DXGI_FORMAT_R16G16B16A16_UINT;
			description.Height = height;
			description.MipLevels = 1;
			description.SampleDesc.Count = 1;
			description.Usage = D3D11_USAGE_DEFAULT;
			description.Width = width;
			
			D3D11_SUBRESOURCE_DATA initialData;
			memset(&initialData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
			initialData.pSysMem = rawData;

			/*unsigned int numBytes = 0;
			unsigned int rowBytes = 0;
			unsigned int numRows = 0;
			DX::getSurfaceInfo(description.Width, description.Height, description.Format, &numBytes, &rowBytes, &numRows);
			initialData.SysMemPitch = rowBytes;*/

			Direct3D::checkError(Direct3D::device->CreateTexture2D(&description, &initialData, &texture));

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDescription;
			memset(&shaderResourceDescription, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
			shaderResourceDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			shaderResourceDescription.Texture2D.MipLevels = 1;
			shaderResourceDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			Direct3D::checkError(Direct3D::device->CreateShaderResourceView(texture, &shaderResourceDescription,
				&shaderResourceView));

			/*
			libRocket doesn't like this... TODO
			if (!image.isValid())
			{
				delete rawData;
				rawData = NULL;
			}
			*/

			initialized = true;
		}
	}
}
