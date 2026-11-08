## 8th November, 2026

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
