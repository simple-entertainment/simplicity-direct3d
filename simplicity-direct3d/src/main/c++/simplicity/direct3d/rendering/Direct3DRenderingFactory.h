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
#ifndef DIRECT3DRENDERINGFACTORY_H_
#define DIRECT3DRENDERINGFACTORY_H_

#include <simplicity/rendering/RenderingFactory.h>

namespace simplicity
{
	namespace direct3d
	{
		/**
		 * <p>
		 * A factory that creates textures implemented using Direct3D.
		 * </p>
		 */
		class SIMPLE_API Direct3DRenderingFactory : public RenderingFactory
		{
			public:
				std::unique_ptr<Texture> createTexture(const char* data, unsigned int length) override;

				std::unique_ptr<Texture> createTexture(const char* rawData, unsigned int width,
					unsigned int height) override;

				std::unique_ptr<Texture> createTexture(Resource& image) override;
		};
	}
}

#endif /* DIRECT3DRENDERINGFACTORY_H_ */
