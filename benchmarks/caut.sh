#!/bash/sh

SRC_FILE_NAME=$1
UNIT_NAME=$2
SRC_PART_NAME=${1%.c}
SRC_FILE_DIR=${1%/*}
CIL_PATH=../cil/

echo "->caut init..."
echo "remove old files..."
rm -rf $SRC_FILE_NAME.db $SRC_PART_NAME.cil.orig.c $SRC_PART_NAME.cil.c

echo "->preprocess file..."
gcc -E -I ../ $SRC_FILE_NAME > $SRC_PART_NAME.i

echo "->extract cfg info and insert cover function --> P"
$CIL_PATH/cilly.byte.exe --noInsertImplicitCasts --useLogicalOperators --domakeCFG --docautcover -file $SRC_FILE_NAME -bc 1 --out $SRC_PART_NAME.cil.orig.c $SRC_PART_NAME.i



#echo "-> insert runtime interfaces --> P' (coverage-driven testing + unit testing level)"
#$CIL_PATH/cilly.byte.exe --domakeCFG --no-split-structs --dotcg -cffile $SRC_FILE_NAME -cfunit $UNIT_NAME --unit_testing --out $SRC_PART_NAME.cil.c $SRC_PART_NAME.i > $SRC_PART_NAME.append


echo "-> insert runtime interfaces --> P' (program testing level + branch testing)"
echo "Remove Old Files..."
rm -rf ${SRC_FILE_DIR}/obj-df-data
echo "Call CIL to Analyze..."
$CIL_PATH/cilly.byte.exe --domakeCFG --no-split-structs --dotcg -cffile $SRC_FILE_NAME --interp_br_testing --out $SRC_PART_NAME.cil.c $SRC_PART_NAME.i > $SRC_PART_NAME.append
echo "Everything is Ready..."
mkdir ${SRC_FILE_DIR}/obj-df-data
mv ${SRC_FILE_DIR}/*.txt ${SRC_FILE_DIR}/obj-df-data


echo "->append code..."
cat $SRC_PART_NAME.append >> $SRC_PART_NAME.cil.c

#comment "#line" line
sed -i "s/\#line/\/\/\#line/g" $SRC_PART_NAME.cil.c
sed -i "s/\#line/\/\/\#line/g" $SRC_PART_NAME.cil.orig.c

echo "->add caut header file \"caut.h\""
sed -i "1 i\\#include \"caut.h\"" $SRC_PART_NAME.cil.c
