#ifndef NIXIE_TRANSFORM_H_
#define NIXIE_TRANSFORM_H_

#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/matrix.h"


namespace Nixie
{
	class GameObject;

	class Transform final
	{
	public:
		Transform(std::shared_ptr<GameObject> game_object) : game_object_(game_object), parent_(nullptr), position_(Vector3<float>(0.0f)), rotation_(Quaternion<float>(1, 0, 0, 0)), scale_(Vector3<float>(1.0f)) {}

		Vector3<float> GetUp() { return rotation_.ToMatrix4() * Vector3<float>(0, 1, 0); }
		Vector3<float> GetDown() { return rotation_.ToMatrix4() * Vector3<float>(0, -1, 0); }
		Vector3<float> GetForward() { return rotation_.ToMatrix4() * Vector3<float>(0, 0, -1); }
		Vector3<float> GetBackward() { return rotation_.ToMatrix4() * Vector3<float>(0, 0, 1); }
		Vector3<float> GetRight() { return rotation_.ToMatrix4() * Vector3<float>(1, 0, 0); }
		Vector3<float> GetLeft() { return rotation_.ToMatrix4() * Vector3<float>(-1, 0, 0); }

		std::shared_ptr<Transform> GetParent();
		void SetParent(std::shared_ptr<Transform> parent);

		Matrix4x4<float> CalculateWorldMatrix();

		Vector3<float> GetPosition();
		Vector3<float> GetLocalPosition();
		inline void SetPosition(const float& x, const float& y, const float& z) { position_ = Vector3<float>(x, y, z); }
		inline void SetPosition(const Vector3<float>& v) { position_ = v; }
		inline void Translate(const float& x, const float& y, const float& z) { position_ += Vector3<float>(x, y, z); }
		inline void Translate(const Vector3<float>& v) { position_ += v; }

		Quaternion<float> GetRotation();
		Quaternion<float> GetLocalRotation();
		inline void SetRotation(const float& x, const float& y, const float& z) { rotation_ = Quaternion<float>::FromEulerAngles(x, y, z); }
		inline void SetRotation(const Vector3<float>& v) { rotation_ = Quaternion<float>::FromEulerAngles(v); }
		inline void SetRotation(const Quaternion<float>& q) { rotation_ = q; }
		inline void SetRotation(const Vector3<float>& v, const float& s) { rotation_ = Quaternion<float>(v.x, v.y, v.z, s); }
		inline void Rotate(const float& x, const float& y, const float& z) { rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(x, y, z); }
		inline void Rotate(const Vector3<float>& v) { rotation_ = rotation_ * Quaternion<float>::FromEulerAngles(v); }
		inline void Rotate(const Quaternion<float> q) { rotation_ = rotation_ * q; }

		Vector3<float> GetScale();
		Vector3<float> GetLocalScale();
		inline void SetScale(const float& s) { scale_ = Vector3<float>(s); }
		inline void SetScale(const float& x, const float& y, const float& z) { scale_ = Vector3<float>(x, y, z); }
		inline void SetScale(const Vector3<float>& v) { scale_ = v; }
		inline void Scale(const float& value) { scale_ += value; }
		inline void Scale(const float& x, const float& y, const float& z) { scale_ += Vector3<float>(x, y, z); }
		inline void Scale(const Vector3<float>& v) { scale_ += v; }

	private:
		std::shared_ptr<GameObject> game_object_;
		std::shared_ptr<Transform> parent_;

		Vector3<float> position_;
		Quaternion<float> rotation_;
		Vector3<float> scale_;
	};
}

#endif