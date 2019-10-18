# C++ Blastn
Run Blastn on specified data. For the example data, the extend step may take around 30 minutes to execute, however all other steps are relatively fast.
## Building
### Windows
  * Open `Blastn.sln` in Visual Studio 2019.
  * Visual Studio Setup
    * Open project properties
    * On the top, select `Configuration: All Configurations`
    * On the top, select `Platform: All Platforms`
    * Go to `C/C++ -> Optimization`
      * Select `Optimization: Maximum Optimization (Favor Speed) (/O2)`
      * Select `Favor Size or Speed: Favor Fast Code (/Ot)`
    * Go to `C/C++ -> Preprocessor`
      * Select `Preprocessor Definitions: <Edit...>`
        * In definitions, enter `_CRT_SECURE_NO_WARNINGS`
        * This allows for the timestamp system to work as `<ctime>` is used.
    * Go to `C/C++ -> Language`
      * Select `C++ Language Standard: ISO C++17 Standard (/std:c++17)`
  * On the top, specify `Release`, `x64`, and press `Ctrl + Shift + B` to build.
  * The generated executable will be `x64\Release\Blastn.exe`.
### Mac and Linux
  * In the `cpp` directory, run the `make` command.
  * The generated binary will be `blastn`.

## Command Line Arguments
| Argument | Description                   | Default |
|----------|-------------------------------|---------|
| `-q`     | Path to query file            | Yes
| `-db`    | Path to data file             | Yes
| `-sp`    | Query / data name seperator   | `>`
| `-l`     | Word length                   | `11`
| `-m`     | Smith Waterman min score      | Yes
| `-ma`    | Smith Waterman match score    | `2`
| `-mi`    | Smith Waterman mismatch score | `-3`
| `-g`     | Smith Waterman gap score      | `-1`
| `-dt`    | Dust threshold                | Yes
| `-dl`    | Dust pattern length           | `3`
| `-o`     | Output file                   | `blastn_out.txt`
| `-test`  | Expects `dust`, `extend`, `match`, `pairs`, `sequence`, `sw` or `smith waterman`, `sort`, `split` | NA
