TASK=lampice

rm test/$TASK.{in,out}.*

./gen 100 350 2 simple-simple > test/$TASK.in.1a
./gen 101 777 3 simple-reverse > test/$TASK.in.1b
./gen 102 1509 5 deep-reverse > test/$TASK.in.1c
./gen 103 2222 26 deep-longpalin > test/$TASK.in.1d
./gen 104 1 1 simple-simple > test/$TASK.in.1e
./gen 105 2 1 simple-simple > test/$TASK.in.1f
./gen 106 2 2 simple-simple > test/$TASK.in.1g

./gen 200 43333 2 chain-simple > test/$TASK.in.2a
./gen 201 44444 2 chain-reverse > test/$TASK.in.2b
./gen 202 45555 10 chain-longpalin > test/$TASK.in.2c
./gen 203 47777 26 chain-longpalin > test/$TASK.in.2d
./gen 204 49999 8 chain-reverse > test/$TASK.in.2e
./gen 205 49994 1 chain-simple > test/$TASK.in.2f

./gen 300 45111 2 simple-simple > test/$TASK.in.3a
./gen 301 45222 5 simple-simple > test/$TASK.in.3b
./gen 302 45333 7 simple-reverse > test/$TASK.in.3c
./gen 303 45444 10 deep-reverse > test/$TASK.in.3d
./gen 304 45555 8 shallow-simple > test/$TASK.in.3e
./gen 305 46666 17 deep-longpalin 6 > test/$TASK.in.3f
./gen 306 47777 6 deep-longpalin 10 > test/$TASK.in.3g
./gen 307 48888 2 deep-reverse 4 > test/$TASK.in.3h
./gen 308 49999 5 deep-simple > test/$TASK.in.3i
./gen 309 48888 1 deep-simple > test/$TASK.in.3j
./gen 310 49998 4 deep-reset 50 20 > test/$TASK.in.3k
./gen 311 48899 10 deep-reset 4 10 > test/$TASK.in.3l
./gen 312 47777 26 deep-reset 10 100 > test/$TASK.in.3m 

for i in {a..g}; do time ./lampice < test/$TASK.in.1$i > test/$TASK.out.1$i; done
for i in {a..f}; do time ./lampice < test/$TASK.in.2$i > test/$TASK.out.2$i; done
for i in {a..m}; do time ./lampice < test/$TASK.in.3$i > test/$TASK.out.3$i; done
