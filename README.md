<h1 align="center">
	minishell
</h1>
<h2 align="center">
	<i>Creating a shell in C</i><br>
</h2>

<p align="center">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/psimarro-g/minishell?color=green" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/psimarro-g/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/psimarro-g/minishell?color=blue" />
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/psimarro-g/minishell?color=lightblue" />
	<img alt="GitHub code lines" src="https://tokei.rs/b1/github/psimarro-g/minishell?branch=parser&color=orange" height="20"/>
</p>

<p align="center">
	Mac OS X 10.15.7 (Darwin Kernel Version 19.6.0)<br>
</p>


## The shell

<p align="center">
<img src="https://github.com/psimarro-g/minishell/blob/main/image/Screen%20Shot%202023-10-29%20at%209.22.39%20PM.png">
</p>

This project comprises a simple yet functional shell that aims to replicate bash's basic functionality.

It should:
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
- Not use more than one global variable.
- Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
  - < should redirect input.
  - \> should redirect output.
  - << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
  - \>\> should redirect output in append mode.
- Implement pipes ( | character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- The shell also implements the following builtins:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

<h2 align="center">
	<b><i>Contributors</i></b><br>
</h2>

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table align="center">
  <tbody>
	<td align="center" valign="top" width="14.28%"><a href="https://github.com/psimarro-g"><img src="https://avatars.githubusercontent.com/u/94054765?v=4" width="100px;" alt="Pablo Simarro"/><br /><sub><b>psimarro-g</b></sub></a><br /></td>
	<td align="center" valign="top" width="14.28%"><a href="https://github.com/damontoro"><img src="https://avatars.githubusercontent.com/u/57947618?v=4" width="100px;" alt="David Montoro"/><br /><sub><b>damontoro</b></sub></a><br /></td>
  </tbody>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->
