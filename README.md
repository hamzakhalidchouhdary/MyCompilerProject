# MyCompilerProject
A NoSQL to SQL query compiler
### BACKGROUND
When I was studying 7th semester of my BS I got oppurtunity to study compiler constructure. That was very interesting course in have ever had entire my acdemic life this course helped me to apply data strctures and thoery of computation to solve a problem. I hited an idea to write a compiler that can translate NoSQL to SQL queries.
### Overview
This basic translator takes functions conected statement and convert into SQL query. If some syntax error recognize then just notify and error message.
### Berif Work-flow of Compiler
Compiler is a special type of software that predefined gramminacal statements and translate them into pre programmed language. Any Compiler works in following layers
- Lexical Analysis
- Syntax Analysis
- Semantic Analysis
- Translation
- Code Optimization

#### Statement Syntax
The input statement syntax is following:
```
tableName.coreOperationToBePerformed().optionalOperationToBePerformed()
```
Simple Example reading all user less 25 years and unmerried will be:
```
User.read().filter(age < 25 & meritalStatus != merried);
```
