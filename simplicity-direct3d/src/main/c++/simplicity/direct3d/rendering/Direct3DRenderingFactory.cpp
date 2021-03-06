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
#include "Direct3DRenderingFactory.h"
#include "Direct3DTexture.h"

using namespace std;

namespace simplicity
{
	namespace direct3d
	{
		unique_ptr<Texture> Direct3DRenderingFactory::createTexture(const char* data, unsigned int length)
		{
			return unique_ptr<Texture>(new Direct3DTexture(data, length));
		}

		unique_ptr<Texture> Direct3DRenderingFactory::createTexture(const char* rawData, unsigned int width,
				unsigned int height)
		{
			return unique_ptr<Texture>(new Direct3DTexture(rawData, width, height));
		}

		unique_ptr<Texture> Direct3DRenderingFactory::createTexture(Resource& image)
		{
			return unique_ptr<Texture>(new Direct3DTexture(image));
		}
	}
}
