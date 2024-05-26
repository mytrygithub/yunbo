
#!/bin/bash

sh clean_test_dir.sh

mkdir -p only_file_in_path
touch only_file_in_path/filenamea.stp
touch only_file_in_path/filenameb.stp

mkdir -p empty

mkdir -p not_exist_suffix
touch not_exist_suffix/filename1.so
touch not_exist_suffix/filename1.txt
touch not_exist_suffix/filename1.zip

#mdir not_exist_dir

touch dir_is_a_file

mkdir -p not_permissions
sudo chown 600 not_permissions

mkdir -p have_dir_in_path/dir1
touch have_dir_in_path/filenamea.stp
touch have_dir_in_path/filenameb.stp
