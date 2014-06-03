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
#ifndef DIRECT3DRENDERINGENGINE_H_
#define DIRECT3DRENDERINGENGINE_H_

#include <map>

#include <D3D11.h>

#include <simplicity/rendering/RenderingEngine.h>

#include "Direct3DRenderer.h"

namespace simplicity
{
	namespace direct3d
	{
		class Direct3DRenderingEngine : public RenderingEngine
		{
			public:
				Direct3DRenderingEngine();

				void addLight(Entity& light) override;

				void addRenderer(std::unique_ptr<Renderer> renderer) override;

				void advance() override;

				Entity* getCamera() const override;

				const Graph* getGraph() const override;

				int getHeight() const override;

				int getWidth() const override;

				void onPlay() override;

				void onStop() override;

				std::unique_ptr<Renderer> removeRenderer(Renderer* renderer) override;

				void setCamera(Entity* camera) override;

				void setGraph(Graph* graph) override;

				void setHeight(int height) override;

				void setWidth(int width) override;

			private:
				struct CameraProperties
				{
					Model* bounds;
					Vector3 boundsPosition;
					Vector3 position;
					Matrix44 transform;
				};

				Entity* camera;

				Vector4 clearingColour;

				ID3D11Texture2D* depthStencilBuffer;

				Graph* graph;

				int height;

				std::vector<Entity*> lights;

				std::vector<Model*> models;

				std::vector<std::unique_ptr<Renderer>> renderers;

				IDXGISwapChain* swapChain;

				int width;

				HWND window;

				void createDepthStencilView();

				void createRenderTargetView();

				DXGI_SWAP_CHAIN_DESC createSwapChainDescription();

				CameraProperties getCameraProperties() const;

				void initViewport();

				void render(Renderer& renderer, const Entity& entity);
		};
	}
}

#endif /* DIRECT3DRENDERINGENGINE_H_ */
