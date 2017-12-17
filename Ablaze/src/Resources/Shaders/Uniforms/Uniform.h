#pragma once
#include "Common.h"
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
			virtual void Upload(Shader* shader) const = 0;

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

		void Upload(Shader* shader) const override
		{
			shader->SetUniform(m_UniformLocation, m_Value);
		}

		String ToString() const override
		{
			return "Uniform";
		}

	};

}