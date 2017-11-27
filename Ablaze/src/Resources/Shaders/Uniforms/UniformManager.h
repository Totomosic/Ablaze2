#pragma once
#include "Uniform.h"

namespace Ablaze
{

	enum class UniformUploadMode
	{
		Repeat,
		Once
	};

	struct AB_API UniformInfo
	{
	public:
		Internal::Uniform* uniform;
		UniformUploadMode mode;
	};

	class AB_API UniformManager : public Object
	{
	private:
		mutable std::vector<UniformInfo> m_Uniforms;

	public:
		UniformManager();
		~UniformManager();

		const std::vector<UniformInfo>& Uniforms() const;
		std::vector<UniformInfo>& Uniforms();
		int UniformCount() const;

		void AddUniform(Internal::Uniform* uniform, UniformUploadMode mode = UniformUploadMode::Repeat);
		void RemoveUniform(int index) const;
		void RemoveUniform(const String& uniformLocation) const;

		Internal::Uniform* Get(const String& uniformLocation) const;
		Internal::Uniform* operator[](const String& uniformLocation) const;

		template<typename T>
		void AddUniform(const String& uniformLocation, const T& value)
		{
			AddUniform(new Uniform<T>(uniformLocation, value));
		}

		void UploadAll(const Resource<Shader>& shader) const;

		String ToString() const override;

	};

}