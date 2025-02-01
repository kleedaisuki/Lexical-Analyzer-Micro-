# Lexical Analyzer(Micro)

This is tiny lexical analyzer developed for personal joy~ Because it's for killing time, so I barely optimized my code.

There is only one function, `read_from_file` that . It reads files, and then seperates lines and paragraphs into tokens

## Space left to optimize

+ The class, `String`, declared in `tokens.hpp` and realized in `class.String.cpp`, actually wasted plenty of resource, as it requests 32B directly instead of using `union` to have short strings in stack.

+ The class, `List`, committed the same problem as well. *They are actually part of my own tiny frame, so they may not fit these codes.*

+ When comparing charcaters, branches can also be optimized.

## Something intresting

+ It can ditinguish nearly all operators in C & C++, and you can have more detailed setting easily. You may need a syntax analyzer if wanting more.

+ It can be realized in pure C, but I am too tired to finish such.
