#pragma once
#include "Common.h"
#include "Resources\Resource.h"
#include "Resources\Shaders\Shader.h"

namespace Ablaze
{

	namespace Internal
	{

		class AB_API Uniform : public Object
		{
		protected:
			String m_UniformLocation;

		public:
			Uniform(const String& uniform);
			virtual void Upload(const Resource<Shader>& shader) const = 0;

			const String& UniformLocation() const;
			String& UniformLocation();

		};

	}

	template<typename T>
	class AB_API Uniform : public Internal::Uniform
	{
	private:
		T m_Value;

	public:
		Uniform(const String& uniform, const T& value) : Internal::Uniform(uniform),
			m_Value(value)
		{
		
		}

		const T& Value() const { return m_Value; }
		T& Value() { return m_Value; }

		void Upload(const Resource<Shader>& shader) const override
		{
			shader->Bind();
			shader->SetUniform<T>(m_UniformLocation, m_Value);
			shader->Unbind();
		}

		String ToString() const override
		{
			return "Uniform";
		}

	};

}