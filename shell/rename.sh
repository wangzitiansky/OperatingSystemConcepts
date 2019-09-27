count=1;
for txt in `find . -iname '*.txt' -type f -maxdepth 1`
do
    new=txt-$count.${txt##*.}
    echo "Running $txt to $ new"
    mv "$txt" "$new"
    let count++
done

