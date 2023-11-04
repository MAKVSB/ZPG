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

//include static models
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/plain.h"
#include "Models/plain_indiced.h"
#include "Models/bushes.h"
#include "Models/gift.h"

class ModelLoader
{
public:
	template <typename T, std::size_t N>
	static std::vector<T> convertToVector(const T(&dataArray)[N]) {
		return std::vector<T>(dataArray, dataArray + N);
	}
};