# Topics proposals for the C++ intermadiate Co-learning

## plan

- 17.05.2016: doxygen by delf
- 24.05.2016: introduction to design patterns by christian (+ instructions on compiling scribus by ale)
- 1?.6.2016: exporting to epubepub

## ale

- http://www.modernescpp.com/index.php has a few articles on multithreading (http://www.modernescpp.com/index.php/tag/threads)
- go through (and try out) the changes in C++ 14: https://en.wikipedia.org/wiki/C%2B%2B14
- [modern c++ features: C++11/14/17](https://github.com/AnthonyCalandra/modern-cpp-features)
- check [clang-tidy](http://clang.llvm.org/extra/clang-tidy/) for code analysis
- lift (aufzug) programmieren
- going through [THE WAYS TO AVOID COMPLEXITY IN MODERN C++](http://vitiy.info/Slides/MeetingCPP2015/MeetingCPP2015Complexity.pdf)
- go throug (parts of) the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- scribus als projekt:
  - markdown export / import mit formelle grammatik (generierte c library)
    - https://github.com/aoloe/scribus-plugin-gettext-markdown-2
    - using the `greg` parser generator:
      - using `markdown_parser.leg`
      - generating a `c` library that has to bound to c++ "events"
  - epub export
    - https://github.com/aoloe/scribus-plugin-export-epub
    - it already creates a zip file (that's epub...) with all the needed files with some basic html in there
    - needs a css file with the matching styles
    - needs an heuristic for placing and resizing images
    - needs an heuristic for placing the text in the right order
  - python scripting in c++ applikation einbinden
    - currently uses a(n unmaintained) fork of the `kross` engine (formerly?) used by kde
    - it compiles but fails at runtime: it's stuck at getting the signals and slots to cross the boundaries
    - create a basic scripting engine for integrating python inside of a c++ program
    - create a scripting engine that can work with qt on boths c++ and python side
- inkscape als projekt
- lambdas:
  - <http://maitesin.github.io//Lambda_comparison/ and https://news.ycombinator.com/item?id=11697951>
- folds (`...`):
  - http://en.cppreference.com/w/cpp/language/fold
- memory analysis / leeks with valgrind
- high level critical view on real world code snippets: http://www.viva64.com/en/b/0391/
- dependency management with conan https://www.conan.io/ (cf. slides for presentation on the 28 may 2016 @ metalab wiki / c++ user group)
- [more c++ idioms](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms)
- [libui](https://github.com/andlabs/libui) is a simple UI library that interfaces with GTK, OS X or Windows, depending on your operating system.
- deep learning framework: <https://github.com/nyanp/tiny-cnn>
- machin learning: <http://mlpack.org/>
- mutex:
  - read and write locks:
    - http://stackoverflow.com/questions/19915152/c11-multiple-read-and-one-write-thread-mutex
    - with a proper c++ 14 example and one that works with c++ 11
- create a light weight web / documentation / epub browser based on [libui](https://github.com/andlabs/libui) / [litehtml](https://github.com/litehtml/litehtml) (using [litebrowser-linux](https://github.com/litehtml/litebrowser-linux/) as an example)
- library for 3D world generation based on open street map: <https://github.com/reinterpretcat/utymap>
- a wrapper around curl: <https://github.com/whoshuu/cpr>
- [Modern Memory Safety: C/C++ Vulnerability Discovery, Exploitation, Hardening](https://github.com/struct/mms)
- implement a buzz fizz language
  - by understanding this python example <https://www.promptworks.com/blog/the-fastest-fizzbuzz-in-the-west?utm_source=python&utm_medium=reddit&utm_campaign=FizzBuzz>
  - here a rply implementation in c++: <https://gist.github.com/pranavkantgaur/f301fd064f7ba444d41a>
  - and what rply is: http://w3.impa.br/~diego/software/rply/
  looks like a cool introduction to parsing!
- embed lua into c++:
  - https://github.com/vinniefalco/LuaBridge
  - https://github.com/progschj/luacpp11
- using range based loops: auto, const & & <https://blog.petrzemek.net/2016/08/17/auto-type-deduction-in-range-based-for-loops/>
- [c++ koans](https://github.com/torbjoernk/CppKoans): learning c++ by making tests pass.  
  other koans:
  - http://www.yeradis.com/2014/09/29/koans/
  - https://github.com/bkleinen/CPPKoans
  - https://github.com/sensorflo/cppkoans
- Making your class "move enabled": https://www.oreilly.com/ideas/2-major-reasons-why-modern-c-is-a-performance-beast
- Implementing a renderer (OpenGL clone) in 500 LOC: https://github.com/ssloy/tinyrenderer/wiki
- explore [drakon](http://drakon-editor.sourceforge.net/), a visual language for specifications that can generate code
  - http://drakon-editor.sourceforge.net/cpp/cpp.html
  - http://drakon-editor.sourceforge.net/cpp.pdf
- [Reclaiming Data Structures with Cycles](https://www.justsoftwaresolutions.co.uk/cplusplus/reclaiming-data-structures-with-cycles.html) ("garbage collection" in c++)
- uml and c++: <https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/
- pub quiz:
  - http://www.pvv.org/~oma/PubQuiz_CPP_Oct2011.pdf
  - http://cppquiz.org/
- [Demystifying constexpr](http://blog.quasardb.net/demystifying-constexpr/)
- [Lambda Magic](https://adishavit.github.io/2016/magical-captureless-lambdas/)
- [Leaky 🕳 Lambdas](https://adishavit.github.io/2016/leaky-closures-captureless-lambdas/)
- [Default Constructed Return Value: return {}](https://adishavit.github.io/2015/default-constructed-return-value-return/)
- [c++ 17 and Polymorphism](https://adishavit.github.io/2016/polymorphism-polymorphism/)
- read articles from [overload magazine](https://accu.org/index.php/journals/c78/)
- [Using data structures and algorithms in C++ using STL](http://www.techiedelight.com/data-structures-and-algorithms-interview-questions-stl/)
- [is the preprocessor still needed in c++?](http://foonathan.net/blog/2017/05/08/preprocessor.html) and [HN](https://news.ycombinator.com/item?id=14290051) (für luzern?)
- [C++ Error Handling: Why Use Eithers in Favor of Exceptions and Error-Codes](https://hackernoon.com/error-handling-in-c-or-why-you-should-use-eithers-in-favor-of-exceptions-and-error-codes-f0640912eb45) and [HN thread](https://news.ycombinator.com/item?id=14356036)
- have a look at [jakob's threads pool implementation](https://github.com/progschj/ThreadPool/) (using c++ 11 threads instead of pthreads; and compare to <https://github.com/leohotfn/Reuzel>)
- expore c++ 17: https://github.com/tvaneerd/cpp17_in_TTs/blob/master/ALL_IN_ONE.md


## katrin

- uml
- projects:
  - notepadqq


## delf

- interface to R
- doxygen
- profiling
- clang tools for error analyzing
- designing an std alike algorithm
- how to define an API
- concurrency / parallel computing
- c++ for android
- network programming

## christian

- spezifikationen
- design patterns mit head first
  - https://hfdpcpp.codeplex.com/
- computational statistics
- compiling with debug symbols + `ddd` for debugging

# richard
  - `boxbackup`
    - get the gui into shape
