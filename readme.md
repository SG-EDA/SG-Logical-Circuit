Logical Circuit
=============

Catalogue
-------------
* [中文文档](readme_cn.md)
* [Trigger document](tri_readme.md)

Documents
-------------
### Colon Expression

#### input
Setting the input line of the circuit (automatically defining a line variable)
```
input:A
```

#### output
Set the output line of the circuit (the existing line variable)
```
output:r
```

#### set
Set the value of the input line variable
```
set: A 1
```

#### load
Load a logical circuit script file (*. lc). It will be executed directly.
```
load:D:/test.lc
```

### Command

* **trueTable:** Running circuit with enumerating all inputs
* **statTable**  Running circuit with enumerating all inputs and trigger state
* **multiplexing:** Statistics of all line usage
* **gateNum:** Output the number of logic gates in the current circuit
* **stru:** Output of the current circuit structure (does not look good)
* **run:** Running Circuit with Current Input
* **clear:** Clear the current circuit
* **middleVar:** Running circuit and output all line values with Current Input
* **multiplexing:** Statistics of all line usage
* **resetTri** Reset all triggers with initial state of 0