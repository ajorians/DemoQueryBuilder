import std;
import <cassert>;

template<typename T, size_t N>
constexpr auto array_size(T(&)[N]) -> size_t { return N; }

static bool check(auto&& arr)
{
	constexpr auto size = array_size(arr);
	return size >= 3;
}

//const char* const emotions[]
//{
//	"\N{WINKING FACE}",
//	"\N{CAT FACE}",
//	"\N{SHOCKED FACE WITH EXPLODING HEAD}"
//};

//int main()
//{
//	assert(check(emotions));
//}