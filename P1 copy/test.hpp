template <typename T, int Val>
class Test
{
public:
    // For no reason, let's prevent @val from being 2.
    // (Note: I don't think it matters too much where this static assertion
    // is placed.)
    static_assert(Val != 2, "Val cannot be 2.");
        
    Test() = default;
};

