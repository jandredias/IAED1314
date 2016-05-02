#!/bin/bash
# Script teste

echo "***************************"
echo "***** BEGIN OF SCRIPT *****"
echo "***************************"
echo "Downloading..."
git clone git@github.com:pcdiasmega/IAED-proj1.git
echo "Extracting..."
mv IAED-proj1/* ./
echo "Deleting files..."
rm -rf IAED-proj1
echo "Compiling..."
gcc -ansi -Wall -pedantic -o proj1 proj.c

echo "Running Test 01..."
./proj1 <test01.in> test01.myout
diff test01.out test01.myout

echo "Running Test 02..."
./proj1 <test02.in> test02.myout
diff test02.out test02.myout

echo "Running Test 03..."
./proj1 <test03.in> test03.myout
diff test03.out test03.myout

echo "Running Test 04..."
./proj1 <test04.in> test04.myout
diff test04.out test04.myout

echo "Running Test 05..."
./proj1 <test05.in> test05.myout
diff test05.out test05.myout

echo "Running Test 06..."
./proj1 <test06.in> test06.myout
diff test06.out test06.myout

echo "Running Test 07..."
./proj1 <test07.in> test07.myout
diff test07.out test07.myout

echo "Running Test 08..."
./proj1 <test08.in> test08.myout
diff test08.out test08.myout

echo "*************************"
echo "***** END OF SCRIPT *****"
echo "*************************"
