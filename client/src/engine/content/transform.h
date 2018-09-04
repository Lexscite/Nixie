#ifndef NIXIE_TRANSFORM_H_
#define NIXIE_TRANSFORM_H_

#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"


namespace DirectX
{
	namespace SimpleMath
	{
		struct Matrix;
	}
}

namespace Nixie
{
	class Transform final
	{
	public:
		Transform() : parent_(nullptr), position_(Vector3()), rotation_(Quaternion()), scale_(Vector3(1)) {}

		Vector3 GetUp() { return Vector3::Up().Rotate(rotation_); }
		Vector3 GetDown() { return Vector3::Down().Rotate(rotation_); }
		Vector3 GetLeft() { return Vector3::Left().Rotate(rotation_); }
		Vector3 GetRight() { return Vector3::Right().Rotate(rotation_); }
		Vector3 GetForward() { return Vector3::Forward().Rotate(rotation_); }
		Vector3 GetBackward() { return Vector3::Backward().Rotate(rotation_); }

		std::shared_ptr<Transform> GetParent();
		void SetParent(std::shared_ptr<Transform> parent);

		DirectX::SimpleMath::Matrix CalculateWorldMatrix();

		Vector3 GetPosition();
		Vector3 GetLocalPosition();
		inline void SetPosition(float x, float y, float z) { position_ = Vector3(x, y, z); }
		inline void SetPosition(Vector3 v) { position_ = v; }
		inline void Translate(float x, float y, float z) { position_ += Vector3(x, y, z); }
		inline void Translate(Vector3 v) { position_ += v; }

		Quaternion GetRotation();
		Quaternion GetLocalRotation();
		inline void SetRotation(float r, float p, float y) { rotation_ = Quaternion(r, p, y); }
		inline void SetRotation(Vector3 v) { rotation_ = Quaternion(v); }
		inline void Rotate(float r, float p, float y) { rotation_ *= Quaternion(r, p, y); }
		inline void Rotate(Vector3 v) { rotation_ *= Quaternion(v); }

		Vector3 GetScale();
		Vector3 GetLocalScale();
		inline void SetScale(float value) { scale_ = Vector3(value); }
		inline void SetScale(float x, float y, float z) { scale_ = Vector3(x, y, z); }
		inline void SetScale(Vector3 v) { scale_ = v; }
		inline void Scale(float value) { scale_ += Vector3(value); }
		inline void Scale(float x, float y, float z) { scale_ += Vector3(x, y, z); }
		inline void Scale(Vector3 v) { scale_ += v; }

	private:
		std::shared_ptr<Transform> parent_;

		Vector3 position_;
		Quaternion rotation_;
		Vector3 scale_;
	};
}

#endif