# The Hash data structure

## Terminology

- Hash function
- Hashing
- Hash table
- Key/value
- Slot/bucket

- Collision resolution
  - chained hashing
    - each slot is the head of a linked-list or chain
  - Open address hashing
    - linear probing
    - quadratic probing
    - double hashing

## About the Makefile

For this exercise I studied the Makefile provided by the course and comment it,
just for the sake of documentation. This, but is an over-complicated Makefile
for this problem, and I tried to mimic the directory structure and
organization only to learn how these all are used to manage a larger project.

## Doxygen

Doxygen is a tool for creating nice documentation. It is used for many languages
and is not specific to the C++ language (Python, PHP and Java among many
others). The way it works is that you write documentation in your code in a
specific way, and create a config file for the Doxygen to follow, and then it
will create an HTML website for the documentation. It is useful for larger
object-oriented projects that have many layers of inheritance (for example, the
OpenFOAM framework/toolbox for computational fluid dynamics applications). The
following is some of the documentation that I used to create the documentation
for this project.

### Notes

- It is advised to not put the documentation comments only in the header files.
  comments in the implementation files are for the developer who actually edit
  those files.

- Create a config file:

  ```sh
  $ doxygen -g # Creates a file called 'Doxyfile' (With description comments)
  $ doxygen -s -g # Like above but without comment
  $ doxygen -g doxy_config.conf # Specify the name of the config file
  ```
  you can read description for each option to know more about them. There are,
  however a lot of them, but a handful of them are as follows:

  - `PROJECT_NAME = "My Project"`
  - `PROJECT_NUMBER = 0.1`
  - `OUTPUT_DIRECTORY = ../doc`
  - `ALWAYS_DETAILED_SEC = YES` -> lazy
  - `INLINE_INHERITED_MEMB = YES`
  - `EXTRACT_ALL = YES`
  - `EXTRACT_PRIVATE = YES`
  - `EXTRACT_STATIC = YES`
  - `WARN_NO_PARAMDOC = YES` -> this helps fix broken documentation
  - `GENERATE_TREEVIEW = YES`
  - `PREDEFINED` -> related to preprocessor directive that affect documentation
  - `HIDE_UNDOC_RELATIONS = NO`
  - `CALL_GRAPH` -> graph of functions that are called inside the documented function
  - `CALLER_GRAPH` -> graph of functions that call the documented function

