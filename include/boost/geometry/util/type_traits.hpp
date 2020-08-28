// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP
#define BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP


#include <iterator>
#include <type_traits>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/mpl/has_xxx.hpp>
#include <boost/range/has_range_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// C++17
template <bool B>
using bool_constant = std::integral_constant<bool, B>;


// C++17
template <typename ...>
struct conjunction
    : std::true_type
{};
template<typename Trait>
struct conjunction<Trait>
    : Trait
{};
template <typename Trait, typename ...Traits>
struct conjunction<Trait, Traits...>
    : std::conditional_t<Trait::value, conjunction<Traits...>, Trait>
{};


// C++17
template <typename ...>
struct disjunction
    : std::false_type
{};
template <typename Trait>
struct disjunction<Trait>
    : Trait
{};
template <typename Trait, typename ...Traits>
struct disjunction<Trait, Traits...>
    : std::conditional_t<Trait::value, Trait, disjunction<Traits...>>
{};


// C++17
template <typename Trait>
struct negation
    : bool_constant<!Trait::value>
{};


/*
template <typename ...Traits>
using and_ = conjunction<Traits...>;

template <typename ...Traits>
using or_ = disjunction<Traits...>;

template <typename Trait>
using not_ = negation<Trait>;
*/


template <typename T>
struct is_geometry
    : bool_constant<! std::is_void<typename tag<T>::type>::value>
{};

template <typename T>
struct is_not_geometry
    : std::is_void<typename tag<T>::type>
{};


template <typename T>
struct is_point
    : std::is_same<point_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_point
    : std::is_same<multi_point_tag, typename tag<T>::type>
{};

template <typename T>
struct is_pointlike
    : std::is_base_of<pointlike_tag, typename tag<T>::type>
{};


template <typename T>
struct is_segment
    : std::is_same<segment_tag, typename tag<T>::type>
{};

template <typename T>
struct is_linestring
    : std::is_same<linestring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_linestring
    : std::is_same<multi_linestring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polylinear
    : std::is_base_of<polylinear_tag, typename tag<T>::type>
{};

template <typename T>
struct is_linear
    : std::is_base_of<linear_tag, typename tag<T>::type>
{};


template <typename T>
struct is_box
    : std::is_same<box_tag, typename tag<T>::type>
{};

template <typename T>
struct is_ring
    : std::is_same<ring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polygon
    : std::is_same<polygon_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_polygon
    : std::is_same<multi_polygon_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polygonal
    : std::is_base_of<polygonal_tag, typename tag<T>::type>
{};

template <typename T>
struct is_areal
    : std::is_base_of<areal_tag, typename tag<T>::type>
{};


template <typename T>
struct is_polysegmental
    : bool_constant<is_polylinear<T>::value || is_polygonal<T>::value>
{};


template <typename T>
struct is_multi
    : std::is_base_of<multi_tag, typename tag<T>::type>
{};


template <typename T>
struct is_multi_element
    : bool_constant<is_point<T>::value || is_linestring<T>::value || is_polygon<T>::value>
{};


template <typename T>
struct is_single
    : std::is_base_of<single_tag, typename tag<T>::type>
{};


template <typename Geometry, typename T = void>
struct enable_if_point
    : std::enable_if<is_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_point_t = typename enable_if_point<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_multi_point
    : std::enable_if<is_multi_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_point_t = typename enable_if_multi_point<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_pointlike
    : std::enable_if<is_pointlike<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_pointlike_t = typename enable_if_pointlike<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_segment
    : std::enable_if<is_segment<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_segment_t = typename enable_if_segment<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polylinear
    : std::enable_if<is_polylinear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polylinear_t = typename enable_if_polylinear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_linear
    : std::enable_if<is_linear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_linear_t = typename enable_if_linear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_box
    : std::enable_if<is_box<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_box_t = typename enable_if_box<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polygonal
    : std::enable_if<is_polygonal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polygonal_t = typename enable_if_polygonal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_areal
    : std::enable_if<is_areal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_areal_t = typename enable_if_areal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polysegmental
    : std::enable_if<is_polysegmental<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polysegmental_t = typename enable_if_polysegmental<Geometry, T>::type;



BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category)

template <typename T>
struct is_iterator
    : bool_constant
        <
            has_iterator_category
                <
                    std::iterator_traits<T>
                >::value
        >
{};


template <typename T, bool HasIterator = boost::has_range_iterator<T>::value>
struct is_range_impl
    : is_iterator
        <
            typename boost::range_iterator<T>::type
        >
{};
template <typename T>
struct is_range_impl<T, false>
    : std::false_type
{};

template <typename T>
struct is_range
    : is_range_impl<T>
{};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP
