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
| Argument       | Description                   | Default Value |
|----------------|-------------------------------|---------|
| `-query`       | Path to query file            | `data/SRR7236689--ARG830.fa`
| `-subject`     | Path to data file             | `data/Gn-SRR7236689_contigs.fasta`
| `-out`         | Output file                   | `result.txt`
| `-sep`         | Query / subject seperator     | `>`
| `-word-length` | Word length                   | `11`
| `-sw-minscore` | Smith Waterman min score      | `20`
| `-sw-match`    | Smith Waterman match score    | `2`
| `-sw-mismatch` | Smith Waterman mismatch score | `-3`
| `-sw-gap`      | Smith Waterman gap score      | `-1`
| `-dust-thresh` | Dust threshold                | `0.1`
| `-dust-length` | Dust pattern length           | `3`
| `-lambda`      | E-value lambda constant       | `0.267`
| `-kappa`       | E-value kappa constant        | `0.041`
| `-test`        | Expects `dust`, `extend`, `match`, `pairs`, `sequence`, `sw` or `smith waterman`, `sort`, `split` | NA
