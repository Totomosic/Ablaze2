#pragma once
#include "Common.h"
#include "Structs\__Structs__.h"
#include "Resources\Meshes\__Meshes__.h"

namespace Ablaze
{

	class Layer;

	// Base class for all Objects in the game
	class AB_API Entity : public Object
	{
	protected:
		Transform m_Transform;
		Mesh m_Mesh;
		bool m_HasMesh; // m_Mesh will be invalid if this is false
		Layer* m_Layer;
		bool m_IsTagged;

	public:
		Entity(const Transform& transform, const Mesh& mesh);
		Entity(const Transform& transform);
		Entity(const Mesh& mesh);
		Entity();

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

		Maths::Vec3 Forward() const;
		Maths::Vec3 Right() const;
		Maths::Vec3 Up() const;

		void SetTransform(const Transform& transform);
		void SetMesh(const Mesh& mesh);
		void DeleteMesh();
		void SetName(const String& name);

		void Rotate(float angle, const Maths::Vec3& axis, Space space = Space::World, Angle angleType = Angle::Degrees);

		virtual void Update(double elapsedSeconds); // Every update
		virtual void Tick(); // Every second

		String ToString() const override;

		friend class Layer;

	private:
		void SetLayer(Layer* layer);

	};

}