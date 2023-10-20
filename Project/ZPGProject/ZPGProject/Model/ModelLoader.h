/**
 * @file ModelLoader.h
 *
 * @brief Helper methods and utilities for ModelBuilder class.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once

#include <vector>

class ModelLoader
{
public:
	template <typename T, std::size_t N>
	static std::vector<T> convertToVector(const T(&dataArray)[N]) {
		return std::vector<T>(dataArray, dataArray + N);
	}
};