#pragma once

#include <Djipi.h>

namespace DjipiApp
{
	class TestVector2
	{
	public:
		Djipi::Vector2 vec1;
		Djipi::Vector2 vec2;

		TestVector2()
		{
			vec1 = Djipi::Vector2(1, 1);
			vec2 = Djipi::Vector2(2, 3);

			TestPrintVectors();
            TestScalarMultDiv();
            TestBasicOperations();
            TestAddSub();
		}

		// Test : print the vec1 and vec2 using component index
		// and << operator overload
		void TestPrintVectors()
		{
            cout << "Print vectors :" << endl;
			cout << "By index :" << endl;
			cout << "vec1 = (" << vec1[0] << ", " << vec1[0] << ")" << endl;
			cout << "vec2 = (" << vec2[0] << ", " << vec2[1] << ")" << endl;
			
			cout << endl << "By operator overload :" << endl;
			cout << "vec 1 = " << vec1 << endl;
			cout << "vec 2 = " << vec2 << endl;
		}

        // Test : scalar mult / div operators
		void TestScalarMultDiv()
		{
            Djipi::Vector2 v1(3.0f, 4.0f);
            v1 *= 2.0f;
            v1 /= 2.0f;
            if (v1.x == 3.0f && v1.y == 4.0f) {
                std::cout << "Test passed: v1" << std::endl;
            }
            else {
                std::cout << "Test failed: v1" << std::endl;
            }

            Djipi::Vector2 v2(1.0f, 2.0f);
            v2 *= 5.0f;
            v2 /= 5.0f;
            if (v2.x == 1.0f && v2.y == 2.0f) {
                std::cout << "Test passed: v2" << std::endl;
            }
            else {
                std::cout << "Test failed: v2" << std::endl;
            }

            Djipi::Vector2 v3(0.0f, 0.0f);
            v3 *= 10.0f;
            v3 /= 10.0f;
            if (v3.x == 0.0f && v3.y == 0.0f) {
                std::cout << "Test passed: v3" << std::endl;
            }
            else {
                std::cout << "Test failed: v3" << std::endl;
            }

            Djipi::Vector2 v4(3.0f, -4.0f);
            v4 *= 0.5f;
            v4 /= 0.5f;
            if (v4.x == 3.0f && v4.y == -4.0f) {
                std::cout << "Test passed: v4" << std::endl;
            }
            else {
                std::cout << "Test failed: v4" << std::endl;
            }
		}

        // Test : basic operations
        void TestBasicOperations()
        {
            Djipi::Vector2 v1(3.0f, 4.0f);

            // Test multiplication par un scalaire
            Djipi::Vector2 result = v1 * 2.0f;
            if (result.x == 6.0f && result.y == 8.0f) {
                std::cout << "Test passed: v1 * 2" << std::endl;
            }
            else {
                std::cout << "Test failed: v1 * 2" << std::endl;
            }

            // Test division par un scalaire
            result = v1 / 2.0f;
            if (result.x == 1.5f && result.y == 2.0f) {
                std::cout << "Test passed: v1 / 2" << std::endl;
            }
            else {
                std::cout << "Test failed: v1 / 2" << std::endl;
            }

            // Test inversion du vecteur (négatif)
            result = -v1;
            if (result.x == -3.0f && result.y == -4.0f) {
                std::cout << "Test passed: -v1" << std::endl;
            }
            else {
                std::cout << "Test failed: -v1" << std::endl;
            }

            // Test magnitude du vecteur
            float magnitude = Magnitude(v1);
            if (std::fabs(magnitude - 5.0f) < 0.001f) {
                std::cout << "Test passed: Magnitude of v1" << std::endl;
            }
            else {
                std::cout << "Test failed: Magnitude of v1" << std::endl;
            }

            // Test normalisation du vecteur
            Djipi::Vector2 normalized = Normalize(v1);
            float normMagnitude = Magnitude(normalized);
            if (std::fabs(normMagnitude - 1.0f) < 0.001f) {
                std::cout << "Test passed: Normalized v1" << std::endl;
            }
            else {
                std::cout << "Test failed: Normalized v1" << std::endl;
            }

        }

