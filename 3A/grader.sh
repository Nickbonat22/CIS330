#!/bin/ksh

ID="3A"
PROJ_DIR="/home/users/hank/public_html/330/projects/3A"
OUTPUT_NAME="3A_output.pnm"
CORRECT_OUTPUT="${PROJ_DIR}/${OUTPUT_NAME}"
INPUT="${PROJ_DIR}/3A_input.pnm"
EXEC_NAME="proj${ID}"

#Check that an input file was provided to this script
if [[ $# != 1 ]] ; then
   echo "Usage: $0 <c file>"
   exit 1
fi

#Check that the program compiles 
gcc -o $EXEC_NAME $1
if [[ $? != 0 ]] ; then
   echo "Compile failure!"
   exit 1
fi

#Run the executable with the input and output
./$EXEC_NAME $INPUT $OUTPUT_NAME

#Check for correct output
diff $CORRECT_OUTPUT ./$OUTPUT_NAME
if [[ $? != 0 ]] ; then
   echo "Your output image is not correct."
   exit 1
fi

echo "Your program appears to be working correctly."
echo "It compiles, runs, and generates the correct output."
echo "Please upload your code to Canvas, following the instructions in the ${ID} prompt."
echo "Grading will consist of the steps performed by this script, complemented by inspection of your code."

