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
#include "Direct3DRenderer.h"

#include <simplicity/model/Text.h>

#include "../model/Direct3DMesh.h"
#include "Direct3D.h"

using namespace std;

namespace simplicity
{
	namespace direct3d
	{
		Direct3DRenderer::Direct3DRenderer() :
			clearColorBuffer(true),
			clearDepthBuffer(true),
			clearingColor(0.0f, 0.0f, 0.0f, 1.0f),
			clearStencilBuffer(true),
			defaultPipeline()
		{
		}

		bool Direct3DRenderer::clearsColorBuffer() const
		{
			return clearColorBuffer;
		}

		bool Direct3DRenderer::clearsDepthBuffer() const
		{
			return clearDepthBuffer;
		}

		bool Direct3DRenderer::clearsStencilBuffer() const
		{
			return clearStencilBuffer;
		}

		void Direct3DRenderer::dispose()
		{
		}

		const Vector4& Direct3DRenderer::getClearingColor() const
		{
			return clearingColor;
		}

		Pipeline* Direct3DRenderer::getDefaultPipeline()
		{
			return defaultPipeline.get();
		}

		void Direct3DRenderer::init()
		{
			if (clearColorBuffer)
			{
				Direct3D::deviceContext->
					ClearRenderTargetView(Direct3D::renderTargetView, clearingColor.getData());
			}
			if (clearDepthBuffer)
			{
				Direct3D::deviceContext->
					ClearDepthStencilView(Direct3D::depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
			}
			if (clearStencilBuffer)
			{
				Direct3D::deviceContext->
					ClearDepthStencilView(Direct3D::depthStencilView, D3D10_CLEAR_STENCIL, 1.0f, 0);
			}
		}

		bool Direct3DRenderer::isScissorEnabled() const
		{
			return false;
		}

		void Direct3DRenderer::render(const Model& model)
		{
			if (model.getTypeID() == Direct3DMesh::TYPE_ID)
			{
				const Direct3DMesh* d3dMesh = static_cast<const Direct3DMesh*>(&model);

				UINT offset = 0;
				unsigned int stride = sizeof(Vertex);
				ID3D11Buffer* vertexBuffer = d3dMesh->getVertexBuffer();
				Direct3D::deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

				ID3D11Buffer* indexBuffer = d3dMesh->getIndexBuffer();
				Direct3D::deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

				Direct3D::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				Direct3D::deviceContext->DrawIndexed(d3dMesh->getIndexCount(), 0, 0);
			}
		}

		void Direct3DRenderer::setClearBuffers(bool clearBuffers)
		{
			clearColorBuffer = clearBuffers;
			clearDepthBuffer = clearBuffers;
			clearStencilBuffer = clearBuffers;
		}

		void Direct3DRenderer::setClearColorBuffer(bool clearColorBuffer)
		{
			this->clearColorBuffer = clearColorBuffer;
		}

		void Direct3DRenderer::setClearDepthBuffer(bool clearDepthBuffer)
		{
			this->clearDepthBuffer = clearDepthBuffer;
		}

		void Direct3DRenderer::setClearingColor(const Vector4& clearingColor)
		{
			this->clearingColor = clearingColor;
		}

		void Direct3DRenderer::setClearStencilBuffer(bool clearStencilBuffer)
		{
			this->clearStencilBuffer = clearStencilBuffer;
		}

		void Direct3DRenderer::setDefaultPipeline(unique_ptr<Pipeline> defaultPipeline)
		{
			this->defaultPipeline = move(defaultPipeline);
		}

		void Direct3DRenderer::setScissor(const Vector<unsigned int, 2>& /* topLeft */,
			const Vector<unsigned int, 2>& /* bottomRight */)
		{
		}

		void Direct3DRenderer::setScissorEnabled(bool /* scissorEnabled */)
		{
		}
	}
}
