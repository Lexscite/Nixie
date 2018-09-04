#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../graphics/d3d.h"

namespace Nixie
{
	class Transform final
	{
	public:
		Transform() : parent(nullptr), position(Vector3()), rotation(Quaternion()), scale(Vector3(1)) {}

		Vector3 GetUp() { return Vector3::Up().Rotate(rotation); }
		Vector3 GetDown() { return Vector3::Down().Rotate(rotation); }
		Vector3 GetLeft() { return Vector3::Left().Rotate(rotation); }
		Vector3 GetRight() { return Vector3::Right().Rotate(rotation); }
		Vector3 GetForward() { return Vector3::Forward().Rotate(rotation); }
		Vector3 GetBackward() { return Vector3::Backward().Rotate(rotation); }

		Transform* GetParent();
		void SetParent(Transform* parent);

		DirectX::SimpleMath::Matrix CalculateWorldMatrix();

		// Position

		Vector3 GetPosition();
		Vector3 GetLocalPosition();

		inline void SetPosition(float x, float y, float z) { position = Vector3(x, y, z); }
		inline void SetPosition(Vector3 v) { position = v; }

		inline void Translate(float x, float y, float z) { position += Vector3(x, y, z); }
		inline void Translate(Vector3 v) { position += v; }

		// Rotation

		Quaternion GetRotation();
		Quaternion GetLocalRotation();

		inline void SetRotation(float r, float p, float y) { rotation = Quaternion(r, p, y); }
		inline void SetRotation(Vector3 v) { rotation = Quaternion(v); }

		inline void Rotate(float r, float p, float y) { rotation *= Quaternion(r, p, y); }
		inline void Rotate(Vector3 v) { rotation *= Quaternion(v); }

		// Scale

		Vector3 GetScale();
		Vector3 GetLocalScale();

		inline void SetScale(float value) { scale = Vector3(value); }
		inline void SetScale(float x, float y, float z) { scale = Vector3(x, y, z); }
		inline void SetScale(Vector3 v) { scale = v; }

		inline void Scale(float value) { scale += Vector3(value); }
		inline void Scale(float x, float y, float z) { scale += Vector3(x, y, z); }
		inline void Scale(Vector3 v) { scale += v; }

	private:
		Transform* parent;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};
}

#endif