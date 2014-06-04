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
#include "../rendering/Direct3D.h"
#include "Direct3DMesh.h"

using namespace std;

namespace simplicity
{
	namespace direct3d
	{
		Direct3DMesh::Direct3DMesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices,
				Access access) :
			access(access),
			color(),
			indexBuffer(nullptr),
			indexCount(0),
			initialIndices(indices),
			initialized(false),
			initialVertices(vertices),
			normalMap(nullptr),
			texture(nullptr),
			vertexBuffer(nullptr),
			visible(true)
		{
		}

		Direct3DMesh::~Direct3DMesh()
		{
			if (indexBuffer != nullptr)
			{
				indexBuffer->Release();
			}

			if (vertexBuffer != nullptr)
			{
				vertexBuffer->Release();
			}
		}

		Mesh::Access Direct3DMesh::getAccess() const
		{
			return access;
		}

		const Vector4& Direct3DMesh::getColor() const
		{
			return color;
		}

		ID3D11Buffer* Direct3DMesh::getIndexBuffer() const
		{
			return indexBuffer;
		}

		unsigned int Direct3DMesh::getIndexCount() const
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialIndices.size();
			}

			return indexCount;
		}

		unsigned int* Direct3DMesh::getIndices()
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialIndices.data();
			}

			// TODO
			return nullptr;
		}

		const unsigned int* Direct3DMesh::getIndices() const
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialIndices.data();
			}

			// TODO
			return nullptr;
		}

		Texture* Direct3DMesh::getNormalMap() const
		{
			return normalMap;
		}

		Model::PrimitiveType Direct3DMesh::getPrimitiveType() const
		{
			return PrimitiveType::TRIANGLE_LIST;
		}

		Texture* Direct3DMesh::getTexture() const
		{
			return texture;
		}

		unsigned short Direct3DMesh::getTypeID() const
		{
			return TYPE_ID;
		}

		ID3D11Buffer* Direct3DMesh::getVertexBuffer() const
		{
			return vertexBuffer;
		}

		unsigned int Direct3DMesh::getVertexCount() const
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialVertices.size();
			}

			// TODO
			return 0;
		}

		Vertex* Direct3DMesh::getVertices()
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialVertices.data();
			}

			// TODO
			return nullptr;
		}

		const Vertex* Direct3DMesh::getVertices() const
		{
			if (!initialized || access == Access::READ_LOCAL)
			{
				return initialVertices.data();
			}

			// TODO
			return nullptr;
		}

		void Direct3DMesh::init()
		{
			if (initialized)
			{
				return;
			}

			D3D11_BUFFER_DESC vertexBufferDescription;
			memset(&vertexBufferDescription, 0, sizeof(D3D11_BUFFER_DESC));
			vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDescription.ByteWidth = sizeof(Vertex) * initialVertices.size();
			vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;

			D3D11_SUBRESOURCE_DATA vertexBufferData;
			memset(&vertexBufferData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
			vertexBufferData.pSysMem = initialVertices.data();

			Direct3D::checkError(Direct3D::device->CreateBuffer(&vertexBufferDescription, &vertexBufferData,
				&vertexBuffer));

			D3D11_BUFFER_DESC indexBufferDescription;
			memset(&indexBufferDescription, 0, sizeof(D3D11_BUFFER_DESC));
			indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDescription.ByteWidth = sizeof(unsigned int) * initialIndices.size();
			indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;

			D3D11_SUBRESOURCE_DATA indexBufferData;
			memset(&indexBufferData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
			indexBufferData.pSysMem = initialIndices.data();

			Direct3D::checkError(Direct3D::device->CreateBuffer(&indexBufferDescription, &indexBufferData,
				&indexBuffer));

			if (access != Access::READ_LOCAL)
			{
				initialVertices.resize(0);

				indexCount = initialIndices.size();
				initialIndices.resize(0);
			}

			initialized = true;
		}

		bool Direct3DMesh::isVisible() const
		{
			return visible;
		}

		void Direct3DMesh::resizeIndices(unsigned int size)
		{
			if (!initialized)
			{
				initialIndices.resize(size);
			}

			// TODO
		}

		void Direct3DMesh::resizeVertices(unsigned int size)
		{
			if (!initialized)
			{
				initialVertices.resize(size);
			}

			// TODO
		}

		void Direct3DMesh::setColor(const Vector4& color)
		{
			this->color = color;
		}

		void Direct3DMesh::setNormalMap(Texture* normalMap)
		{
			this->normalMap = normalMap;
		}

		void Direct3DMesh::setPrimitiveType(PrimitiveType /* primitiveType */)
		{
		}

		void Direct3DMesh::setTexture(Texture* texture)
		{
			this->texture = texture;
		}

		void Direct3DMesh::setVisible(bool visible)
		{
			this->visible = visible;
		}
	}
}
