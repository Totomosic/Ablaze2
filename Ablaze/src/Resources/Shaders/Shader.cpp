#include "Shader.h"
#include "Scene\Systems\__Systems__.h"
#include "Resources\ResourceManager.h"

namespace Ablaze
{

	std::vector<Shader*> Shader::s_Shaders = std::vector<Shader*>();

	Shader::Shader(const String& vertexSrc, const String& fragmentSrc) : GLObject(), Asset(),
		m_UniformLocations()
	{
		Create();
		BuildProgram(vertexSrc, fragmentSrc);
		s_Shaders.push_back(this);
	}

	Shader::Shader(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc) : GLObject(), Asset(),
		m_UniformLocations()
	{
		Create();
		BuildProgram(vertexSrc, geometrySrc, fragmentSrc);
		s_Shaders.push_back(this);
	}

	Shader::~Shader()
	{
		GL_CALL(glDeleteProgram(m_Id));
	}

	void Shader::Bind() const
	{
		GL_CALL(glUseProgram(m_Id));
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

	void Shader::SetUniform(const String& uniformName, int value) const
	{
		Bind();
		GL_CALL(glUniform1i(GetUniformLocation(uniformName), value));
	}

	void Shader::SetUniform(const String& uniformName, uint value) const
	{
		SetUniform(uniformName, (int)value);
	}

	void Shader::SetUniform(const String& uniformName, float value) const
	{
		Bind();
		GL_CALL(glUniform1f(GetUniformLocation(uniformName), value));
	}

	void Shader::SetUniform(const String& uniformName, bool value) const
	{
		SetUniform(uniformName, (int)value);
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector2f& value) const
	{
		Bind();
		GL_CALL(glUniform2f(GetUniformLocation(uniformName), value.x, value.y));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector3f& value) const
	{
		Bind();
		GL_CALL(glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector4f& value) const
	{
		Bind();
		GL_CALL(glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector2i& value) const
	{
		Bind();
		GL_CALL(glUniform2i(GetUniformLocation(uniformName), value.x, value.y));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector3i& value) const
	{
		Bind();
		GL_CALL(glUniform3i(GetUniformLocation(uniformName), value.x, value.y, value.z));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Vector4i& value) const
	{
		Bind();
		GL_CALL(glUniform4i(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Plane& value) const
	{
		Bind();
		GL_CALL(glUniform4f(GetUniformLocation(uniformName), value.normal.x, value.normal.y, value.normal.z, value.height));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Ray& value) const
	{
		Bind();
		GL_CALL(glUniform3f(GetUniformLocation(uniformName), value.Direction.x, value.Direction.y, value.Direction.z));
	}

	void Shader::SetUniform(const String& uniformName, const Maths::Matrix4d& value) const
	{
		Bind();
		float values[16];
		for (int i = 0; i < 16; i++)
		{
			values[i] = (float)value.values[i];
		}
		GL_CALL(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, values));
	}

	void Shader::SetUniform(const String& uniformName, const Color& value) const
	{
		Bind();
		GL_CALL(glUniform4f(GetUniformLocation(uniformName), value.r, value.g, value.b, value.a));
	}

	String Shader::ToString() const
	{
		return "Shader";
	}

	Shader* Shader::FromFile(const Filepath& vertexPath, const Filepath& fragmentPath)
	{
		File vertexFile = Filesystem::OpenFile(vertexPath, OpenFlags::Read);
		File fragmentFile = Filesystem::OpenFile(fragmentPath, OpenFlags::Read);		
		Shader* shader = new Shader(PreprocessShader(vertexFile.ReadText(), vertexPath), PreprocessShader(fragmentFile.ReadText(), fragmentPath));
		vertexFile.Close();
		fragmentFile.Close();
		return shader;
	}

	Shader* Shader::FromFile(const Filepath& vertexPath, const Filepath& geometryPath, const Filepath& fragmentPath)
	{
		File vertexFile = Filesystem::OpenFile(vertexPath, OpenFlags::Read);
		File geometryFile = Filesystem::OpenFile(geometryPath, OpenFlags::Read);
		File fragmentFile = Filesystem::OpenFile(fragmentPath, OpenFlags::Read);
		Shader* shader = new Shader(PreprocessShader(vertexFile.ReadText(), vertexPath), PreprocessShader(geometryFile.ReadText(), geometryPath), PreprocessShader(fragmentFile.ReadText(), fragmentPath));
		vertexFile.Close();
		geometryFile.Close();
		fragmentFile.Close();
		return shader;
	}

	Shader* Shader::FromFile(const Filepath& shaderFile)
	{
		const int NONE_SHADER_TYPE = -1;
		const int VERTEX_SHADER_TYPE = 0;
		const int FRAGMENT_SHADER_TYPE = 1;
		const int GEOMETRY_SHADER_TYPE = 2;

		std::stringstream ss[3];
		int currentType = NONE_SHADER_TYPE;
		bool isGeometryShader = false;

		File f = Filesystem::OpenFile(shaderFile, OpenFlags::Read);
		String line;
		while (f.ReadTextLine(&line))
		{
			if (line.find("#shader") != String::npos)
			{
				if (line.find("vertex") != String::npos)
				{
					currentType = VERTEX_SHADER_TYPE;
				}
				else if (line.find("fragment") != String::npos)
				{
					currentType = FRAGMENT_SHADER_TYPE;
				}
				else if (line.find("geometry") != String::npos)
				{
					currentType = GEOMETRY_SHADER_TYPE;
					isGeometryShader = true;
				}
			}
			else
			{
				ss[currentType] << line << '\n';
			}
		}
		if (!isGeometryShader)
		{
			Shader* shader = new Shader(PreprocessShader(ss[VERTEX_SHADER_TYPE].str(), shaderFile), PreprocessShader(ss[FRAGMENT_SHADER_TYPE].str(), shaderFile));
			return shader;
		}
		// Use Geometry Shader
		Shader* shader = new Shader(PreprocessShader(ss[VERTEX_SHADER_TYPE].str(), shaderFile), PreprocessShader(ss[GEOMETRY_SHADER_TYPE].str(), shaderFile), PreprocessShader(ss[FRAGMENT_SHADER_TYPE].str(), shaderFile));
		return shader;
	}

	Shader* Shader::FromSource(const String& vertexSrc, const String& fragmentSrc)
	{
		return new Shader(PreprocessShader(vertexSrc, ""), PreprocessShader(fragmentSrc, ""));
	}

	Shader* Shader::FromSource(const String& vertexSrc, const String& geometrySource, const String& fragmentSrc)
	{
		return new Shader(PreprocessShader(vertexSrc, ""), PreprocessShader(geometrySource, ""), PreprocessShader(fragmentSrc, ""));
	}

	const std::vector<Shader*>& Shader::GetAll()
	{
		return s_Shaders;
	}

	void Shader::Create()
	{
		m_Id = GL_CALL(glCreateProgram());
	}

	void Shader::BuildProgram(const String& vertexSrc, const String& fragmentSrc)
	{
		uint vertex = AttachShader(vertexSrc, GL_VERTEX_SHADER);
		uint fragment = AttachShader(fragmentSrc, GL_FRAGMENT_SHADER);
		GL_CALL(glLinkProgram(m_Id));

		GL_CALL(glDetachShader(m_Id, vertex));
		GL_CALL(glDetachShader(m_Id, fragment));
		GL_CALL(glDeleteShader(vertex));
		GL_CALL(glDeleteShader(fragment));
	}

	void Shader::BuildProgram(const String& vertexSrc, const String& geometrySrc, const String& fragmentSrc)
	{
		uint vertex = AttachShader(vertexSrc, GL_VERTEX_SHADER);
		uint geometry = AttachShader(geometrySrc, GL_GEOMETRY_SHADER);
		uint fragment = AttachShader(fragmentSrc, GL_FRAGMENT_SHADER);
		GL_CALL(glLinkProgram(m_Id));

		GL_CALL(glDetachShader(m_Id, vertex));
		GL_CALL(glDetachShader(m_Id, fragment));
		GL_CALL(glDeleteShader(vertex));
		GL_CALL(glDeleteShader(fragment));
	}

	uint Shader::AttachShader(const String& shaderSrc, GLenum shaderType)
	{
		uint shader = GL_CALL(glCreateShader(shaderType));
		const char* cstr = shaderSrc.c_str();
		GL_CALL(glShaderSource(shader, 1, &cstr, nullptr));
		GL_CALL(glCompileShader(shader));

		int result;
		GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GL_CALL(glGetShaderInfoLog(shader, length, &length, &error[0]));
			String errorMessage(&error[0]);
			GL_CALL(glDeleteShader(shader));
			AB_ERROR(errorMessage);
			return 0;
		}

		GL_CALL(glAttachShader(m_Id, shader));
		return shader;
	}

	int Shader::GetUniformLocation(const String& uniformName) const
	{
		int location = -1;
		if (m_UniformLocations.find(uniformName) != m_UniformLocations.end())
		{
			location = m_UniformLocations[uniformName];
		}
		else
		{
			location = GL_CALL(glGetUniformLocation(m_Id, uniformName.c_str()));
			m_UniformLocations[uniformName] = location;
			if (location == -1)
			{
				AB_WARN("Unable to find uniform variable: " + uniformName + " in shader with ID: " + std::to_string(m_Id));
			}
		}
		return location;
	}

	String Shader::PreprocessShader(const String& shaderSource, const Filepath& thisFilename)
	{
		String INCLUDE_DIRECTIVE = "#include";

		std::vector<String> lines = SplitString(shaderSource, "\n");
		std::stringstream ss;
		for (String line : lines)
		{
			if (strstr(line.c_str(), INCLUDE_DIRECTIVE.c_str()))
			{
				int beginIndex = line.find_first_of('\"');
				int endIndex = line.find_last_of('\"');
				String filename = line.substr(beginIndex + 1, endIndex - beginIndex - 1);				
				if (!Filesystem::FileExists(filename))
				{
					int begin = thisFilename.Path().find_last_of('/');
					filename = thisFilename.Path().substr(0, begin) + "/" + filename;
				}
				String data = PreprocessShader(Filesystem::OpenFile(filename).ReadText(), filename);
				ss << data << '\n';
			}
			else
			{
				ss << line << '\n';
			}
		}
		return ss.str();
	}

}