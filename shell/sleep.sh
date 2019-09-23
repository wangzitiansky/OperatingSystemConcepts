echo Count:
#存储光标位置
tput sc

for count in `seq 0 40`
do
#恢复光标位置
    tput rc
#删除整行内容
    tput ed
    echo -n $count
    sleep 1
done

