lista=()
while [[ $1 != "" ]]; do
  echo $1
  echo ${lista[@]}
  lista=( "$1" "${lista[@]}" ); shift; done
#echo "${lista[@]}"