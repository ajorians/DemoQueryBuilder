export module QueryLanguage;

import std;
import <cassert>;

#if defined(_DEBUG) && defined(NDEBUG)
#error "Please enable assertions in debug mode"
#endif

export 
struct QueryBuilder
{
	auto greater(int value) && -> QueryBuilder&&
	{
		operators.push_back({ .value = value, .kind = Operator::Kind::Greater });
		return std::move( *this );
	}

	auto build() const& -> std::function<std::vector<int>( const std::vector<int>&)>
	{
		decltype(build()) query = [](auto data) { return data; };

		using Data = std::vector<int>;
		auto fused = fuse(operators);

		for (auto op : validate( fused ) )
		{
			switch (op.kind)
			{
			case Operator::Kind::Greater:
				query = [previous = std::move( query ),
				         minimum = op.value](const Data& data) {
					Data output;
					for (auto x : previous(data))
					{
						if (x > minimum)
						{
							output.push_back(x);
						}
					}
					return output;
				};
				break;
			}
		}

		return query;
	}

private:
	struct Operator
	{
		enum class Kind
		{
			Greater,
			/*...*/
		};

		union { int value; /*...*/ };
		Kind kind;
	};

	std::vector<Operator> operators;

	static std::vector<Operator> fuse(const std::vector<Operator>& ops)
	{
		std::vector<Operator> fused;
		for ( int i=1; i<ops.size(); ++i)
		{
			if ( ops[i].kind == Operator::Kind::Greater && ops[i - 1].kind == Operator::Kind::Greater)
			{
				if ( ops[i].value > ops[i - 1].value )
				{
					fused.push_back(ops[i]);
				}
				else
				{
					fused.push_back(ops[i - 1]);
				}
			}
		}
		return fused;
	}

	static const std::vector<Operator>& validate(const std::vector<Operator>& ops)
	{
		assert(ops.size() > 0);
		return ops;
	}
};

