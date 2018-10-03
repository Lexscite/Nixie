#ifndef VOODOO_TRANSFORM_H_
#define VOODOO_TRANSFORM_H_

#include "math.h"
#include "vector.h"
#include "quaternion.h"
#include "matrix.h"

namespace voodoo
{
	class GameObject;

	class Transform final
	{
	public:
		Transform(std::shared_ptr<GameObject> game_object);

		std::shared_ptr<Transform> GetParent();
		void SetParent(std::shared_ptr<Transform> parent);

		Matrix4x4f CalculateWorldMatrix();

		Vector3f GetUp();
		Vector3f GetDown();
		Vector3f GetForward();
		Vector3f GetBackward();
		Vector3f GetRight();
		Vector3f GetLeft();

		Vector3f GetPosition();
		Vector3f GetLocalPosition();
		Quaternion GetRotation();
		Quaternion GetLocalRotation();
		Vector3f GetScale();
		Vector3f GetLocalScale();

		void SetPosition(const float& x, const float& y, const float& z);
		void SetPosition(const Vector3f& v);
		void SetRotation(const float& x, const float& y, const float& z);
		void SetRotation(const Vector3f& v);
		void SetRotation(const Quaternion& q);
		void SetRotation(const Vector3f& v, const float& s);
		void SetRotationByDegrees(const float& x, const float& y, const float& z);
		void SetRotationByDegrees(const Vector3f v);
		void SetScale(const float& s);
		void SetScale(const float& x, const float& y, const float& z);
		void SetScale(const Vector3f& v);

		void Translate(const float& x, const float& y, const float& z);
		void Translate(const Vector3f& v);
		void Rotate(const float& x, const float& y, const float& z);
		void Rotate(const Vector3f& v);
		void Rotate(const Quaternion q);
		void RotateByDegrees(const float& x, const float& y, const float& z);
		void RotateByDegrees(const Vector3f v);
		void Scale(const float& value);
		void Scale(const float& x, const float& y, const float& z);
		void Scale(const Vector3f& v);

	private:
		std::shared_ptr<GameObject> game_object_;
		std::shared_ptr<Transform> parent_;

		Vector3f position_;
		Quaternion rotation_;
		Vector3f scale_;
	};
}

#endif