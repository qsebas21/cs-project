#include <SFML/Graphics.hpp>
#include <complex>
#include "oneapi/tbb.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using Complex = std::complex<double>;

int mandelbrot(Complex const &c)
{
  int i = 0;
  auto z = c;
  for (; i != 256 && norm(z) < 4.; ++i)
  {
    z = z * z + c;
  }
  return i;
}

auto to_color(int k)
{
  return k < 256 ? sf::Color{static_cast<sf::Uint8>(10 * k), 0, 0}
                 : sf::Color::Black;
}

int main()
{
  int const display_width{800};
  int const display_height{800};

  Complex const top_left{-2.2, 1.5};
  Complex const lower_right{0.8, -1.5};
  auto const diff = lower_right - top_left;

  auto const delta_x = diff.real() / display_width;
  auto const delta_y = diff.imag() / display_height;

  sf::Image image;
  image.create(display_width, display_height);

  // Changes begin here

  // creating a text file to store the computation time as a function of grain size
  std::ofstream file;
  file.open("times.txt", std::ofstream::out);
  file << "Grain size \t\t  t (us)" << std::endl;



  for (int i = 1; i <= 800; i *= 2)
  {                                                         // for loop for different grain sizes
    auto start = std::chrono::high_resolution_clock::now(); // start time measurement

    // parallel computation here; for loop enclosed by parallel_for blacked_range2d
    // only change in the original for loop is the row and column limits

    oneapi::tbb::parallel_for(

        oneapi::tbb::blocked_range2d<int>(0, display_height, i, 0, display_width, i),
        [&](oneapi::tbb::blocked_range2d<int> range)
        {
          for (int row = range.rows().begin(); row != range.rows().end(); ++row)
          {

            for (int column = range.cols().begin(); column != range.cols().end(); ++column)
            {
              // madelbrot computation
              auto k = mandelbrot(top_left + Complex{delta_x * column, delta_y * row});
              image.setPixel(column, row, to_color(k));
            }
          }
        },
        oneapi::tbb::simple_partitioner());

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    file << i << " \t\t " << duration.count() << std::endl;
  };

  file.close();

  image.saveToFile("mandelbrot.png");
}
