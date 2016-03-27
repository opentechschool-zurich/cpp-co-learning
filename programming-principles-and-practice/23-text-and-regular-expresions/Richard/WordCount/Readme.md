# Word Count exercise from [exercism.io](http://exercism.io/exercises/cpp/word-count/readme)

Write a program that given a phrase can count the occurrences of each word in that phrase.

Implementation notes: 

We have a function
```cpp
map<string, int> countWords(string inputText)
```
 We create a `map<string, int>`
 
 Then we create an istringstream
 
 and read a word from it. This word we then try to insert into our map and get a somewhat complicated iterator back:
 
 `auto ret = wordMap.insert(pair<string, int>(s, 1));`
 
 This iterator is a pair of a map entry and a boolean. The boolean tells us whether the insert happened or whether the word already existed in the map.
 
 So, if the second of the pais is false the word already exists. Then we want to increment the word count of the map entry that we find in the first of the return.
 This first is another pair so we know the word (key) is in the "first" and the count is in the "second". So we need to increment the count of the second.
 
 
