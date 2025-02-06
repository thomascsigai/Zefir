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

        // Test scalar mult / div
		void TestScalarMultDiv()
		{
            std::cout << endl << "Test scalar mult / div :" << endl;
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
	};
}