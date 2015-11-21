- 10.1 Input and ouptut
- 10.2 The I/O stream model
  - `input / output < -- > [io]stream < -- > buffer < --- > somewhere...`
- 10.3 Files
- 10.4 Opening a file
- 10.5 Reading and writing a file
  - 10-05.cpp // TODO: compile it
- 10.6 I/O error handling
  - good()
  - eof()
  - fail() // we might want to retrieve from there with clear()
  - bad() // really!
- 10.7 Reading a single value
  - Breaking the problem into manageable parts
  - Separating dialog from function
  - 10-07.cpp // does not compile
- 10.8 User-defined output operators
  - 10-08.cpp // cuold comppile
- 10.9 User-defined input operators
  - 10-08.cpp // cuold comppile
- 10.10 A standard input loop
- 10.11 Reading a structured file
  - "but the reality is still that we can rarely control the input format offered by the files we need to read."  
    Try to use standard formats and libraries as much as possible! (csv, xml, json, ...)
- 10.11.1 In-memory representation
- 10.11.2 Reading structured values
  - cf. Qt and Json
- 10.11.3 Changing representations

# Review

1. When dealing with input and output, how is the variety of devices dealt with in most modern computers?
2. What, fundamentally, does an istream do?
3. What, fundamentally, does an ostream do?
4. What, fundamentally, is a file?
5. What is a file format?
6. Name four different types of devices that can require I/O for a program.
7. What are the four steps for reading a file? (g?)
   - xabj vgf anzr
   - bcra vg
   - ernq va
   - pybfr vg
8. What are the four steps for writing a file? (g?)
   - anzr vg
   - bcra vg
   - jevgr bhg
   - pybfr vg
9. Name and define the four stream states.
  - tbbq
  - rbs
  - snvy
  - onq
10. Discuss how the following input problems can be resolved:
    - The user typing an out-of-range value
    - Getting no value (end of file)
    - The user typing something of the wrong type
11. In what way is input usually harder than output?
12. In what way is output usually harder than input?
13. Why do we (often) want to separate input and output from computation?
14. What are the two most common uses of the istream member function clear()?
15. What are the usual function declarations for << and >> for a user-defined type X?
