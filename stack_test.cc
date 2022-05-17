#include <gtest/gtest.h>
#include <stack>
#include "stack.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	//EXPECT_STRNE("hello", "world");
	// Expect equality.
	//EXPECT_EQ(6 * 7, 42);
	{
		std::deque<int>						mydeque (3,100);
		std::vector<int>					myvector (2,200);
		std::stack<int>						s1_std;
		ft::stack<int>						s1_ft;
		std::stack<int, std::deque<int> >	s2_std(mydeque);
		ft::stack<int, std::deque<int> >	s2_ft(mydeque);
		std::stack<int, std::vector<int> >	s3_std;
		ft::stack<int, std::vector<int> >	s3_ft;
		std::stack<int, std::vector<int> >	s4_std(myvector);
		ft::stack<int, std::vector<int> >	s4_ft(myvector);

		EXPECT_EQ(s1_std.empty(), s1_ft.empty());
		EXPECT_EQ(s2_std.empty(), s2_ft.empty());
		EXPECT_EQ(s3_std.empty(), s3_ft.empty());
		EXPECT_EQ(s4_std.empty(), s4_ft.empty());

		EXPECT_EQ(s1_std.size(), s1_ft.size());
		EXPECT_EQ(s2_std.size(), s2_ft.size());
		EXPECT_EQ(s3_std.size(), s3_ft.size());
		EXPECT_EQ(s4_std.size(), s4_ft.size());

		EXPECT_EQ(s2_std.top(), s2_ft.top());
		EXPECT_EQ(s4_std.top(), s4_ft.top());

		s2_std.top() -= 42;
		s2_ft.top() -= 42;
		s4_std.top() -= 42;
		s4_ft.top() -= 42;

		EXPECT_EQ(s2_std.top(), s2_ft.top());
		EXPECT_EQ(s4_std.top(), s4_ft.top());

		for (int i=0; i<5; ++i)
		{
			s1_std.push(i);
			s1_ft.push(i);
			EXPECT_EQ(s1_std.top(), s1_ft.top());
		}
		
		EXPECT_EQ(s1_std.empty(), s1_ft.empty());
		EXPECT_EQ(s1_std.size(), s1_ft.size());
		EXPECT_EQ(s1_std.top(), s1_ft.top());

		while (!s1_std.empty() && !s1_ft.empty())
		{
			EXPECT_EQ(s1_std.top(), s1_ft.top());
			s1_std.pop();
			s1_ft.pop();
		}
		
		const std::vector<int>						myvectorbis (21,42);
		const std::stack<int, std::vector<int> >	s5_std(myvectorbis);
		const ft::stack<int, std::vector<int> >		s5_ft(myvectorbis);
		
		EXPECT_EQ(s1_std == s1_std, s1_ft == s1_ft);
		EXPECT_EQ(s2_std == s2_std, s2_ft == s2_ft);
		EXPECT_EQ(s3_std == s3_std, s3_ft == s3_ft);
		EXPECT_EQ(s4_std == s4_std, s4_ft == s4_ft);
		EXPECT_EQ(s4_std == s5_std, s4_ft == s5_ft);
		
		EXPECT_EQ(s1_std != s1_std, s1_ft != s1_ft);
		EXPECT_EQ(s2_std != s2_std, s2_ft != s2_ft);
		EXPECT_EQ(s3_std != s3_std, s3_ft != s3_ft);
		EXPECT_EQ(s4_std != s4_std, s4_ft != s4_ft);
		EXPECT_EQ(s4_std != s5_std, s4_ft != s5_ft);
		
		EXPECT_EQ(s1_std < s1_std, s1_ft < s1_ft);
		EXPECT_EQ(s2_std < s2_std, s2_ft < s2_ft);
		EXPECT_EQ(s3_std < s3_std, s3_ft < s3_ft);
		EXPECT_EQ(s4_std < s4_std, s4_ft < s4_ft);
		EXPECT_EQ(s4_std < s5_std, s4_ft < s5_ft);
		
		EXPECT_EQ(s1_std <= s1_std, s1_ft <= s1_ft);
		EXPECT_EQ(s2_std <= s2_std, s2_ft <= s2_ft);
		EXPECT_EQ(s3_std <= s3_std, s3_ft <= s3_ft);
		EXPECT_EQ(s4_std <= s4_std, s4_ft <= s4_ft);
		EXPECT_EQ(s4_std <= s5_std, s4_ft <= s5_ft);
		
		EXPECT_EQ(s1_std > s1_std, s1_ft > s1_ft);
		EXPECT_EQ(s2_std > s2_std, s2_ft > s2_ft);
		EXPECT_EQ(s3_std > s3_std, s3_ft > s3_ft);
		EXPECT_EQ(s4_std > s4_std, s4_ft > s4_ft);
		EXPECT_EQ(s4_std > s5_std, s4_ft > s5_ft);
		
		EXPECT_EQ(s1_std >= s1_std, s1_ft >= s1_ft);
		EXPECT_EQ(s2_std >= s2_std, s2_ft >= s2_ft);
		EXPECT_EQ(s3_std >= s3_std, s3_ft >= s3_ft);
		EXPECT_EQ(s4_std >= s4_std, s4_ft >= s4_ft);
		EXPECT_EQ(s4_std >= s5_std, s4_ft >= s5_ft);
	}
	{
		const std::deque<int>						mydeque (3,100);
		const std::vector<int>						myvector (2,200);
		const std::stack<int>						s1_std;
		const ft::stack<int>						s1_ft;
		const std::stack<int, std::deque<int> >		s2_std(mydeque);
		const ft::stack<int, std::deque<int> >		s2_ft(mydeque);
		const std::stack<int, std::vector<int> >	s3_std;
		const ft::stack<int, std::vector<int> >		s3_ft;
		const std::stack<int, std::vector<int> >	s4_std(myvector);
		const ft::stack<int, std::vector<int> >		s4_ft(myvector);

		EXPECT_EQ(s1_std.empty(), s1_ft.empty());
		EXPECT_EQ(s2_std.empty(), s2_ft.empty());
		EXPECT_EQ(s3_std.empty(), s3_ft.empty());
		EXPECT_EQ(s4_std.empty(), s4_ft.empty());

		EXPECT_EQ(s1_std.size(), s1_ft.size());
		EXPECT_EQ(s2_std.size(), s2_ft.size());
		EXPECT_EQ(s3_std.size(), s3_ft.size());
		EXPECT_EQ(s4_std.size(), s4_ft.size());

		EXPECT_EQ(s2_std.top(), s2_ft.top());
		EXPECT_EQ(s4_std.top(), s4_ft.top());
		
		const std::vector<int>						myvectorbis (21,42);
		const std::stack<int, std::vector<int> >	s5_std(myvectorbis);
		const ft::stack<int, std::vector<int> >		s5_ft(myvectorbis);
		
		EXPECT_EQ(s1_std == s1_std, s1_ft == s1_ft);
		EXPECT_EQ(s2_std == s2_std, s2_ft == s2_ft);
		EXPECT_EQ(s3_std == s3_std, s3_ft == s3_ft);
		EXPECT_EQ(s4_std == s4_std, s4_ft == s4_ft);
		EXPECT_EQ(s4_std == s5_std, s4_ft == s5_ft);
		
		EXPECT_EQ(s1_std != s1_std, s1_ft != s1_ft);
		EXPECT_EQ(s2_std != s2_std, s2_ft != s2_ft);
		EXPECT_EQ(s3_std != s3_std, s3_ft != s3_ft);
		EXPECT_EQ(s4_std != s4_std, s4_ft != s4_ft);
		EXPECT_EQ(s4_std != s5_std, s4_ft != s5_ft);
		
		EXPECT_EQ(s1_std < s1_std, s1_ft < s1_ft);
		EXPECT_EQ(s2_std < s2_std, s2_ft < s2_ft);
		EXPECT_EQ(s3_std < s3_std, s3_ft < s3_ft);
		EXPECT_EQ(s4_std < s4_std, s4_ft < s4_ft);
		EXPECT_EQ(s4_std < s5_std, s4_ft < s5_ft);
		
		EXPECT_EQ(s1_std <= s1_std, s1_ft <= s1_ft);
		EXPECT_EQ(s2_std <= s2_std, s2_ft <= s2_ft);
		EXPECT_EQ(s3_std <= s3_std, s3_ft <= s3_ft);
		EXPECT_EQ(s4_std <= s4_std, s4_ft <= s4_ft);
		EXPECT_EQ(s4_std <= s5_std, s4_ft <= s5_ft);
		
		EXPECT_EQ(s1_std > s1_std, s1_ft > s1_ft);
		EXPECT_EQ(s2_std > s2_std, s2_ft > s2_ft);
		EXPECT_EQ(s3_std > s3_std, s3_ft > s3_ft);
		EXPECT_EQ(s4_std > s4_std, s4_ft > s4_ft);
		EXPECT_EQ(s4_std > s5_std, s4_ft > s5_ft);
		
		EXPECT_EQ(s1_std >= s1_std, s1_ft >= s1_ft);
		EXPECT_EQ(s2_std >= s2_std, s2_ft >= s2_ft);
		EXPECT_EQ(s3_std >= s3_std, s3_ft >= s3_ft);
		EXPECT_EQ(s4_std >= s4_std, s4_ft >= s4_ft);
		EXPECT_EQ(s4_std >= s5_std, s4_ft >= s5_ft);
	}
}
