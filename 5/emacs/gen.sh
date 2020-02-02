./gen 100 100 1000 1 > test/emacs.in.1
./gen 100 95 1000 1 > test/emacs.in.2

./gen 1 100 1000 0 > test/emacs.in.3
./gen 1 100 1000 0 > test/emacs.in.4
./gen 1 95 1000 0 > test/emacs.in.5

./gen 100 100 1000 0 > test/emacs.in.6
./gen 100 100 10000 0 > test/emacs.in.7
./gen 95 100 1000 0 > test/emacs.in.8
./gen 100 95 1000 0 > test/emacs.in.9
./gen 100 100 1 2 > test/emacs.in.10

for i in {1..10}; do ./paula < test/emacs.in.$i > test/emacs.out.$i; done
