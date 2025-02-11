C program emulating the piping and redirection of Bash. A school project at Hive Helsinki, part of the 42 network of schools. Got full 125/125 points, even though there were a couple of bugs I found after the last evaluation.
There is a lot of unnecessary repeat code especially in the "_cmd" functions, but it is partly due to our schools limitations on things like function arguments (max 4) and variables in a function. Also the exit code handling is not very elegant.

The program mimics the behavior of
```
< file1 command | command > file2
```
The equivalent in pipex would be
```
./bin/pipex file1 "command" "command" file2
```
For example
```
./bin/pipex Makefile "cat" "tr -d ' '" makefile_with_no_spaces.txt
```
The mandatory is limited to exactly two commands, but in the bonus you can go above two commands. You always need one infile and one outfile, even if your commands don't use them
```
./bin/pipex_bonus Makefile cat cat cat cat cat cat cat cat outfile
```
Also in the bonus part we got to implement a heredoc.
```
./bin/pipex_bonus here_doc END cat cat outf
```
behaves similarly to
```
cat << END | cat >> outf
```
The here_doc mode of the bonus also works with multiple pipes.
