#!/bash/sh

SRC_FILE_NAME=$1
UNIT_NAME=$2
SRC_MAIN_NAME=${1%.c}
SEARCH=$3
ITER=$4


#echo testing object
echo $SRC_MAIN_NAME

#gen exe
make FILE=$SRC_MAIN_NAME

#run unit testing
#./$SRC_MAIN_NAME --file $SRC_MAIN_NAME.c --unit $UNIT_NAME --db $SRC_MAIN_NAME.c.db --dfs
#mv cover_status.txt $SRC_MAIN_NAME-dfs




