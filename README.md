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

2. **Linux:**

   + Modify Makefile *(line 27-31)*:

     + Replace all matlab location to your matlab location
     + Replace *START_DIR* to code location

     ```bash
     MATLAB_ROOT               = /usr/local/MATLAB/R2015b
     MATLAB_BIN                = /usr/local/MATLAB/R2015b/bin
     MATLAB_ARCH_BIN           = /usr/local/MATLAB/R2015b/bin/glnxa64
     MASTER_ANCHOR_DIR         = 
     START_DIR                 = /home/allen/HW3_2
     ```

   + Build static library *(generate BayesCurFit.a)*:

     ```bash
     make
     ```

   + Build executable file:

     ``` bash
     gcc main.c BayesCurfit.a -lm -fopenmp -o Bayes
     ```

3. **MacOS:**

   + TBD



### How To Execute

``` bash
./Bayes {x_input_file} {t_input_file} {size} {order} {x_to_predict}
```

example:

![](https://cl.ly/3u1W2M031840/Bayes_result.png)



