# Week 9

- What is buffer?
([source](https://www.learncpp.com/cpp-tutorial/input-and-output-io-streams/#comment-477661))

  A chunk of memory used to store something.
  When you copy a solution from your neighbor at school, you don't look at 1
  character and write it down on your paper, then proceed with the next
  character. Instead, you read some of your neighbors words and store them in
  your brain. Then write down the words on your paper. That's a lot faster. Your
  brain is the buffer. Writing the words on your paper is flushing.

- What is the difference between buffer and stream?
([source](https://www.learncpp.com/cpp-tutorial/input-and-output-io-streams/#comment-416628))

  - A buffer is a place where data is stored, usually without a specific type.
  - A stream has a buffer in which it stores the data before sending it somewhere
  else.
  - You might be able to access the buffer, e.g., for `std::cout` via
  ```cpp
  auto buf{ std::cout.rdbuf() };
  std::cout << "There are " << buf.in_avail() << " characters available\n";
  ```

## Outline

[video](https://youtu.be/c3HWPPnVSYI)

- Object oriented programming II
- Type conversion / type casting
- File IO

## Further reading resources

- [Chapter 23, learncpp.com](https://www.learncpp.com/cpp-tutorial/input-and-output-io-streams/)
- [Buffered vs unbuffered IO](https://stackoverflow.com/a/1450563/13041067)
- [What does flushing the buffer mean?](https://stackoverflow.com/q/15042849/13041067)

