#include "UniformManager.h"

namespace Ablaze
{

	UniformManager::UniformManager() : Object()
	{
	
	}

	UniformManager::UniformManager(const UniformManager& other)
	{
		for (const auto& uniform : other.m_Uniforms)
		{
			AddUniform(uniform.uniform->Clone(), uniform.mode);
		}
	}

	UniformManager::~UniformManager()
	{
		for (UniformInfo& info : m_Uniforms)
		{
			delete info.uniform;
		}
	}

	UniformManager& UniformManager::operator=(const UniformManager& other)
	{
		for (int i = m_Uniforms.size() - 1; i >= 0; i--)
		{
			UniformInfo& info = m_Uniforms[i];
			delete info.uniform;
			m_Uniforms.erase(m_Uniforms.begin() + i);
		}
		for (const auto& uniform : other.m_Uniforms)
		{
			AddUniform(uniform.uniform->Clone(), uniform.mode);
		}
		return *this;
	}

	const std::vector<UniformInfo>& UniformManager::Uniforms() const
	{
		return m_Uniforms;
	}

	std::vector<UniformInfo>& UniformManager::Uniforms()
	{
		return m_Uniforms;
	}

	int UniformManager::UniformCount() const
	{
		return m_Uniforms.size();
	}

	void UniformManager::AddUniform(Internal::Uniform* uniform, UniformUploadMode mode)
	{
		m_Uniforms.push_back({ uniform, mode });
	}

	void UniformManager::RemoveUniform(int index) const
	{
		Internal::Uniform* ptr = m_Uniforms[index].uniform;
		m_Uniforms.erase(m_Uniforms.begin() + index);
		delete ptr;
	}

	void UniformManager::RemoveUniform(const String& uniformLocation) const
	{
		for (int i = 0; i < UniformCount(); i++)
		{
			if (m_Uniforms[i].uniform->UniformLocation() == uniformLocation)
			{
				RemoveUniform(i);
				return;
			}
		}
		AB_WARN("Unable to find uniform with UniformLocation: " + uniformLocation);
	}

	Internal::Uniform* UniformManager::Get(const String& uniformLocation) const
	{
		for (int i = 0; i < UniformCount(); i++)
		{
			if (m_Uniforms[i].uniform->UniformLocation() == uniformLocation)
			{
				return m_Uniforms[i].uniform;
			}
		}
		AB_WARN("Unable to find uniform with UniformLocation: " + uniformLocation);
		return nullptr;
	}

	Internal::Uniform* UniformManager::operator[](const String& uniformLocation) const
	{
		return Get(uniformLocation);
	}

	void UniformManager::UploadAll(Shader* shader) const
	{
		std::vector<int> remove;
		int count = 0;
		for (UniformInfo& info : m_Uniforms)
		{
			info.uniform->Upload(shader);
			if (info.mode == UniformUploadMode::Once)
			{
				remove.push_back(count);
			}
			count++;
		}
		for (int i = remove.size() - 1; i >= 0; i--)
		{
			RemoveUniform(i);
		}
	}

	bool UniformManager::operator==(const UniformManager& other) const
	{
		if (m_Uniforms.size() != other.m_Uniforms.size())
		{
			return false;
		}
		for (int i = 0; i < m_Uniforms.size(); i++)
		{
			if ((*m_Uniforms[i].uniform) != (*other.m_Uniforms[i].uniform))
			{
				return false;
			}
		}
		return true;
	}

	bool UniformManager::operator!=(const UniformManager& other) const
	{
		return !(*this == other);
	}

	String UniformManager::ToString() const
	{
		return "UniformManager";
	}

}