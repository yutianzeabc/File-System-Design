file_system: main.o group_link_operator.o inode_operator.o my_cd.o my_create.o my_format.o my_ls.o my_mkdir.o my_open_close.o my_read.o my_rmdir.o my_start_exit.o my_write.o term.o my_rm.o
	g++ -o file_system  main.o group_link_operator.o inode_operator.o my_cd.o my_create.o my_format.o my_ls.o my_mkdir.o my_open_close.o my_read.o my_rmdir.o my_start_exit.o my_write.o term.o my_rm.o
group_link_operator.o: group_link_operator.c c_operator.h fs.h
	gcc -c group_link_operator.c -o group_link_operator.o
inode_operator.o: inode_operator.c c_operator.h fs.h inode.h
	gcc -c inode_operator.c -o inode_operator.o
my_cd.o: my_cd.c c_operator.h fs.h inode.h
	gcc -c my_cd.c -o my_cd.o
my_create.o: my_create.c c_operator.h fs.h inode.h
	gcc -c my_create.c -o my_create.o
my_rm.o: my_rm.c c_operator.h fs.h inode.h
	gcc -c my_rm.c -o my_rm.o
my_format.o: my_format.c c_operator.h fs.h inode.h
	gcc -c my_format.c -o my_format.o
my_ls.o: my_ls.c c_operator.h fs.h inode.h
	gcc -c my_ls.c -o my_ls.o
my_mkdir.o: my_mkdir.c c_operator.h fs.h inode.h
	gcc -c my_mkdir.c -o my_mkdir.o
my_open_close.o: my_open_close.c c_operator.h fs.h inode.h
	gcc -c my_open_close.c -o my_open_close.o
my_read.o: my_read.c c_operator.h fs.h inode.h
	gcc -c my_read.c -o my_read.o
my_rmdir.o: my_rmdir.c c_operator.h fs.h inode.h
	gcc -c my_rmdir.c -o my_rmdir.o
my_start_exit.o: my_start_exit.c c_operator.h fs.h inode.h
	gcc -c my_start_exit.c -o my_start_exit.o
my_write.o: my_write.c c_operator.h fs.h inode.h
	gcc -c my_write.c -o my_write.o
term.o: term.cpp cmd.hpp cpp_operator.h
	g++ -c term.cpp -o term.o
main.o: main.cpp cmd.hpp cpp_operator.h c_operator.h
	g++ -c main.cpp -o main.o
clean:
	rm -rf *.o file_system
