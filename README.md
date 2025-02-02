# Lexical Analyzer(Micro)

This is tiny lexical analyzer developed for personal joy~ Because it's for killing time, so I barely optimized my code.

The function, `read_from_file`, reads files, and then seperates lines and paragraphs into C/C++ tokens.

## Space left to optimize

+ The class, `List`, committed the same problem as well. *They are actually part of my own tiny frame, so they may not fit these codes.*

+ When comparing charcaters, branches can also be optimized.

## Something intresting

+ It can ditinguish nearly all operators in C & C++, and you can have more detailed setting easily. You may need a syntax analyzer if wanting more.

+ It can be realized in pure C, but I am too tired to finish such.
