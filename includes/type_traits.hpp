/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:51:36 by anclarma          #+#    #+#             */
/*   Updated: 2022/05/03 13:32:01 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace	ft
{
	template <class T, T v>
		struct integral_constant
		{
			static const T value = v;
			typedef T value_type;
			typedef integral_constant<T,v> type;
			operator T()
			{
				return (v);
			}
		};

	typedef integral_constant<bool, false>	false_type;
	typedef integral_constant<bool, true>	true_type;

	template<typename>                                                            
		struct is_integral_helper : public false_type
		{
		};                                                    
	template<>
		struct is_integral_helper<bool> : public true_type
		{
		};
	template<>
		struct is_integral_helper<char> : public true_type
		{
		};
	template<>
		struct is_integral_helper<wchar_t> : public true_type
		{
		};
	template<>
		struct is_integral_helper<signed char> : public true_type
		{
		};
	template<>
		struct is_integral_helper<short int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<long int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<long long int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<unsigned char> : public true_type
		{
		};
	template<>
		struct is_integral_helper<unsigned short int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<unsigned int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<unsigned long int> : public true_type
		{
		};
	template<>
		struct is_integral_helper<unsigned long long int> : public true_type
		{
		};

	//is_integral
	template <class T>
		struct	is_integral
		: is_integral_helper<T>::type
	{
	};

	//enable_if
	template <bool B, class T = void>
		struct	enable_if
		{
		};
	template <class T>
		struct	enable_if<true, T>
		{
			typedef T	type;
		};

	//is_same
	template <class T, class U>
		struct is_same
		: public false_type
		{
		};
	template<typename _Tp>
		struct is_same<_Tp, _Tp>
		: public true_type
		{
		};
}

#endif
