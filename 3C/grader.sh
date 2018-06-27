#!/bin/ksh

if [[ "$(hostname)" != "ix-dev" ]] ; then
    echo "You must run this script on ix-dev"
    exit 1
fi

ID="3C"
PROJ_DIR="/home/users/hank/public_html/330/projects/3C"
OUTPUT_NAME="3C_out.pnm"
CORRECT_OUTPUT="${PROJ_DIR}/${OUTPUT_NAME}"
INPUT="${PROJ_DIR}/3C_input.pnm"
EXEC_NAME="proj${ID}"

#Check that an input file was provided to this script
if [[ $# != 1 ]] ; then
   echo "Usage: $0 <tar file>"
   exit 1
fi

if [[ ! -f $1 ]] ; then
   echo "Cannot find tarfile $1"
   exit 1
fi

rm -Rf tmp
mkdir tmp
cd tmp
tar xvf ../$1 
cp $PROJ_DIR/Makefile .
cp $PROJ_DIR/main3C.C .
make
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
echo "Please upload your tarball to Canvas, following the instructions in the ${ID} prompt."
echo "Grading will consist of the steps performed by this script, complemented by inspection of your code."

