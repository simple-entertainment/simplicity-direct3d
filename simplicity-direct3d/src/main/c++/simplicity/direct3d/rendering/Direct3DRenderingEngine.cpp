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
#include <algorithm>

#include <simplicity/common/AddressEquals.h>
#include <simplicity/math/MathFunctions.h>
#include <simplicity/rendering/Camera.h>
#include <simplicity/rendering/Light.h>
#include <simplicity/Simplicity.h>

#include <simplicity/winapi/windowing/WinAPIEngine.h>

#include "Direct3D.h"
#include "Direct3DRenderingEngine.h"

using namespace std;
using namespace simplicity::winapi;

namespace simplicity
{
	namespace direct3d
	{
		Direct3DRenderingEngine::Direct3DRenderingEngine() :
			camera(),
			depthStencilBuffer(NULL),
			graph(NULL),
			height(768),
			lights(),
			renderers(),
			swapChain(NULL),
			width(1024),
			window(NULL)
		{
		}

		void Direct3DRenderingEngine::addLight(Entity& light)
		{
			lights.push_back(&light);
		}

		void Direct3DRenderingEngine::addRenderer(unique_ptr<Renderer> renderer)
		{
			renderers.push_back(move(renderer));
		}

		void Direct3DRenderingEngine::advance()
		{
			CameraProperties cameraProperties = getCameraProperties();

			std::vector<Entity*> entities;
			if (cameraProperties.bounds == NULL || graph == NULL)
			{
				entities = Simplicity::getScene()->getEntities();
			}
			else
			{
				entities =
					graph->getEntitiesWithinBounds(*cameraProperties.bounds,
					cameraProperties.boundsPosition);
			}

			for (unique_ptr<Renderer>& renderer : renderers)
			{
				renderer->init();

				renderer->getDefaultPipeline()->apply();
				renderer->getDefaultPipeline()->set("cameraPosition", cameraProperties.position);
				renderer->getDefaultPipeline()->set("cameraTransform", cameraProperties.transform);

				for (unsigned int index = 0; index < lights.size(); index++)
				{
					lights[index]->getComponent<Light>()->apply(*renderer->getDefaultPipeline(),
						getPosition3(lights[index]->getTransform()));
				}

				for (Entity* entity : entities)
				{
					render(*renderer, *entity);
				}

				renderer->dispose();
			}

			Direct3D::checkError(swapChain->Present(NULL, NULL));
		}

		void Direct3DRenderingEngine::createDepthStencilView()
		{
			D3D11_TEXTURE2D_DESC depthStencilDescription;
			depthStencilDescription.ArraySize = 1;
			depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDescription.CPUAccessFlags = 0;
			depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDescription.Height = height;
			depthStencilDescription.MipLevels = 1;
			depthStencilDescription.MiscFlags = 0;
			depthStencilDescription.SampleDesc.Count = 1;
			depthStencilDescription.SampleDesc.Quality = 0;
			depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDescription.Width = width;

			Direct3D::checkError(Direct3D::device->CreateTexture2D(&depthStencilDescription, NULL,
				&depthStencilBuffer));
			Direct3D::checkError(Direct3D::device->CreateDepthStencilView(depthStencilBuffer, NULL,
				&Direct3D::depthStencilView));
		}

		void Direct3DRenderingEngine::createRenderTargetView()
		{
			ID3D11Texture2D* backBuffer = NULL;
			Direct3D::checkError(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer));

			Direct3D::checkError(Direct3D::device->CreateRenderTargetView(backBuffer, NULL,
				&Direct3D::renderTargetView));

			backBuffer->Release();
		}

		DXGI_SWAP_CHAIN_DESC Direct3DRenderingEngine::createSwapChainDescription()
		{
			DXGI_SWAP_CHAIN_DESC swapChainDescription;
			ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

			swapChainDescription.BufferCount = 1;
			swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDescription.BufferDesc.Height = height;
			swapChainDescription.BufferDesc.Width = width;
			swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			swapChainDescription.OutputWindow = window;
			swapChainDescription.SampleDesc.Count = 1;
			swapChainDescription.SampleDesc.Quality = 0;
			swapChainDescription.Windowed = true;

			return swapChainDescription;
		}

		Entity* Direct3DRenderingEngine::getCamera() const
		{
			return camera;
		}

