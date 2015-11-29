# Setup

Add the following lines to your `.bashrc` file so then you should be able to call the command `processing-java` 
from the command line.
```
# path to the processing-java binary
export PATH=$PATH:/YOUR/PATH/TO/processing-3.0.1
```
# Build

Run the bash script `buil-processing.sh`. It should generate the java code and bytecode inside the folder `bytecode-out`
and run the java process for that bytecode.

