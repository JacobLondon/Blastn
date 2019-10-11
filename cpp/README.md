# C++ Blastn

## Building
* Windows
  * Open `Blastn.sln` in Visual Studio 2019.
  * On the top, specify `Release` and `x64`.
  * The generated executable will be `x64\Release\Blastn.exe`.
* Mac and Linux
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
