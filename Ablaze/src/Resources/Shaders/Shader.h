#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include "Utils\FileSystem\FileSystem.h"

namespace Ablaze
{

	class Texture2D;

	class AB_API Shader : public Asset, public GLObject
	{
	private:
		static const int VertexShader = 0;
		static const int GeometryShader = 1;
		static const int FragmentShader = 2;

		static std::vector<Shader*> s_Shaders;
		static std::unordered_map<String, String> s_DefaultHeaders;

	private:
		mutable std::unordered_map<String, int> m_UniformLocations;

	public:
		Shader(const String& vertexSrc, const String& fragmentSrc);
		Shader(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		~Shader() override;

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
		void SetTexture(const String& samplerName, T* texture, int bindPort)
		{
			texture->Bind(bindPort);
			SetUniform(samplerName, bindPort);
		}

		String ToString() const override;

		friend class ResourceManager;
		friend class Engine;

	public:
		static Shader* FromSource(const String& vertexSrc, const String& fragmentSrc);
		static Shader* FromSource(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		static Shader* FromFile(const Filepath& vertexFile, const Filepath& fragmentFile);
		static Shader* FromFile(const Filepath& vertexFile, const Filepath& geometryFile, const Filepath& fragmentFile);
		static Shader* FromFile(const Filepath& shaderFile);

		static const std::vector<Shader*>& GetAll();
		
	private:
		void Create();
		void BuildProgram(const String& vertexSrc, const String& fragmentSrc);
		void BuildProgram(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc);
		uint AttachShader(const String& shaderSource, GLenum shaderType);
		int GetUniformLocation(const String& uniformName) const;

	private:
		static void Initialise();
		static void AddHeader(const String& headerName, const String& source);
		static bool HeaderExists(const String& headerName);
		static String& GetHeader(const String& headerName);
		static String PreprocessShader(const String& shaderSource, const Filepath& thisFilename);

	};

}