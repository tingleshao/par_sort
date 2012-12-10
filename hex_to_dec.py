file_name = raw_input('Please enter file name, with extension: ');
arrayT = open(file_name, 'r');
arrayS = arrayT.read();
arraySS = arrayS.strip().split('\n');
array = [];
for stuff in arraySS:
	stuffs = stuff.strip().split(' ');
	for ele in stuffs:
		array.append(int(ele, 16));
		
print array

dec_file = open('dec_array.txt', 'w');
for ele in array:
	dec_file.write(str(ele));
	dec_file.write(" ");
	
print 'file saved into dec_array.txt'
dec_file.close();
arrayT.close();
