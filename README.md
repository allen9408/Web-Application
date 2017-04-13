# Software Engineering: Web Applications 2017 SPRING

*name:Weiqing Ni		netID: wn61*

## BayesBurFit

More details on [Github](https://github.com/allen9408/Web-Application).  

#### Supported platform:

+ Windows
+ Linux
+ MacOS (*Require Xcode, to be verified*)

#### How To Build

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

     ```bash
     gcc main.c BayesCurFit.a -lm -fopenmp -o Bayes
     ```

3. **MacOS:**

   + TBD


#### How To Execute

``` bash
./Bayes {x_input_file} {t_input_file} {size} {x_to_predict}
```

example:

![](https://cl.ly/3u1W2M031840/Bayes_result.png)



## Get Stock Information From Yahoo Finance

#### Configure for MYSQL

**GetStock/CreateDatabase.php  &&  GetStock/ImportData.php**

Modify username and password according to your configuration for mySQL:

```php
$username = "root";
$password = "";
```

#### How To Execute

```bash
cd GetStock
# Get history information
php getHistory.php
# Get real time information
php getReal.php
# Create database
php CreateDatabase.php
# Import data to database
php ImportData.php
# Output database tables
php showDatabase.php
# Clear tables
php clearTable.php
```

#### Stocks

| Code |  Company  |
| :--: | :-------: |
| GOOG |  Google   |
| YHOO |   Yahoo   |
| MSFT | Microsoft |
|  FB  | Facebook  |
| CCF  |   Chase   |

#### Results

Find history data in `./GetStock/hist_data/{Code}-{Time}.csv`.

Find real-time data in `./GetStock/real_data/{Code}-{Time}.csv`.

#### Known Issues

+ Timestamp is different due to different API.

+ Warning fixes

  ​

## HW5/BackPropagation

**Compile and run:**

```bash
cd {DIR}
g++ bp.cpp -o bp
./bp {max_training_times} {target_error} {learning_rate}
```

## HW6/ TCP Server and Client

**Compile and Run:**

```bash
cd {DIR}
g++ server.cpp -o server
g++ client.cpp -o client
./server [port_num]
./client [server_IP] [port_num]
```

**Commands supported by the server:**

1. Get files

   `GET [filename]`

2. Bounce text

   `BOUNCE [text]`

3. Exit

   `EXIT`

   or

   `EXIT [exit_code]`

   ​





