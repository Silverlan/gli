///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file test/core/texture_1d.cpp
/// @date 2013-01-12 / 2013-01-12
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/core/texture1d.hpp>

int test_texture1d_clear()
{
	int Error(0);

	glm::u8vec4 const Orange(255, 127, 0, 255);

	gli::texture1D Texture(
		gli::texture1D::size_type(glm::log2(16u) + 1),
		gli::RGBA8U,
		gli::texture1D::dimensions_type(16));

	//Texture.clear<glm::u8vec4>(Cyan);

	return Error;
}

int test_texture1d_query()
{
	int Error(0);

	gli::texture1D Texture(
		gli::texture1D::size_type(2),
		gli::RGBA8U,
		gli::texture1D::dimensions_type(2));

	Error += Texture.size() == sizeof(glm::u8vec4) * 3 ? 0 : 1;
	Error += Texture.format() == gli::RGBA8U ? 0 : 1;
	Error += Texture.levels() == 2 ? 0 : 1;
	Error += !Texture.empty() ? 0 : 1;
	Error += Texture.dimensions() == 2 ? 0 : 1;

	return Error;
}

int test_texture1d_access()
{
	int Error(0);

	{
		gli::texture1D Texture(
			gli::texture1D::size_type(2),
			gli::RGBA8U,
			gli::texture1D::dimensions_type(2));
		assert(!Texture.empty());

		gli::image Image0 = Texture[0];
		gli::image Image1 = Texture[1];
		
		std::size_t Size0 = Image0.size();
		std::size_t Size1 = Image1.size();

		Error += Size0 == sizeof(glm::u8vec4) * 2 ? 0 : 1;
		Error += Size1 == sizeof(glm::u8vec4) * 1 ? 0 : 1;

		*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
		*Image1.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

		glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
		glm::u8vec4 * PointerB = Image1.data<glm::u8vec4>();

		glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
		glm::u8vec4 * Pointer1 = Texture.data<glm::u8vec4>() + 2;

		Error += PointerA == Pointer0 ? 0 : 1;
		Error += PointerB == Pointer1 ? 0 : 1;

		glm::u8vec4 ColorA = *Image0.data<glm::u8vec4>();
		glm::u8vec4 ColorB = *Image1.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;
		glm::u8vec4 Color1 = *Pointer1;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
	}

	{
		gli::texture1D Texture(
			gli::texture1D::size_type(1),
			gli::RGBA8U,
			gli::texture1D::dimensions_type(2));

		std::size_t SizeA = Texture.size();
		Error += SizeA == sizeof(glm::u8vec4) * 2 ? 0 : 1;

		gli::image Image0 = Texture[0];
		
		std::size_t Size0 = Image0.size();
		Error += Size0 == sizeof(glm::u8vec4) * 2 ? 0 : 1;

		*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
		glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *PointerA;
		glm::u8vec4 Color0 = *Pointer0;
		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	return Error;
}

int test_texture1d_size()
{
	int Error(0);

	struct test
	{
		test(
			gli::format const & Format,
			gli::texture1D::dimensions_type const & Dimensions,
			gli::texture1D::size_type const & Size) :
			Format(Format),
			Dimensions(Dimensions),
			Size(Size)
		{}

		gli::format Format;
		gli::texture1D::dimensions_type Dimensions;
		gli::texture1D::size_type Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, gli::texture1D::dimensions_type(4), 16));
	Tests.push_back(test(gli::R8U, gli::texture1D::dimensions_type(4), 4));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::texture1D Texture(
			gli::texture1D::size_type(1),
			Tests[i].Format,
			gli::texture1D::dimensions_type(4));

		gli::image Image = Texture[0];

		Error += Image.size() == Tests[i].Size ? 0 : 1;
		Error += Texture.size() == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_texture1d_size();
	Error += test_texture1d_query();
	Error += test_texture1d_clear();
	Error += test_texture1d_access();

	return Error;
}
