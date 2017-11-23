#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class AssetType
	{
		OBJModel,
		Cuboid,
		Sphere,
		Grid,
		Rectangle,
		Ellipse,

		Shader,
		ShaderProgram,

		Texture,
		Texture2D,
		Font
	};

	enum class LoadType
	{
		Loaded,
		Generated
	};

	class AB_API AssetLoadInfo : public Object
	{
	private:
		AssetType m_AssetType;
		LoadType m_LoadType;
		std::unordered_map<String, String> m_Identifiers;

	public:
		AssetLoadInfo();

		const AssetType Type() const;
		AssetType& Type();
		const LoadType LoadMethod() const;
		LoadType& LoadMethod();
		const std::unordered_map<String, String>& Identifiers() const;
		std::unordered_map<String, String>& Identifiers();

		void AddIdentifier(const String& name, const String& identifier);
		const String& GetIdentifier(const String& name) const;
		String& GetIdentifier(const String& name);

		template<typename T>
		void AddIdentifier(const String& name, T identifier)
		{
			AddIdentifier(name, std::to_string(identifier));
		}

		template<>
		void AddIdentifier(const String& name, const char* string)
		{
			AddIdentifier(name, String(string));
		}

		bool operator==(const AssetLoadInfo& other) const;
		bool operator!=(const AssetLoadInfo& other) const;

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

	};

}

namespace std
{

	template<>
	struct hash<Ablaze::AssetLoadInfo>
	{
		std::size_t operator()(const Ablaze::AssetLoadInfo& info) const
		{
			return ((int)info.Type() << 8) | ((int)info.LoadMethod() << 4) | (info.Identifiers().size());
		}
	};

}