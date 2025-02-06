#include <Vector2.h>

namespace Djipi
{
	float& Vector2::operator[](int i)
	{
		return ((&x)[i]);
	}

	const float& Vector2::operator[](int i) const
	{
		return ((&x)[i]);
	}

	Vector2& Vector2::operator *=(float s)
	{
		x *= s; y *= s;
		return (*this);
	}
	
	Vector2& Vector2::operator /=(float s)
	{
		x /= s; y /= s;
		return (*this);
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& v)
	{
		std::cout << "(" << v[0] << ", " << v[1] << ")";
		return os;
	}
}