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
		UniformManager(const UniformManager& other);
		~UniformManager();

		UniformManager& operator=(const UniformManager& other);

		const std::vector<UniformInfo>& Uniforms() const;
		std::vector<UniformInfo>& Uniforms();
		int UniformCount() const;

		void AddUniform(Internal::Uniform* uniform, UniformUploadMode mode = UniformUploadMode::Repeat);
		void RemoveUniform(int index) const;
		void RemoveUniform(const String& uniformLocation) const;
		void Clear();

		Internal::Uniform* Get(const String& uniformLocation) const;
		Internal::Uniform* operator[](const String& uniformLocation) const;

		template<typename T>
		Uniform<T>* Get(const String& uniformLocation) const
		{
			return (Uniform<T>*)Get(uniformLocation);
		}

		template<typename T>
		Uniform<T>* operator[](const String& uniformLocation) const
		{
			return Get<T>(uniformLocation);
		}

		template<typename T>
		void AddUniform(const String& uniformLocation, const T& value, UniformUploadMode mode = UniformUploadMode::Repeat)
		{
			AddUniform(new Uniform<T>(uniformLocation, value), mode);
		}

		void UploadAll(Shader* shader) const;

		bool operator==(const UniformManager& other) const;
		bool operator!=(const UniformManager& other) const;

		String ToString() const override;

	};

}