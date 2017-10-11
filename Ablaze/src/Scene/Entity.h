#pragma once
#include "Common.h"
#include "Structs\__Structs__.h"
#include "Resources\Meshes\__Meshes__.h"

namespace Ablaze
{

	// Base class for all Objects in the game
	class AB_API Entity : public Object
	{
	protected:
		Transform m_Transform;
		Mesh m_Mesh;
		bool m_HasMesh; // m_Mesh will be invalid if this is false

	public:
		Entity(const Transform& transform, const Mesh& mesh, bool addToScene = true);
		Entity(const Transform& transform, bool addToScene = true);
		Entity(const Mesh& mesh, bool addToScene = true);
		Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene = true);
		Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene = true);
		Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene = true);
		Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, bool addToScene = true);
		Entity(const Maths::Vec3& position, const Mesh& mesh, bool addToScene = true);
		Entity(const Maths::Vec3& position, bool addToScene = true);
		Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene = true);
		Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene = true);
		Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene = true);
		Entity(float x, float y, float z, const Maths::Quaternion& rotation, bool addToScene = true);
		Entity(float x, float y, float z, const Mesh& mesh, bool addToScene = true);
		Entity(float x, float y, float z, bool addToScene = true);
		Entity(bool addToScene = true);

		const Transform& GetTransform() const;
		Transform& GetTransform();
		const Mesh& GetMesh() const;
		Mesh& GetMesh();
		bool HasMesh() const;

		const Maths::Vec3& Position() const;
		Maths::Vec3& Position();
		const Maths::Quaternion& Rotation() const;
		Maths::Quaternion& Rotation();
		const Maths::Vec3& Scale() const;
		Maths::Vec3& Scale();

		void SetTransform(const Transform& transform);
		void SetMesh(const Mesh& mesh);
		void DeleteMesh();

		virtual void Update(double elapsedSeconds); // Every update
		virtual void Tick(); // Every second

		String ToString() const override;

	};

}