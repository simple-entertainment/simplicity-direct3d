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
#ifndef DIRECT3DMESH_H_
#define DIRECT3DMESH_H_

#include <vector>

#include <D3D11.h>

#include <simplicity/model/Mesh.h>

namespace simplicity
{
	namespace direct3d
	{
		class Direct3DMesh : public Mesh
		{
			public:
				/**
				* <p>
				* An ID unique to the this model class.
				* </p>
				*/
				static const unsigned int TYPE_ID = 15;

				/**
				 * @param indices The indices into the collection of vertices.
				 * @param vertices The collection of vertices.
				 * @param access The access to grant to this mesh's internal data i.e. vertices and indices after
				 * initialization.
				 */
				Direct3DMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
					Access access = Access::NONE);

				virtual ~Direct3DMesh();

				Access getAccess() const override;

				const Vector4& getColor() const override;

				ID3D11Buffer* getIndexBuffer() const;

				unsigned int getIndexCount() const override;
				
				unsigned int* getIndices() override;

				const unsigned int* getIndices() const override;

				Texture* getNormalMap() const override;

				PrimitiveType getPrimitiveType() const override;

				Texture* getTexture() const override;

				unsigned short getTypeID() const override;

				ID3D11Buffer* getVertexBuffer() const;

				unsigned int getVertexCount() const override;

				Vertex* getVertices() override;

				const Vertex* getVertices() const override;

				void init() override;

				bool isVisible() const override;

				void resizeIndices(unsigned int size) override;

				void resizeVertices(unsigned int size) override;

				void setColor(const Vector4& color) override;

				void setNormalMap(Texture* normalMap) override;

				void setPrimitiveType(PrimitiveType primitiveType) override;

				void setTexture(Texture* texture) override;

				void setVisible(bool visible) override;

			private:
				Access access;

				Vector4 color;

				ID3D11Buffer* indexBuffer;

				unsigned int indexCount;

				std::vector<unsigned int> initialIndices;

				mutable bool initialized;

				std::vector<Vertex> initialVertices;

				Texture* normalMap;

				Texture* texture;

				ID3D11Buffer* vertexBuffer;

				bool visible;
		};
	}
}

#endif /* DIRECT3DMESH_H_ */
