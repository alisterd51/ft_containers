# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 03:39:54 by anclarma          #+#    #+#              #
#    Updated: 2022/05/16 18:00:49 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 2.8)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -Weffc++")

set(SRCS1
	main_iterrators_traits.cpp
	)
set(SRCS2
	test_rbtree.cpp
	)
set(SRCS3
	test_pop_back.cpp
	)
set(HEADERS
	includes/map.hpp
	includes/algorithm.hpp
	includes/bitset.hpp
	includes/deque.hpp
	includes/ft_containers_monkey_tester
	includes/iterator.hpp
	includes/list.hpp
	includes/map.hpp
	includes/queue.hpp
	includes/set.hpp
	includes/stack.hpp
	includes/type_traits.hpp
	includes/utility.hpp
	includes/vector.hpp
	)

include_directories(
	includes
	)

add_executable(test1 ${SRCS1} ${HEADERS})
add_executable(test2 ${SRCS2} ${HEADERS})
add_executable(test3 ${SRCS3} ${HEADERS})
