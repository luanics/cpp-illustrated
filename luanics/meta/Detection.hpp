#pragma once

#include "luanics/meta/Detection.ipp"

namespace luanics {

/// Implementation of Walter Brown's detection toolkit.
/// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4436.pdf

template<template<typename ...> class OpT, typename ...ArgsT>
using IsDetected = detail::Detector<void, OpT, ArgsT...>;

template<template<typename ...> class OpT, typename ...ArgsT>
bool constexpr IsDetected_v = IsDetected<OpT, ArgsT...>::value;

template<template<typename ...> class OpT, typename ...ArgsT >
using Detected_t = typename IsDetected<OpT, ArgsT...>::type;

}  // namespace luanics
