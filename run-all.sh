cd '1. Getting Started'
for dir in $(ls -d *); do
    cd ${dir}
    make clean
    make
    make run &
    sleep 8
    kill \-KILL $(pidof main)
    cd ..
done
cd ..