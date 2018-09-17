#ifndef NIXIE_TRANSFORM_H_
#define NIXIE_TRANSFORM_H_

#pragma once

#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/matrix.h"


namespace nixie
{
	class GameObject;

	class Transform final
	{
	public:
		Transform(std::shared_ptr<GameObject> game_object);

		Vector3<float> GetUp();
		Vector3<float> GetDown();
		Vector3<float> GetForward();
		Vector3<float> GetBackward();
		Vector3<float> GetRight();
		Vector3<float> GetLeft();

		std::shared_ptr<Transform> GetParent();
		void SetParent(std::shared_ptr<Transform> parent);

		Matrix4x4<float> CalculateWorldMatrix();

		Vector3<float> GetPosition();
		Vector3<float> GetLocalPosition();
		Quaternion<float> GetRotation();
		Quaternion<float> GetLocalRotation();
		Vector3<float> GetScale();
		Vector3<float> GetLocalScale();

		void SetPosition(const float& x, const float& y, const float& z);
		void SetPosition(const Vector3<float>& v);
		void SetRotation(const float& x, const float& y, const float& z);
		void SetRotation(const Vector3<float>& v);
		void SetRotation(const Quaternion<float>& q);
		void SetRotation(const Vector3<float>& v, const float& s);
		void SetRotationByDegrees(const float& x, const float& y, const float& z);
		void SetRotationByDegrees(const Vector3<float> v);
		void SetScale(const float& s);
		void SetScale(const float& x, const float& y, const float& z);
		void SetScale(const Vector3<float>& v);

		void Translate(const float& x, const float& y, const float& z);
		void Translate(const Vector3<float>& v);
		void Rotate(const float& x, const float& y, const float& z);
		void Rotate(const Vector3<float>& v);
		void Rotate(const Quaternion<float> q);
		void RotateByDegrees(const float& x, const float& y, const float& z);
		void RotateByDegrees(const Vector3<float> v);
		void Scale(const float& value);
		void Scale(const float& x, const float& y, const float& z);
		void Scale(const Vector3<float>& v);

	private:
		std::shared_ptr<GameObject> game_object_;
		std::shared_ptr<Transform> parent_;

		Vector3<float> position_;
		Quaternion<float> rotation_;
		Vector3<float> scale_;
	};
}

#endif