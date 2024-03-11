# Lsystem-CS-sem1

🧩 The Lindenmayer system, abbreviated as L-system, is a formal system defining languages. It was created for modeling plants by the biologist Aristid Lindenmayer.

A deterministic context-free L-system, called D0L, is a triple (S, A, R), where S is an alphabet, A is a word over S called an axiom, and R is a set of replacement rules that associate symbols with words over S. For each element in S, there is at most one replacement rule in R.

A word w belongs to the language defined by an L-system if and only if there exists a non-negative integer n such that w has a derivation of length n. We assume that the axiom has a derivation of length 0. A word with a derivation of length n + 1 is obtained from a word with a derivation of length n by simultaneously replacing each symbol with the word specified by its rule, or leaving it unchanged if there is no rule for it.

We consider a textual interpretation of words in the language defined by an L-system. The interpretation starts with a sequence of lines called the prologue, followed by a sequence of lines corresponding to individual symbols of the word, and ends with a sequence of lines called the epilogue. The lines corresponding to symbols are determined using interpretation rules. For each symbol, there is at most one interpretation rule. Symbols of the word for which no interpretation is specified are omitted from it.

🧩 INPUT:
The input to the program consists of a line with a non-negative integer specifying the length of the derivation, followed by lines describing the L-system and lines describing the interpretation of the word.

The description of the L-system consists of a line containing the axiom, followed by a sequence of lines with replacement rules. A replacement rule line starts with the symbol to be replaced, followed by the word replacing it. The alphabet of the L-system is not explicitly given. We assume it is the set of symbols occurring in the axiom and replacement rules.

The description of the word interpretation starts with a sequence of lines for the prologue, followed by lines for interpretation rules, and finally, lines for the epilogue. Each of these three sequences is preceded by an empty line. An interpretation rule line starts with the interpreted symbol, followed by the text that should be output for that symbol.

🧩 OUTPUT:
The program output consists of printing to standard output, one after the other, in the following order:
sequence of lines for the prologue,
sequence of lines representing the interpretation of the derived word,
sequence of lines for the epilogue.
Each output line ends with a newline character.

❗️The program executed on data from the .in file generates a file in the PostScript language. You can convert it to the .pdf format using the ps2pdf program and get some cool results (check examples in attached files)❗️

❗In the code, both variable names and comments are in Polish because this program was one of the projects for the first semester of computer science studies. Sorry for the inconvenience.❗️
