import QueryLanguage;
import std;

int main()
{
	auto query = QueryBuilder()
		.greater( 42 )
		.greater( 19 )
		.build();

	std::vector<int> data = { 10, 20, 30, 40, 50, 60, 70,
	                          10, 20, 30, 40, 50, 60, 70 };

	auto result = query(data);

	for (auto x : result)
	{
		std::printf( "%d ", x );
	}//Outputs: 50 60 70 50 60 70
}