# Python Blastn
## Running
* Install the `requirements.txt` file.
* Windows Arguments
  * Run `main.py` with Python 3 and specify arguments.
  * `-q <*.fa path>` The query fa file.
  * `-d <*.fasta path>` The data fasta file.
  * `-l <int>` The split length for words.
  * `-m <int>` The minimum Smith Waterman score before removing a word.
  * `-dt <float>` The minimum Dust score before removing a word.
  * `-ma <int>` The Smith Waterman score for a matching character.
  * `-mi <int>` The Smith Waterman score for a non-matching character.
  * `-g <int>` The Smith Waterman score for a gap character.
* Mac and Linux Arguments
  * Use the Windows arguments, or use the `blastn.sh` file.
  * Open and modify `blastn.sh` to specify named arguments.
    * Set `test` to `true` to use the test data set.
    * Set `test` to `false` to use the large data set.
  * Run `./blastn.sh`