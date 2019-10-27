#pragma once

#include <mlpack/core.hpp>
#include <mlpack/methods/ann/ffn.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/loss_functions/mean_squared_error.hpp>


using namespace mlpack;


//use this if you want custom layers in your ffn.

//template<
//	typename OutputLayerType = ann::NegativeLogLikelihood<>,
//	typename InitializationRuleType = ann::RandomInitialization,
//	typename... CustomLayers
//
//> class ann::FFN;



