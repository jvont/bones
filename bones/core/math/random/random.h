#pragma once

#include <core/typedefs.h>

#include <chrono>
#include <random>

namespace bones
{
  template<typename T>
  class Random;

  template<>
  class Random<int>
  {
  private:
    std::mt19937::result_type seed;
    std::mt19937 gen;

    std::uniform_int_distribution<int> distribution;
    int lb, ub;

  public:
    Random(u32 seed) : seed(seed) {}
    Random()
    {
      std::random_device rd;

      // seed using system time, in microseconds
      seed = rd() ^ (
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch()).count() +
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch()).count()
      );

      // mersenne_twister_engine seeded with rd()
      gen = std::mt19937(seed);

      // initialize uniform distribution
      lb = 0;
      ub = 100;
      distribution = std::uniform_int_distribution<int>(lb, ub);
    }

    void get_params(int& a, int& b)
    {
      a = lb;
      b = ub;
    }

    void set_params(int a, int b)
    {
      lb = a;
      ub = b;
      distribution.param(std::uniform_int_distribution<int>::param_type(a, b));
    }

    int next(int b)
    {
      if (lb != 0 || ub != b)
        set_params(0, b);

      return distribution(gen);
    };

    int next(int a, int b)
    {
      if (lb != a || ub != b)
        set_params(a, b);

      return distribution(gen);
    }
  };

  template<>
  class Random<float>
  {
  private:
    std::mt19937::result_type seed;
    std::mt19937 gen;

    std::uniform_real_distribution<float> distribution;
    float lb, ub;

  public:
    Random(u32 seed) : seed(seed) {}
    Random()
    {
      std::random_device rd;

      // seed using system time, in microseconds
      seed = rd() ^ (
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch()).count() +
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch()).count()
      );

      // mersenne_twister_engine seeded with rd()
      gen = std::mt19937(seed);

      // initialize uniform distribution
      lb = 0.0f;
      ub = 1.0f;
      distribution = std::uniform_real_distribution<float>(lb, ub);
    }

    void get_params(float& a, float& b)
    {
      a = lb;
      b = ub;
    }
    void set_params(float a, float b)
    {
      lb = a;
      ub = b;
      distribution.param(std::uniform_real_distribution<float>::param_type(a, b));
    }

    float next(float b)
    {
      if (lb != 0 || ub != b)
        set_params(0, b);

      return distribution(gen);
    }

    float next(float a, float b)
    {
      if (lb != a || ub != b)
        set_params(a, b);

      return distribution(gen);
    }
  };

  template<>
  class Random<double>
  {
  private:
    std::mt19937::result_type seed;
    std::mt19937 gen;

    std::uniform_real_distribution<double> distribution;
    double lb, ub;

  public:
    Random(u32 seed) : seed(seed) {}
    Random()
    {
      std::random_device rd;

      // seed using system time, in microseconds
      seed = rd() ^ (
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch()).count() +
        (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch()).count()
      );

      // mersenne_twister_engine seeded with rd()
      gen = std::mt19937(seed);

      // initialize uniform distribution
      lb = 0.0f;
      ub = 1.0f;
      distribution = std::uniform_real_distribution<double>(lb, ub);
    }

    void get_params(double& a, double& b)
    {
      a = lb;
      b = ub;
    }
    void set_params(double a, double b)
    {
      lb = a;
      ub = b;
      distribution.param(std::uniform_real_distribution<double>::param_type(a, b));
    }

    double next(double b)
    {
      if (lb != 0 || ub != b)
        set_params(0, b);

      return distribution(gen);
    }

    double next(double a, double b)
    {
      if (lb != a || ub != b)
        set_params(a, b);

      return distribution(gen);
    }
  };
}