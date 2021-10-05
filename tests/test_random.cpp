#include <core/math/random/random.h>
#include <core/math/math.h>
using namespace bones;

#include <doctest/doctest.h>

TEST_CASE("PRNG uniform distributions")
{
  int iterations = 100000;
  
  SUBCASE("uniform int distribution")
  {
    Random<int> rand;
    unsigned int sum = 0;

    for (int i = 0; i <  iterations; i++)
      sum += rand.next(1, 9);

    float avg = sum / (float)iterations;
    CHECK(math::approx_equal(avg, 5.0f, 0.01f));
  }

  SUBCASE("uniform real distribution (float)")
  {
    Random<float> rand;
    float sum = 0;

    for (int i = 0; i <  iterations; i++)
      sum += rand.next(1.0f, 9.0f);

    float avg = sum / (float)iterations;
    CHECK(math::approx_equal(avg, 5.0f, 0.01f));
  }
}
