#pragma once
#include "Common.h"
#include "Resources\Resource.h"
#include "ShaderProgram.h"
#include "Utils\FileSystem\FileSystem.h"

namespace Ablaze
{

	class AB_API Shader : public Asset, public GLObject
	{
	private:
		static const int VertexShader = 0;
		static const int GeometryShader = 1;
		static const int FragmentShader = 2;

	private:
		mutable std::unordered_map<String, int> m_UniformLocations;

	public:
		Shader(const String& vertexSrc, const String& fragmentSrc);
		Shader(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		~Shader();

	public:
		void Bind() const override;
		void Unbind() const override;

		void Reload() override;

		void SetUniform(const String& uniformName, bool value) const;
		void SetUniform(const String& uniformName, int value) const;
		void SetUniform(const String& uniformName, uint value) const;
		void SetUniform(const String& uniformName, float value) const;
		void SetUniform(const String& uniformName, const Maths::Vector2f& value) const;
		void SetUniform(const String& uniformName, const Maths::Vector3f& value) const;
		void SetUniform(const String& uniformName, const Maths::Vector4f& value) const;
		void SetUniform(const String& uniformName, const Maths::Vector2i& value) const;
		void SetUniform(const String& uniformName, const Maths::Vector3i& value) const;
		void SetUniform(const String& uniformName, const Maths::Vector4i& value) const;
		void SetUniform(const String& uniformName, const Maths::Plane& value) const;
		void SetUniform(const String& uniformName, const Maths::Ray& value) const;
		void SetUniform(const String& uniformName, const Maths::Matrix4f& value) const;
		void SetUniform(const String& uniformName, const Color& value) const;

		template<typename T>
		void SetTexture(const String& samplerName, const std::shared_ptr<T>& texture)
		{
			texture->Bind();
			SetUniform(samplerName, (int)texture->GetBindPort());
		}

		String ToString() const override;

		friend class ResourceManager;
		template<typename> friend class std::shared_ptr;

	private:
		static Shader* FromSource(const String& vertexSrc, const String& fragmentSrc);
		static Shader* FromSource(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		static Shader* FromFile(const String& vertexFile, const String& fragmentFile);
		static Shader* FromFile(const String& vertexFile, const String& geometryFile, const String& fragmentFile);
		static Shader* FromFile(const String& shaderFile);
		
	private:
		void Create();
		void BuildProgram(const String& vertexSrc, const String& fragmentSrc);
		void BuildProgram(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		uint AttachShader(const String& shaderSource, GLenum shaderType);
		int GetUniformLocation(const String& uniformName) const;

	};

}