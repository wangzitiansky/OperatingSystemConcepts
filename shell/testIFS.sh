data="name, gender, rollno, location"
oldIFS=$IFS
IFS=,
for item in $data
do
    echo Item:$item
done
IFS=$oldIFS
