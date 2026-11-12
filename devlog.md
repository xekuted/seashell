# 8th November, 2026

### 10:11 a.m.

The goal is to create this shell as a learning experience rather than just a mere college project. I wanted to get my hands dirty with systems programming, and I believe this would be a good way to go about it.

I plan on creating a shell of my own, followed by a system monitor that will run alongside it. For now, I am trying to understand how a shell works and will attempt to implement the concepts myself as much as possible.

AI is strictly prohibited. Any help I need will have to come the old-school way, i.e., through blogs and forums.

### 10:26 a.m.

Understood the underlying mechanism of a shell, and it pretty much boils down to a REPL, which stands for Read, Evaluate, Print, and Loop. I'm going to work on a minimal implementation of this idea first.

### 11:08 a.m. [fflush and scanf vs fgets]

Came across a function called `fflush` and understood how it works. Through this, I also got to understand how buffers work and how `stdin` and `stdout` function in general.

Then came my actual issue. I was trying to take input from the user, but every time I entered something, it only printed the first half.

#### Example:
```sh
> hello world
hello> world>
```

This taught me how `scanf` and `input stream` work. Learnt how scanf only takes input until it hits a whitespace. So what's happening was:
<ol>
<li> The space after hello terminated the string conversion.</li>
<li> This caused world to remain unread in the input stream (stdin).</li>
<li> The shell printed another > .</li>
<li> The next scanf() immediately read the remaining "world" and the shell printed it.</li>
</ol> 
<br>

The solution to this issue is `fgets`. 

fgets basically reads the entire input stream till `[sizeofinput-1]` and then stores it into the buffer. It stops only when it encounters a newline or end of file. It then adds a null terminator (\0) to the end of the string.


### 12:42 p.m.

Finally done with the basic implementation plus implemented an extra check (checking whether an input is empty or not) via `strcspn`. This new function will eventually be used for phase 2 of this shell.

### 1:58 p.m.

Phase 2 is gonna be parsing. The goal is to take commands and parse each command separately.

### 10:22 p.m.

Got busy with some other work and diwali decor, got tokenization working, yet to implement proper parsing. Got to learn about how functions like `strtok` work and finally understood what roles do header files play. Gonna finish parsing now.

### 11:03 p.m.

Got command execution working. Worked with many new libs like `unistd.h`, `sys/types.h` and `sys/wait.h`. Also understood how functions like `fork()`,`execvp()`, `_exit()`,etc work. Lots of learning! Gotta improve the parser now and then work on built-in commands.

## Progress so far
<ol>
    <li>Read user input using fgets().</li>
    <li>Tokenize input using the parser.</li>
    <li>Create a child process using fork().</li>
    <li>Execute external programs using execvp().</li>
    <li>Make the parent wait using waitpid().</li>
    <li>Handle failed process creation and failed command execution.</li>
</ol>

### 11:26 p.m.

I've decided to revisit and improve the parser later, as implementing proper parsing is more involved than I initially anticipated.

For now, I'll focus on getting a functional shell running and progressively address edge cases and improve the parser as the project evolves.

Time to work on built-ins!

# 9th November, 2026

### 9:47 p.m.

Couldn't continue with the project yesterday so time to finish it now (hopefully). Gonna implement the following built-ins:

- `cd`
- `pwd`
- `exit`
- `help`

# 10th November, 2026

### 12:15 a.m.

Finished implementing the built-in commands.

# 11th November, 2026

### 12:02 p.m.
 Improving the parser has got to be the most confusing thing so far, working with pointers and understanding how each command and argument is stored in the memory isn't easy. It's literally the only thing left to improve and only when it's correctly implemented can I work with features like pipes and input/output redirection. A simple program like shell that we use on a daily basis is truly not just "simple". This is the state when I'm just trying to go for a very minimal implementation instead of a proper shell with 1000 other features. Will work on it later.

### 12:07 p.m.

Thinking of working on the looks department of the shell so that at least it looks presentable and feels good to use.

### 12:32 p.m.

Getting to understand header files better and also learnt about makefile. Understood what are the diff kinds of ways to write a header file.

### 1:50 p.m.
Got done with the looks of the shell and I'm very satisfied with it. Now the only thing remaining is the parser and the redirections.

# 12th November, 2026

### 9:00 p.m.

Gonna start with the parser (again) and hopefully get it working properly within the next hour.

### 10:22 p.m.
Got done with the parser. For some reason I was able to just "do it", turns out i don't need to take every concept way too seriously if I don't get it, I can just understand enough to be able to work with it and then understand it deeply over time. I think only input/output redirection remains atp and seashell will finally be ready!
