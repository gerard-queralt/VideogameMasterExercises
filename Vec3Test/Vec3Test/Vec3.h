#pragma once

#include <iostream>

template <class T>
class Vec3
{
public:
	T x;
	T y;
	T z;

public:
	Vec3() {}
	~Vec3() {}
	Vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3(const Vec3& original) {
		this->x = original.x;
		this->y = original.y;
		this->z = original.z;
	}

	Vec3<T> operator+ (const Vec3<T>& adding) {
		return Vec3<T>(x + adding.x, y + adding.y, z + adding.z);
	}

	float magnitude() const {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	Vec3<float> Normalize() {
		float magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		return Vec3<float>(x / magnitude, y / magnitude, z / magnitude);
	}
	float distance_to(const Vec3& to) {
		T diffX = to.x - x;
		T diffY = to.y - y;
		T diffZ = to.z - z;
		return sqrt(pow(diffX, 2) + pow(diffY, 2) + pow(diffZ, 2));
	}
	float dot_product(const Vec3& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vec3<T> cross_product(const Vec3& rhs) {
		T cX = y * rhs.z - z * rhs.y;
		T cY = z * rhs.x - x * rhs.z;
		T cZ = x * rhs.y - y * rhs.x;
		return Vec3<T>(cX, cY, cZ);
	}

	float angle_between(const Vec3& to) {
		float dot = dot_product(to);
		float mFrom = magnitude();
		float mTo = to.magnitude();
		return acos(dot / (mFrom * mTo));
	}

	void print() {
		std::cout << "x: " << x << "; y: " << y << "; z: " << z << "\n";
	}
};
