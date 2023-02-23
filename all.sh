files=$(find *.c)
echo "compiling $files "
# gcc $files -o ./bin/cgpa
gcc *.c -o ./bin/cgpa

err=$?

if [ $err = 0 ]; then
    echo "running cgpa..."
    ./bin/cgpa
fi