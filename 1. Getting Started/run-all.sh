for dir in $(ls -d 0*); do
    make \--directory=${dir} clean
    make \--directory=${dir}
    make \--directory=${dir} run &
    sleep 5
    kill \-KILL $(pidof main)
    make \--directory=${dir} clean
done
