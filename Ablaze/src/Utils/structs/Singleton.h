#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"

namespace Ablaze
{

	template<typename T>
	class AB_API Singleton
	{
	protected:
		Singleton() {}
		~Singleton() {}

	public:
		Singleton(const T& other) = delete;
		Singleton(const T&& other) = delete;

		Singleton& operator=(const Singleton& other) = delete;

	public:
		static T& Instance()
		{
			static T instance;
			return instance;
		}

	};

}