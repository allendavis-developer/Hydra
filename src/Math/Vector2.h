#pragma once
#include <cmath>

namespace Hydra {
    template<typename T>
    struct Vector2
    {
        T X, Y;

        Vector2()
            : X(0), Y(0)
        {

        }

        Vector2(T x, T y)
            : X(x), Y(y)
        {

        }

        // Math operators
        Vector2<T> operator*(Vector2<T>& other)
        {
            return Vector2(X * other.X, Y * other.Y);
        }

        void operator+=(Vector2<T> other)
        {
            X += other.X;
            Y += other.Y;
        }

        Vector2<T> operator*(T scalar)
        {
            return Vector2(X * scalar, Y * scalar);
        }

        Vector2<T> operator-(Vector2<T>& other)
        {
            return Vector2(X - other.X, Y - other.Y);
        }

        Vector2<T> operator+(Vector2<T>& other)
        {
            return Vector2(X + other.X, Y + other.Y);
        }

        // Function to normalize the vector
        void Normalize()
        {
            T magnitude = std::sqrt(X * X + Y * Y);
            if (magnitude != 0)
            {
                X /= magnitude;
                Y /= magnitude;
            }
        }
    };
}
