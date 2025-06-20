#include <core/math/Vector2.h>

namespace Zefir
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

	Vector2& Vector2::operator +=(const Vector2& v)
	{
		x += v.x, y += v.y;
		return (*this);
	}
	Vector2& Vector2::operator -=(const Vector2& v)
	{
		x -= v.x; y -= v.y;
		return (*this);
	}
	
	Vector2& Vector2::operator +=(const b2Vec2& v)
	{
		x += v.x, y += v.y;
		return (*this);
	}

	Vector2& Vector2::operator -=(const b2Vec2& v)
	{
		x -= v.x; y -= v.y;
		return (*this);
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& v)
	{
		std::cout << "(" << v[0] << ", " << v[1] << ")";
		return os;
	}
	
	std::string Vector2::ToString()
	{
		std::ostringstream oss;
		oss << "(" << x << ", " << y << ")";
		return oss.str();
	}
}