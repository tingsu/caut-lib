#! /bin/sh

# This file is used to run branch testing at program level
# Usage: source this_file.sh $file_name_under_test $max_exec_iter_cnt $search_strategy

#file name
file_name_under_test=$1
exec_file_name=${1%.c}
exec_program_name=${exec_file_name##*/}
#the directory where the file under test locates
file_name_dir=${1%/*}
#the maximum iterations
max_exec_iter_cnt=$2
#the path search strategy
search_strategy=$3
#the param for the search strategy
search_strategy_param=$4

echo "Start branch testing"
echo $PWD
echo $file_name_dir
echo $exec_program_name

echo "remove old log files..."
rm -rf ${file_name_dir}/obj-df-log
sleep 1


#use /usr/bin/time to record the wall-clock time of the exectution
time_command="/usr/bin/time -f "%e""

function test_branch(){

		
		echo "branch testing."
		echo $1
		echo "log file name: branch_coverage.log"
		echo $search_strategy_param
		($time_command $exec_file_name --file $file_name_under_test --program_dir $file_name_dir --program_name $exec_program_name --iter $max_exec_iter_cnt --$1 $search_strategy_param 1>/dev/null) 2>> branch_coverage.log
		echo "ms" >> branch_coverage.log
		rm -rf *.cautlog *.lst
}


# test all duas under all strategies
if [ "$search_strategy" = "klee" ]; then
	test_branch "klee-rp-md2u"
elif [ "$search_strategy" = "crest" ]; then
	test_branch "crest-cfg"
elif [ "$search_strategy" = "random_path" ]; then
	test_branch "random"	
elif [ "$search_strategy" = "random_input" ]; then
	test_branch "random_input"		
elif [ "$search_strategy" = "pps" ]; then
	test_branch "pps"
fi

# store log info. into the directory ${file_name_dir}/obj-df-log"
echo "cp all log files into the directory "obj-df-log""
echo "Creating dir: ${file_name_dir}/obj-df-log"
sleep 1
mkdir ${file_name_dir}/obj-df-log
mv ${file_name_dir}/*.log ${file_name_dir}/obj-df-log
