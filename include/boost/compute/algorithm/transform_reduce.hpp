//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/detail/binary_transform_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/default_queue_for_iterator.hpp>

namespace boost {
namespace compute {

template<class InputIterator,
         class UnaryTransformFunction,
         class T,
         class BinaryReduceFunction>
inline T transform_reduce(InputIterator first,
                          InputIterator last,
                          UnaryTransformFunction transform_function,
                          T init,
                          BinaryReduceFunction reduce_function,
                          command_queue &queue)
{
    return ::boost::compute::reduce(
               ::boost::compute::make_transform_iterator(first, transform_function),
               ::boost::compute::make_transform_iterator(last, transform_function),
               init,
               reduce_function,
               queue);
}

template<class InputIterator,
         class UnaryTransformFunction,
         class T,
         class BinaryReduceFunction>
inline T transform_reduce(InputIterator first,
                          InputIterator last,
                          UnaryTransformFunction transform_function,
                          T init,
                          BinaryReduceFunction reduce_function)
{
    command_queue queue = detail::default_queue_for_iterator(first);

    return ::boost::compute::transform_reduce(first,
                                              last,
                                              transform_function,
                                              init,
                                              reduce_function,
                                              queue);
}

template<class InputIterator1,
         class InputIterator2,
         class BinaryTransformFunction,
         class T,
         class BinaryReduceFunction>
inline T transform_reduce(InputIterator1 first1,
                          InputIterator1 last1,
                          InputIterator2 first2,
                          BinaryTransformFunction transform_function,
                          T init,
                          BinaryReduceFunction reduce_function,
                          command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    return ::boost::compute::reduce(
               detail::make_binary_transform_iterator(first1,
                                                      first2,
                                                      transform_function),
               detail::make_binary_transform_iterator(last1,
                                                      first2 + n,
                                                      transform_function),
               init,
               reduce_function,
               queue);
}

template<class InputIterator1,
         class InputIterator2,
         class BinaryTransformFunction,
         class T,
         class BinaryReduceFunction>
inline T transform_reduce(InputIterator1 first1,
                          InputIterator1 last1,
                          InputIterator2 first2,
                          BinaryTransformFunction transform_function,
                          T init,
                          BinaryReduceFunction reduce_function)
{
    command_queue queue = detail::default_queue_for_iterator(first1);

    return ::boost::compute::transform_reduce(first1,
                                              last1,
                                              first2,
                                              transform_function,
                                              init,
                                              reduce_function,
                                              queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP
