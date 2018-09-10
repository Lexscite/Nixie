#ifndef NIXIE_TRANSFORM_H_
#define NIXIE_TRANSFORM_H_

#pragma once

#include "../math/vector3.h"
#include"../math/quaternion.h"


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
		Transform() : parent_(nullptr), position_(Vector3<float>()), rotation_(Quaternion()), scale_(Vector3<float>(1, 1, 1)) {}

		Vector3<float> GetUp() { return Vector3<float>::Up().Rotate(rotation_); }
		Vector3<float> GetDown() { return Vector3<float>::Down().Rotate(rotation_); }
		Vector3<float> GetForward() { return Vector3<float>::Forward().Rotate(rotation_); }
		Vector3<float> GetBackward() { return Vector3<float>::Backward().Rotate(rotation_); }
		Vector3<float> GetRight() { return Vector3<float>::Right().Rotate(rotation_); }
		Vector3<float> GetLeft() { return Vector3<float>::Left().Rotate(rotation_); }

		std::shared_ptr<Transform> GetParent();
		void SetParent(std::shared_ptr<Transform> parent);

		DirectX::SimpleMath::Matrix CalculateWorldMatrix();

		Vector3<float> GetPosition();
		Vector3<float> GetLocalPosition();
		inline void SetPosition(float x, float y, float z) { position_ = Vector3<float>(x, y, z); }
		inline void SetPosition(Vector3<float> v) { position_ = v; }
		inline void Translate(float x, float y, float z) { position_ += Vector3<float>(x, y, z); }
		inline void Translate(Vector3<float> v) { position_ += v; }

		Quaternion GetRotation();
		Quaternion GetLocalRotation();
		inline void SetRotation(float r, float p, float y) { rotation_ = Quaternion(r, p, y, 1.0f); }
		inline void SetRotation(Vector3<float> v) { rotation_ = Quaternion(v.x , v.y, v.z, 1.0f); }
		inline void Rotate(float r, float p, float y) { rotation_ *= Quaternion(r, p, y, 1.0f); }
		inline void Rotate(Vector3<float> v) { rotation_ *= Quaternion(v.x, v.y, v.z, 1.0f); }

		Vector3<float> GetScale();
		Vector3<float> GetLocalScale();
		inline void SetScale(float value) { scale_ = Vector3<float>(value, value, value); }
		inline void SetScale(float x, float y, float z) { scale_ = Vector3<float>(x, y, z); }
		inline void SetScale(Vector3<float> v) { scale_ = v; }
		inline void Scale(float value) { scale_ += value; }
		inline void Scale(float x, float y, float z) { scale_ += Vector3<float>(x, y, z); }
		inline void Scale(Vector3<float> v) { scale_ += v; }

	private:
		std::shared_ptr<Transform> parent_;

		Vector3<float> position_;
		Quaternion rotation_;
		Vector3<float> scale_;
	};
}

#endif