		Direct3DRenderingEngine::CameraProperties Direct3DRenderingEngine::getCameraProperties() const
		{
			CameraProperties properties;
			properties.bounds = NULL;

			if (camera == NULL)
			{
				properties.position = Vector3(0.0f, 0.0f, 0.0f);
				properties.transform.setIdentity();
			}
			else
			{
				properties.bounds = camera->getComponent<Model>(Category::BOUNDS);
				if (properties.bounds != NULL)
				{
					properties.boundsPosition = getPosition3(camera->getTransform() *
						properties.bounds->getTransform());
				}

				Camera* cameraComponent = camera->getComponent<Camera>();
				if (cameraComponent == NULL)
				{
					properties.transform.setIdentity();
				}

				Matrix44 view = camera->getTransform() * cameraComponent->getTransform();
				properties.position = getPosition3(view);
				view.invert();

				Matrix44 projection = cameraComponent->getProjection();

				properties.transform = projection * view;
			}

			return properties;
		}

		const Graph* Direct3DRenderingEngine::getGraph() const
		{
			return graph;
		}

		int Direct3DRenderingEngine::getHeight() const
		{
			return height;
		}

		int Direct3DRenderingEngine::getWidth() const
		{
			return width;
		}

		void Direct3DRenderingEngine::initViewport()
		{
			D3D11_VIEWPORT viewport;
			memset(&viewport, 0, sizeof(D3D10_VIEWPORT));

			viewport.Height = static_cast<float>(height);
			viewport.MaxDepth = 1.0f;
			viewport.MinDepth = 0.0f;
			viewport.Width = static_cast<float>(width);
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;

			Direct3D::deviceContext->RSSetViewports(1, &viewport);
		}

		void Direct3DRenderingEngine::onPlay()
		{
			window = Simplicity::getEngine<WinAPIEngine>()->getWindow();

			UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
			//flags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

			D3D_FEATURE_LEVEL supportedFeatureLevel;
			DXGI_SWAP_CHAIN_DESC swapChainDescription = createSwapChainDescription();
			Direct3D::checkError(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, 0,
				D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &Direct3D::device, &supportedFeatureLevel,
				&Direct3D::deviceContext));

			createDepthStencilView();
			createRenderTargetView();
			Direct3D::deviceContext->OMSetRenderTargets(1, &Direct3D::renderTargetView, Direct3D::depthStencilView);

			initViewport();
		}

		void Direct3DRenderingEngine::onStop()
		{
			if (depthStencilBuffer != NULL)
			{
				depthStencilBuffer->Release();
				depthStencilBuffer = NULL;
			}

			if (Direct3D::depthStencilView != NULL)
			{
				Direct3D::depthStencilView->Release();
				Direct3D::depthStencilView = NULL;
			}

			if (Direct3D::device != NULL)
			{
				Direct3D::device->Release();
				Direct3D::device = NULL;
			}

			if (Direct3D::deviceContext != NULL)
			{
				Direct3D::deviceContext->ClearState();
				Direct3D::deviceContext->Release();
				Direct3D::deviceContext = NULL;
			}

			if (Direct3D::renderTargetView != NULL)
			{
				Direct3D::renderTargetView->Release();
				Direct3D::renderTargetView = NULL;
			}

			if (swapChain != NULL)
			{
				swapChain->Release();
				swapChain = NULL;
			}
		}

		unique_ptr<Renderer> Direct3DRenderingEngine::removeRenderer(Renderer* renderer)
		{
			unique_ptr<Renderer> removedRenderer;

			vector<unique_ptr<Renderer>>::iterator result =
				find_if(renderers.begin(), renderers.end(), AddressEquals<Renderer>(*renderer));
			if (result != renderers.end())
			{
				removedRenderer = move(*result);
				renderers.erase(result);
				renderer = NULL;
			}

			return move(removedRenderer);
		}

		void Direct3DRenderingEngine::render(Renderer& renderer, const Entity& entity)
		{
			for (Model* model : entity.getComponents<Model>(Category::RENDER))
			{
				renderer.getDefaultPipeline()->set("worldTransform", entity.getTransform() * model->getTransform());

				renderer.render(*model);
			}
		}

		void Direct3DRenderingEngine::setCamera(Entity* camera)
		{
			this->camera = camera;
		}

		void Direct3DRenderingEngine::setGraph(Graph* graph)
		{
			this->graph = graph;
		}

		void Direct3DRenderingEngine::setHeight(int height)
		{
			this->height = height;
		}

		void Direct3DRenderingEngine::setWidth(int width)
		{
			this->width = width;
		}
	}
}
