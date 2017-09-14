#include "Shader.h"

namespace Ablaze
{

	const Shader* Shader::s_CurrentlyBound = nullptr;

	Shader::Shader(const String& vertexPath, const String& fragmentPath, bool file) : GLObject(), Asset(),
		m_UniformLocations(), m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
	{
		Create();

		Handle vertexFile = FileSystem::Open(vertexPath, OpenMode::Read);
		Handle fragmentFile = FileSystem::Open(fragmentPath, OpenMode::Read);
		BuildProgram(FileSystem::ReadText(vertexFile), FileSystem::ReadText(fragmentFile));
		FileSystem::Close(vertexFile);
		FileSystem::Close(fragmentFile);
	}

	Shader::Shader(const String& vertexSrc, const String& fragmentSrc) : GLObject(), Asset(),
		m_UniformLocations(), m_VertexPath("-"), m_FragmentPath("-")
	{
		Create();
		BuildProgram(vertexSrc, fragmentSrc);
	}

	Shader::Shader(const String& shaderSrc) : GLObject(), Asset(shaderSrc),
		m_UniformLocations(), m_VertexPath("-"), m_FragmentPath("-")
	{
		Create();
	}

	void Shader::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			glUseProgram(m_Id);
			s_CurrentlyBound = this;
		}
	}

	void Shader::Unbind() const
	{
		// Does nothing
	}

	void Shader::Reload()
	{
		Create();
		//BuildProgram();
	}

	bool Shader::IsFromFile() const
	{
		return Asset::IsFromFile() | (m_VertexPath != "-") | (m_FragmentPath != "-");
	}

	void Shader::SetUniform(const String& uniformName, int value) const
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}

	void Shader::SetUniform(const String& uniformName, float value) const
	{
		glUniform1f(GetUniformLocation(uniformName), value);
	}

	void Shader::SetUniform(const String& uniformName, bool value) const
	{
		SetUniform(uniformName, (int)value);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vec2& value) const
	{
		glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vec3& value) const
	{
		glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vec4& value) const
	{
		glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Plane& value) const
	{
		glUniform4f(GetUniformLocation(uniformName), value.normal.x, value.normal.y, value.normal.z, value.height);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Ray& value) const
	{
		glUniform3f(GetUniformLocation(uniformName), value.direction.x, value.direction.y, value.direction.z);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Mat4& value) const
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, value.values);
	}

	void Shader::SetUniform(const String& uniformName, const Color& value) const
	{
		glUniform4f(GetUniformLocation(uniformName), value.r, value.g, value.b, value.a);
	}

	String Shader::ToString() const
	{
		return "Shader";
	}

	Shader* Shader::FromFile(const String& vertexPath, const String& fragmentPath)
	{
		return new Shader(vertexPath, fragmentPath, true);
	}

	Shader* Shader::FromFile(const String& shaderPath)
	{
		return new Shader(shaderPath);
	}

	Shader* Shader::FromSource(const String& vertexSrc, const String& fragmentSrc)
	{
		return new Shader(vertexSrc, fragmentSrc);
	}

	void Shader::Create()
	{
		m_Id = glCreateProgram();
	}

	void Shader::BuildProgram(const String& vertexSrc, const String& fragmentSrc)
	{
		uint vertex = AttachShader(vertexSrc, GL_VERTEX_SHADER);
		uint fragment = AttachShader(fragmentSrc, GL_FRAGMENT_SHADER);
		glLinkProgram(m_Id);

		glDetachShader(m_Id, vertex);
		glDetachShader(m_Id, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	uint Shader::AttachShader(const String& shaderSrc, GLenum shaderType)
	{
		uint shader = glCreateShader(shaderType);
		const char* cstr = shaderSrc.c_str();
		glShaderSource(shader, 1, &cstr, nullptr);
		glCompileShader(shader);

		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			String errorMessage(&error[0]);
			glDeleteShader(shader);
			AB_ERROR(errorMessage);
			return 0;
		}

		glAttachShader(m_Id, shader);
		return shader;
	}

	int Shader::GetUniformLocation(const String& uniformName) const
	{
		int location = 0;
		if (m_UniformLocations.find(uniformName) != m_UniformLocations.end())
		{
			location = m_UniformLocations[uniformName];
		}
		else
		{
			location = glGetUniformLocation(m_Id, uniformName.c_str());
			m_UniformLocations[uniformName] = location;
			if (location == -1)
			{
				AB_WARN("Unable to find uniform variable: " + uniformName + " in shader with ID: " + std::to_string(m_Id));
			}
		}
		return location;
	}

}