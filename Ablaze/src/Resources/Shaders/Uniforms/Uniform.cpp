#include "Uniform.h"

namespace Ablaze
{
	namespace Internal
	{

		Uniform::Uniform(const String& uniform) : Object(),
			m_UniformLocation(uniform)
		{

		}

		const String& Uniform::UniformLocation() const
		{
			return m_UniformLocation;
		}

		String& Uniform::UniformLocation()
		{
			return m_UniformLocation;
		}

	}
}