        void TestAddSub()
        {
            // Test de l'opérateur += avec des nombres positifs
            Djipi::Vector2 v1(1.0f, 2.0f);
            Djipi::Vector2 v2(3.0f, 4.0f);
            v1 += v2;
            if (v1.x == 4.0f && v1.y == 6.0f)
            {
                std::cout << "Test passed: Operator += (positive numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator += (positive numbers)" << endl;
            }

            // Test de l'opérateur += avec des nombres négatifs
            Djipi::Vector2 v3(-1.0f, -2.0f);
            Djipi::Vector2 v4(-3.0f, -4.0f);
            v3 += v4;
            if (v3.x == -4.0f && v3.y == -6.0f)
            {
                std::cout << "Test passed: Operator += (negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator += (negative numbers)" << endl;
            }

            // Test de l'opérateur += avec un mélange de nombres positifs et négatifs
            Djipi::Vector2 v5(1.0f, -2.0f);
            Djipi::Vector2 v6(-3.0f, 4.0f);
            v5 += v6;
            if (v5.x == -2.0f && v5.y == 2.0f)
            {
                std::cout << "Test passed: Operator += (mixed positive and negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator += (mixed positive and negative numbers)" << endl;
            }

            // Test de l'opérateur -= avec des nombres positifs
            Djipi::Vector2 v7(5.0f, 7.0f);
            Djipi::Vector2 v8(2.0f, 3.0f);
            v7 -= v8;
            if (v7.x == 3.0f && v7.y == 4.0f)
            {
                std::cout << "Test passed: Operator -= (positive numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator -= (positive numbers)" << endl;
            }

            // Test de l'opérateur -= avec des nombres négatifs
            Djipi::Vector2 v9(-5.0f, -7.0f);
            Djipi::Vector2 v10(-2.0f, -3.0f);
            v9 -= v10;
            if (v9.x == -3.0f && v9.y == -4.0f)
            {
                std::cout << "Test passed: Operator -= (negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator -= (negative numbers)" << endl;
            }

            // Test de l'opérateur -= avec un mélange de nombres positifs et négatifs
            Djipi::Vector2 v11(5.0f, -7.0f);
            Djipi::Vector2 v12(-2.0f, 3.0f);
            v11 -= v12;
            if (v11.x == 7.0f && v11.y == -10.0f)
            {
                std::cout << "Test passed: Operator -= (mixed positive and negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator -= (mixed positive and negative numbers)" << endl;
            }

            // Test de l'opérateur + avec des nombres positifs
            Djipi::Vector2 v13(1.0f, 2.0f);
            Djipi::Vector2 v14(3.0f, 4.0f);
            Djipi::Vector2 v15 = v13 + v14;
            if (v15.x == 4.0f && v15.y == 6.0f)
            {
                std::cout << "Test passed: Operator + (positive numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator + (positive numbers)" << endl;
            }

            // Test de l'opérateur + avec des nombres négatifs
            Djipi::Vector2 v16(-1.0f, -2.0f);
            Djipi::Vector2 v17(-3.0f, -4.0f);
            Djipi::Vector2 v18 = v16 + v17;
            if (v18.x == -4.0f && v18.y == -6.0f)
            {
                std::cout << "Test passed: Operator + (negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator + (negative numbers)" << endl;
            }

            // Test de l'opérateur + avec un mélange de nombres positifs et négatifs
            Djipi::Vector2 v19(1.0f, -2.0f);
            Djipi::Vector2 v20(-3.0f, 4.0f);
            Djipi::Vector2 v21 = v19 + v20;
            if (v21.x == -2.0f && v21.y == 2.0f)
            {
                std::cout << "Test passed: Operator + (mixed positive and negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator + (mixed positive and negative numbers)" << endl;
            }

            // Test de l'opérateur - avec des nombres positifs
            Djipi::Vector2 v22(5.0f, 7.0f);
            Djipi::Vector2 v23(2.0f, 3.0f);
            Djipi::Vector2 v24 = v22 - v23;
            if (v24.x == 3.0f && v24.y == 4.0f)
            {
                std::cout << "Test passed: Operator - (positive numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator - (positive numbers)" << endl;
            }

            // Test de l'opérateur - avec des nombres négatifs
            Djipi::Vector2 v25(-5.0f, -7.0f);
            Djipi::Vector2 v26(-2.0f, -3.0f);
            Djipi::Vector2 v27 = v25 - v26;
            if (v27.x == -3.0f && v27.y == -4.0f)
            {
                std::cout << "Test passed: Operator - (negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator - (negative numbers)" << endl;
            }

            // Test de l'opérateur - avec un mélange de nombres positifs et négatifs
            Djipi::Vector2 v28(5.0f, -7.0f);
            Djipi::Vector2 v29(-2.0f, 3.0f);
            Djipi::Vector2 v30 = v28 - v29;
            if (v30.x == 7.0f && v30.y == -10.0f)
            {
                std::cout << "Test passed: Operator - (mixed positive and negative numbers)" << std::endl;
            }
            else
            {
                std::cout << "Failed: Operator - (mixed positive and negative numbers)" << endl;
            }
        }
	};
}