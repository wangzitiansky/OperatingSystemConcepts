start=$(date +%s)
commands;
statements;
end=$(date +%s)
difference=$((end - start))
echo Time takend to execute commands is $difference seconds.
