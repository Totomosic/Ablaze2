#include "ShaderProgram.h"
#include "Utils\Filesystem\__Filesystem__.h"

namespace Ablaze
{

	ShaderProgram::ShaderProgram(ShaderType type, const String& source) : Asset(), GLObject(),
		m_Type(type), m_Source(source), m_Compiled(false)
	{
		Create();
	}

	ShaderProgram::ShaderProgram() : Asset(), GLObject(),
		m_Type(ShaderType::Vertex), m_Source(), m_Compiled(false)
	{
		Create();
	}

	ShaderType ShaderProgram::Type() const
	{
		return m_Type;
	}

	const String& ShaderProgram::Source() const
	{
		return m_Source;
	}

	bool ShaderProgram::IsCompiled() const
	{
		return m_Compiled;
	}

	void ShaderProgram::SetType(ShaderType type)
	{
		m_Type = type;
	}

	void ShaderProgram::SetSource(const String& source)
	{
		m_Source = source;
	}

	void ShaderProgram::Compile()
	{
		if (!m_Compiled)
		{
			const char* cstr = m_Source.c_str();
			GL_CALL(glShaderSource(m_Id, 1, &cstr, nullptr));
			GL_CALL(glCompileShader(m_Id));

			int result;
			GL_CALL(glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE)
			{
				int length;
				GL_CALL(glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GL_CALL(glGetShaderInfoLog(m_Id, length, &length, &error[0]));
				String errorMessage(&error[0]);
				AB_ERROR(errorMessage);
			}
			m_Compiled = true;
		}
		else
		{
			// Recompile
		}
	}

	void ShaderProgram::Reload()
	{
	
	}

	void ShaderProgram::Bind() const
	{
	
	}

	void ShaderProgram::Unbind() const
	{
	
	}

	String ShaderProgram::ToString() const
	{
		return Source();
	}

	ShaderProgram* ShaderProgram::FromFile(ShaderType type, const String& filename)
	{
		File f = Filesystem::OpenFile(filename, OpenFlags::Read);
		ShaderProgram* program = new ShaderProgram(type, f.ReadText());
		program->m_AssetType = AssetType::Loaded;
		f.Close();
		return program;
	}

	ShaderProgram* ShaderProgram::FromSource(ShaderType type, const String& source)
	{
		return new ShaderProgram(type, source);
	}

	void ShaderProgram::Create()
	{
		m_Id = GL_CALL(glCreateShader((GLenum)m_Type));
	}

}