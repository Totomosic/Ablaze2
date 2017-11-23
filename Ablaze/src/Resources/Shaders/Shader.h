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
		static const Shader* s_CurrentlyBound;

	public:
		static const int VertexShader = 0;
		static const int GeometryShader = 1;
		static const int FragmentShader = 2;

	private:
		Resource<ShaderProgram> m_ShaderPrograms[3];
		mutable std::unordered_map<String, int> m_UniformLocations;

	private:
		Shader(const String& vertexSrc, const String& fragmentSrc);
		Shader(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		~Shader(); // Prevent stack objects and can only be deleted by ResourceManager

	public:
		void Bind() const override;
		void Unbind() const override;

		void Reload() override;
		void AttachShader(const Resource<ShaderProgram>& shader);

		void SetUniform(const String& uniformName, bool value) const;
		void SetUniform(const String& uniformName, int value) const;
		void SetUniform(const String& uniformName, float value) const;
		void SetUniform(const String& uniformName, const Maths::Vec2& value) const;
		void SetUniform(const String& uniformName, const Maths::Vec3& value) const;
		void SetUniform(const String& uniformName, const Maths::Vec4& value) const;
		void SetUniform(const String& uniformName, const Maths::Plane& value) const;
		void SetUniform(const String& uniformName, const Maths::Ray& value) const;
		void SetUniform(const String& uniformName, const Maths::Mat4& value) const;
		void SetUniform(const String& uniformName, const Color& value) const;

		template<typename T>
		void SetUniform(const String& uniformName, const T& value) const
		{
			Bind();
			SetUniform(uniformName, value);
		}

		template<typename T>
		void SetTexture(const String& samplerName, const Resource<T>& texture)
		{
			texture->Bind();
			SetUniform<int>(samplerName, texture->GetBindPort());
		}

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

		friend class ResourceManager;

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