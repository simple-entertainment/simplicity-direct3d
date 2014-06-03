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
#ifndef DIRECT3DTEXTURE_H_
#define DIRECT3DTEXTURE_H_

#include <D3D11.h>

#include <simplicity/rendering/Texture.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
	namespace direct3d
	{
		class Direct3DTexture : public Texture
		{
			public:
				/**
				* @param data The texture data.
				* @param length The length of the data.
				*/
				Direct3DTexture(const char* data, unsigned int length);

				/**
				* @param rawData The raw RGBA texture data.
				* @param width The width of the texture.
				* @param height The height of the texture.
				*/
				Direct3DTexture(const char* rawData, unsigned int width, unsigned int height);

				/**
				* @param image The image resource.
				*/
				Direct3DTexture(Resource& image);

				~Direct3DTexture();

				void apply(Pipeline& pipeline) override;

				unsigned int getHeight() override;

				unsigned int getWidth() override;

				void init() override;

			private:
				std::string data;

				unsigned int height;

				bool initialized;

				const char* rawData;

				ID3D11ShaderResourceView* shaderResourceView;

				ID3D11Texture2D* texture;

				unsigned int width;
		};
	}
}

#endif /* DIRECT3DTEXTURE_H_ */
