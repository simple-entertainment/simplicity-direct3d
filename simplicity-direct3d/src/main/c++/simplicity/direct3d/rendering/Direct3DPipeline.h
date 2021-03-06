/*
* Copyright � 2014 Simple Entertainment Limited
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
#ifndef DIRECT3DPIPELINE_H_
#define DIRECT3DPIPELINE_H_

#include <map>

#include <D3D11.h>

#include <simplicity/rendering/Pipeline.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
	namespace direct3d
	{
		class Direct3DPipeline : public Pipeline
		{
			public:
				Direct3DPipeline(Resource& vertexShaderByteCode, Resource& pixelShaderByteCode);

				virtual ~Direct3DPipeline();

				void apply() override;

				void set(const std::string& name, float value) override;

				void set(const std::string& name, int value) override;

				void set(const std::string& name, const Matrix44& value) override;

				void set(const std::string& name, const Vector2& value) override;

				void set(const std::string& name, const Vector3& value) override;

				void set(const std::string& name, const Vector4& value) override;

				void set(const std::string& structName, const std::string& name, float value) override;

				void set(const std::string& structName, const std::string& name, int value) override;

				void set(const std::string& structName, const std::string& name, const Matrix44& value) override;

				void set(const std::string& structName, const std::string& name, const Vector2& value) override;

				void set(const std::string& structName, const std::string& name, const Vector3& value) override;

				void set(const std::string& structName, const std::string& name, const Vector4& value) override;

			private:
				ID3D11Buffer* constantBuffer;

				std::string constantData;

				unsigned int constantDataSize;

				std::map<std::string, unsigned int> constantPositions;

				bool initialized;

				ID3D11PixelShader* pixelShader;

				std::string pixelShaderByteCode;

				ID3D11VertexShader* vertexShader;

				std::string vertexShaderByteCode;

				void init();

				void set(const std::string& name, const char* rawData, unsigned int size);
		};
	}
}

#endif /* DIRECT3DSHADER_H_ */
