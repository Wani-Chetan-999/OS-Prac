echo "Hello World";
touch addressbook.txt
touch com1.txt

read rInput
grep -n "$rInput" addressbook.txt
echo "Enter line no to remove"
	read lineNumber
	for line in `grep -n "$rInput" addressbook.txt`
	do
		number=`echo $line|cut -c1`
		if [ $number -eq $lineNumber ]
		then
		echo -e "${lineNumber}d" > com1.txt
		echo -e "\nThe record was removed from the address book and remaining Record is\n"
		sed -f com1.txt addressbook.txt
		fi
	done