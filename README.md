# Software Engineering: Web Applications 2017 SPRING

*name:Weiqing Ni		netID: wn61*

## BayesBurFit

### Supported platform:

+ Windows
+ Linux
+ MacOS (*Require Xcode, to be verified*)

### How To Build

1. **Windows:**

   + Open Visual Studio/ CodeBlocks, create new console application project.
   + Import all files into project
   + Build

2. **Linux/ Cygwin on Windows:**

   + Build static library *(generate BayesCurFit.a)*:

     ``` bash
     cd Linux/BayesCurFit
     make
     ```


   + Build executable file:

     ``` bash
     gcc main.c BayesCurFit.a -lm -fopenmp -o Bayes
     ```

3. **MacOS:**

   + TBD



### How To Execute

``` bash
./Bayes {x_input_file} {t_input_file} {size} {order} {x_to_predict}
```

example:

![](https://cl.ly/3u1W2M031840/Bayes_result.png)



