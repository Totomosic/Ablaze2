#pragma once
#include "Common.h"
#include "Resources\Asset.h"

namespace Ablaze
{

	enum class ShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};

	class AB_API ShaderProgram : public Asset, public GLObject
	{
	private:
		ShaderType m_Type;
		String m_Source;
		bool m_Compiled;

	private:
		ShaderProgram(ShaderType type, const String& source);
		ShaderProgram();

	public:
		ShaderType Type() const;
		const String& Source() const;
		bool IsCompiled() const;

		void SetType(ShaderType type);
		void SetSource(const String& source);

		void Compile();
		void Reload() override;
		void Bind() const override;
		void Unbind() const override;

		String ToString() const override;

		friend class ResourceManager;
		friend class Shader;

	private:
		static ShaderProgram* FromFile(ShaderType type, const String& filename);
		static ShaderProgram* FromSource(ShaderType type, const String& source);

	private:
		void Create();

	};

}