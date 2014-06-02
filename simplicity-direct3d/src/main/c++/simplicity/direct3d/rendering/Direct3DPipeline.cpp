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
#include "Direct3D.h"
#include "Direct3DPipeline.h"

using namespace std;

namespace simplicity
{
	namespace direct3d
	{
		const unsigned int CONSTANT_BUFFER_SIZE = 128;

		Direct3DPipeline::Direct3DPipeline(Resource& vertexShaderByteCode, Resource& pixelShaderByteCode) :
			constantBuffer(nullptr),
			constantData(CONSTANT_BUFFER_SIZE, ' '),
			constantDataSize(0),
			constantPositions(),
			initialized(false),
			pixelShader(nullptr),
			pixelShaderByteCode(pixelShaderByteCode.getData()),
			vertexShader(nullptr),
			vertexShaderByteCode(vertexShaderByteCode.getData())
		{
		}

		Direct3DPipeline::~Direct3DPipeline()
		{
			if (constantBuffer != nullptr)
			{
				constantBuffer->Release();
			}

			if (pixelShader != nullptr)
			{
				pixelShader->Release();
			}

			if (vertexShader != nullptr)
			{
				vertexShader->Release();
			}
		}

		void Direct3DPipeline::apply()
		{
			init();

			Direct3D::deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, constantData.data(), 0, 0);
			Direct3D::deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

			Direct3D::deviceContext->VSSetShader(vertexShader, nullptr, 0);
			Direct3D::deviceContext->PSSetShader(pixelShader, nullptr, 0);
		}

		void Direct3DPipeline::init()
		{
			if (initialized)
			{
				return;
			}

			CD3D11_BUFFER_DESC constantBufferDescription(CONSTANT_BUFFER_SIZE, D3D11_BIND_CONSTANT_BUFFER);
			Direct3D::checkError(Direct3D::device->CreateBuffer(&constantBufferDescription, nullptr, &constantBuffer));

			Direct3D::checkError(Direct3D::device->CreatePixelShader(pixelShaderByteCode.data(),
				pixelShaderByteCode.size(), nullptr, &pixelShader));

			Direct3D::checkError(Direct3D::device->CreateVertexShader(vertexShaderByteCode.data(),
				vertexShaderByteCode.size(), nullptr, &vertexShader));

			pixelShaderByteCode.resize(0);
			vertexShaderByteCode.resize(0);

			initialized = true;
		}

		void Direct3DPipeline::set(const std::string& name, const char* rawData, unsigned int size)
		{
			if (constantPositions.find(name) == constantPositions.end())
			{
				constantPositions[name] = constantDataSize;
				constantDataSize += size;
				constantData.resize(constantDataSize);
			}

			memcpy(&constantData[constantPositions[name]], rawData, size);
		}

		void Direct3DPipeline::set(const string& name, float value)
		{
			set(name, reinterpret_cast<const char*>(&value), sizeof(float));
		}

		void Direct3DPipeline::set(const string& name, int value)
		{
			set(name, reinterpret_cast<const char*>(&value), sizeof(int));
		}

		void Direct3DPipeline::set(const string& name, const Matrix44& value)
		{
			Matrix44 columnMajorValue = value;
			columnMajorValue.transpose();

			set(name, reinterpret_cast<const char*>(&columnMajorValue), sizeof(Matrix44));
		}

		void Direct3DPipeline::set(const string& name, const Vector2& value)
		{
			set(name, reinterpret_cast<const char*>(&value), sizeof(Vector2));
		}

		void Direct3DPipeline::set(const string& name, const Vector3& value)
		{
			set(name, reinterpret_cast<const char*>(&value), sizeof(Vector3));
		}

		void Direct3DPipeline::set(const string& name, const Vector4& value)
		{
			set(name, reinterpret_cast<const char*>(&value), sizeof(Vector4));
		}

		void Direct3DPipeline::set(const string& structName, const string& name, float value)
		{
		}

		void Direct3DPipeline::set(const string& structName, const string& name, int value)
		{
		}

		void Direct3DPipeline::set(const string& structName, const string& name, const Matrix44& value)
		{
		}

		void Direct3DPipeline::set(const string& structName, const string& name, const Vector2& value)
		{
		}

		void Direct3DPipeline::set(const string& structName, const string& name, const Vector3& value)
		{
		}

		void Direct3DPipeline::set(const string& structName, const string& name, const Vector4& value)
		{
		}
	}
}