- You start documenting your functions, classes or whatnot with some sort of
doc block ([documentation](https://www.doxygen.nl/manual/docblocks.html))
  ```c
  /**
   * ... Javadoc style ...
   */

  /*!
   * ... Qt style ...
   */

  ///
  /// ... text ...
  ///

  //!
  //!... text ...
  //!

  /********************************************//**
   *  ... text
   ***********************************************/

  /////////////////////////////////////////////////
  /// ... text ...
  /////////////////////////////////////////////////

  /************************************************
   *  ... text
   ***********************************************/
  ```
- Use following to help Doxygen

  ```c

  /*! \brief Brief description.
   *         Brief description continued.
   *
   *  Detailed description starts here.
   *  You have to set the following in your config
   *  BRIEF_MEMBER_DESC      = YES
   */
  void function();
  ```

  ```cpp
  /* A dummy class */
  class Test
  {
  };
  /*! \class Test class.h "inc/class.h"
   *  \brief This is a test class.
   *
   * Some details about the Test class. syntax
   *
   * \class <name> [<header-file>] [<header-name>]
   */
  ```

  ```cpp
  /*! \class Par_Test
   * Normal text.
   *
   * \par User defined paragraph:
   * Contents of the paragraph.
   *
   * \par
   * New paragraph under the same heading.
   *
   * \note
   * This note consists of two paragraphs.
   * This is the first paragraph.
   *
   * \par
   * And this is the second paragraph.
   *
   * More normal text.
   */
  class Par_Test {};
  ```

  ```c
  /*!
   * Copies bytes from a source memory area to a destination memory area,
   * where both areas may not overlap.
   * @param[out] dest The memory area to copy to.
   * @param[in]  src  The memory area to copy from.
   * @param[in]  n    The number of bytes to copy
   */
  void memcpy(void *dest, const void *src, size_t n);
  ```

- Brief description (They also show up when hovering over names)

  ```cpp
  /*! \brief Brief description.
   *         Brief description continued.
   *
   *  Detailed description starts here.
   */

  // -------

  /** Brief description which ends at this dot. Details follow
   *  here.
   */

  // -------

  /// Brief description which ends at this dot. Details follow
  /// here.

  // -------

  /// Brief description.
  /** Detailed description. */

  // -------

  //! Brief description.

  //! Detailed description
  //! starts here.
  ```

- Put documentation after members

  ```cpp
  int var; /*!< Detailed description after the member */

  int var; /**< Detailed description after the member */

  int var; //!< Detailed description after the member
           //!<

  int var; ///< Detailed description after the member
           ///<

  int var; //!< Brief description after the member

  /// Brief description after the member
  int var;

  void foo(int v /**< [in] docs for input parameter v. */);
  /**
   Note that these blocks have the same structure and meaning as the special
   comment blocks in the previous section only the < indicates that the member is
   located in front of the block instead of after the block.
  */
  ```

- Add a section for exception in your function Documentation
  read more about ([special commands](https://www.doxygen.nl/manual/commands.html))

  ```
  \exception std::runtime_error If the key-value pair cant be found in the table
  it will throw an exception
  ```

- You can use HTML syntax
  ([documentation](https://www.doxygen.nl/manual/htmlcmds.html)):

  ```html
  <code>std::ostream</code>
  <a href="https://en.wikipedia.org/wiki/Hash_function">Hash function</a>
  ```

- You can also use the Markdown syntax
  ([documentation](https://www.doxygen.nl/manual/markdown.html))

  ```markdown
  `std::ostream`

  [Hash table](https://en.wikipedia.org/wiki/Hash_table)
  ```

- You can write math (in \TeX\).
    Remember to enable `USE_MATHJAX = YES`, and disable `FORMULA_TRANSPARENT =
    NO` in your Doxyfile.

  ```
  \f$\frac{x^2 + 7x + 5}{x + 1}\f$

  \f[
    \frac{\partial \rho}{\partial t} + \frac{\partial(\rho u_{i})}{\partial x_{i}} = 0
  \f]
  ```

- Finally remember to create you documentation ;)

  ```sh
  doxygen <path to config file>
  xdg-open doc/html/index.html # view documentation in the default browser
  ```
- Here's an example snippet from this exercise

  ```cpp
    /**
     * @brief Compute the hash of a given string (hash function)
     * @param key the key for which it computes hash code
     * @return a hash code (might be unique, or not)
     *
     * If the size of your hash table is small your going to have a lot of hash
     * code collisions
     *
     * \par
     * since `hash_val` is an `unsigned` type we can just ignore overflows
     * (overflow is well-defined for unsigned types)
     *
     * \par
     * Because we need a value between `0` and `size - 1`, we take the
     * remainder of division by table's size
     */
    size_t hash(const std::string &key) {
        size_t hash_val = 5381;  // have a nice prime number
        for (const char c : key) {
            hash_val = hash_val * 33 + c;
        }
        return hash_val % data.size();
    }
  ```
- Other examples:

  ```cpp
  /**
   *  A test class. A more elaborate class description.
   */

  class Javadoc_Test
  {
    public:

      /**
       * An enum.
       * More detailed enum description.
       */

      enum TEnum {
            TVal1, /**< enum value TVal1. */
            TVal2, /**< enum value TVal2. */
            TVal3  /**< enum value TVal3. */
           }
         *enumPtr, /**< enum pointer. Details. */
         enumVar;  /**< enum variable. Details. */

        /**
         * A constructor.
         * A more elaborate description of the constructor.
         */
        Javadoc_Test();

        /**
         * A destructor.
         * A more elaborate description of the destructor.
         */
       ~Javadoc_Test();

        /**
         * a normal member taking two arguments and returning an integer value.
         * @param a an integer argument.
         * @param s a constant character pointer.
         * @see Javadoc_Test()
         * @see ~Javadoc_Test()
         * @see testMeToo()
         * @see publicVar()
         * @return The test results
         */
         int testMe(int a,const char *s);

        /**
         * A pure virtual member.
         * @see testMe()
         * @param c1 the first argument.
         * @param c2 the second argument.
         */
         virtual void testMeToo(char c1,char c2) = 0;

        /**
         * a public variable.
         * Details.
         */
         int publicVar;

        /**
         * a function variable.
         * Details.
         */
         int (*handler)(int a,int b);
  };
  ```

## References

1. [Hash function](https://en.wikipedia.org/wiki/Hash_function)
2. [Hash table](https://en.wikipedia.org/wiki/Hash_table)
3. [Linear probing](https://en.wikipedia.org/wiki/Linear_probing)
4. [Doxygen Documentation](https://www.doxygen.nl/manual/)
5. [YouTube tutorial on Doxygen](https://youtu.be/5G1zUpNFmEY)
6. [Tutorial on Doxygen](https://embeddedinventor.com/doxygen-tutorial-getting-started-using-doxygen-on-linux/)
