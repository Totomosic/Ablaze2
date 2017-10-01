#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "Utils\FileSystem\FileSystem.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API Shader : public Asset, public GLObject
	{
	private:
		static const Shader* s_CurrentlyBound;

	private:
		mutable std::unordered_map<String, int> m_UniformLocations;
		String m_VertexPath;
		String m_FragmentPath;

	private:
		Shader(const String& vertexPath, const String& fragmentPath, bool fromFile);
		Shader(const String& vertexSrc, const String& fragmentSrc);
		Shader(const String& ShaderSrc);
		~Shader(); // Prevent stack objects and can only be deleted by ResourceManager

	public:
		void Bind() const override;
		void Unbind() const override;
		bool IsFromFile() const override;

		void Reload() override;

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
			SetUniform(uniformName, value);
		}

		template<typename T>
		void SetTexture(const String& samplerName, const Resource<T>& texture)
		{
			texture->Bind();
			SetUniform<int>(samplerName, texture->GetBindPort());
		}

		String ToString() const override;

		friend class ResourceManager;

	private:
		static Shader* FromSource(const String& vertexSrc, const String& fragmentSrc);
		static Shader* FromFile(const String& vertexFile, const String& fragmentFile);
		static Shader* FromFile(const String& shaderFile); // Create custom file format with both vertex and fragment shaders in it
		
	private:
		void Create();
		void BuildProgram(const String& vertexSrc, const String& fragmentSrc);
		uint AttachShader(const String& shaderSource, GLenum shaderType);
		int GetUniformLocation(const String& uniformName) const;

	};

}