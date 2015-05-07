//
// Created by Joshua Bradt on 4/28/15.
//

#include "catch.hpp"
#include "Vector3D.h"

SCENARIO("Vector3D class is working", "[vector3d]")
{
    GIVEN("A vector")
    {
        double x {3};
        double y {4};
        double z {5};

        Vector3D vec {x, y, z};

        REQUIRE(vec.x == x);
        REQUIRE(vec.y == y);
        REQUIRE(vec.z == z);

        WHEN("the vector is multiplied by a constant")
        {
            double scalar {5.387};
            Vector3D scaled = vec * scalar;

            THEN("the components are scaled")
            {
                REQUIRE(scaled.x == x * scalar);
                REQUIRE(scaled.y == y * scalar);
                REQUIRE(scaled.z == z * scalar);
            }
        }

        WHEN("the vector is divided by a constant") {
            double scalar{5.387};
            Vector3D scaled = vec / scalar;

            THEN("the components are scaled")
            {
                REQUIRE(scaled.x == x / scalar);
                REQUIRE(scaled.y == y / scalar);
                REQUIRE(scaled.z == z / scalar);
            }
        }

        WHEN("the norm is calculated")
        {
            double norm = vec.norm();

            THEN("the result is the vector's magnitude")
            {
                double expected = sqrt(x*x + y*y + z*z);
                REQUIRE(norm == expected);
            }
        }

    }

    GIVEN("two unequal vectors")
    {
        double x1 {3};
        double y1 {4};
        double z1 {5};
        double x2 {6};
        double y2 {7};
        double z2 {8};

        Vector3D vec1 {x1, y1, z1};
        Vector3D vec2 {x2, y2, z2};

        REQUIRE(vec1.x == x1);
        REQUIRE(vec1.y == y1);
        REQUIRE(vec1.z == z1);
        REQUIRE(vec2.x == x2);
        REQUIRE(vec2.y == y2);
        REQUIRE(vec2.z == z2);

        WHEN("they are added")
        {
            Vector3D sum = vec1 + vec2;

            THEN("the components are added")
            {
                REQUIRE(sum.x == x1 + x2);
                REQUIRE(sum.y == y1 + y2);
                REQUIRE(sum.z == z1 + z2);
            }
        }

        WHEN("they are subtracted")
        {
            Vector3D diff = vec1 - vec2;

            THEN("the components are subtracted")
            {
                REQUIRE(diff.x == x1 - x2);
                REQUIRE(diff.y == y1 - y2);
                REQUIRE(diff.z == z1 - z2);
            }
        }

        WHEN("they are assignment-added")
        {
            Vector3D sum = vec1 + vec2;
            vec1 += vec2;

            THEN("the one assigned to equals the sum")
            {
                REQUIRE(vec1 == sum);
            }
        }

        WHEN("they are assignment-subtracted")
        {
            Vector3D diff = vec1 - vec2;
            vec1 -= vec2;

            THEN("the one assigned to equals the difference")
            {
                REQUIRE(vec1 == diff);
            }
        }

        WHEN("they are dotted together")
        {
            double dot = vec1.dot(vec2);

            THEN("the result is the dot product")
            {
                double expect = x1*x2 + y1*y2 + z1*z2;
                REQUIRE(dot == expect);
            }
        }

        WHEN("they are crossed")
        {
            Vector3D cross = vec1.cross(vec2);

            THEN("the result is the cross product")
            {
                REQUIRE(cross.x == y1*z2 - z1*y2);
                REQUIRE(cross.y == z1*x2 - x1*z2);
                REQUIRE(cross.z == x1*y2 - y1*x2);
            }
        }

        WHEN("they are tested for equality")
        {
            THEN("they are not found to be equal")
            {
                REQUIRE_FALSE(vec1 == vec2);
            }
        }
    }
}

SCENARIO("A Vector3D needs to be constructed from a std::vector")
{
    GIVEN("A std::vector")
    {
        std::vector<double> svec {1, 2, 3};

        WHEN("the Vector3D is constructed with this std::vector")
        {
            Vector3D vec {svec};

            THEN("it is constructed correctly")
            {
                REQUIRE(vec.x == svec[0]);
                REQUIRE(vec.y == svec[1]);
                REQUIRE(vec.z == svec[2]);
            }
        }

        WHEN("the std::vector does not have three components")
        {
            std::vector<double> vec_less {0, 1};
            std::vector<double> vec_more {0, 1, 2, 3};

            THEN("construction fails")
            {
                REQUIRE_THROWS(Vector3D {vec_less});
                REQUIRE_THROWS(Vector3D {vec_more});
            }
        }
    }
}