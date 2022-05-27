# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 03:39:54 by anclarma          #+#    #+#              #
#    Updated: 2022/05/27 12:39:12 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.14)
project(ft_containers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -Weffc++ -fsanitize=address -g3")

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
	)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

enable_testing()

add_executable(
	stack_test
	stack_test.cc
	)
target_link_libraries(
	stack_test
	gtest_main
	)

include(GoogleTest)
gtest_discover_tests(stack_test)
