QPid-Proton Demos
=================

These scripts are for testing purposes only.  It does not check
failures and does not clean up after itself.  Use only to verify
correctness of installation.

simple
------

The "simple" code (*simple.py* and *simple.c*) do nothing explicit
with SASL.  An invocation of them might look like:

```shell
$ ./simple.py amqp://qpid/amq.topic 'Hello, world!'
Got: "Hello, world!"
$ 
```

or perhaps


```shell
$ make simple
gcc -Wall -Wextra -pedantic -std=c99 -O0 -ggdb  -lqpid-proton  simple.c -o simple
$ ./simple amqp://qpid/amq.topic 'Hello, world!'
Got: "Hello, world!"
$ 
```

In theory, these two are identical.  In practice, the C is a whole lot
easier to debug.  I recommend starting with the Python and only using
the C if failure is observed.

