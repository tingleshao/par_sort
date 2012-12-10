arrayT = open('array.txt', 'r');
array = [];
arrayS = arrayT.read();
arraySS = arrayS.split("\n");
for stuff in arraySS:
	stuffs = stuff.split(" ");
	for ele in stuffs:
		array.append(int(ele));
		
print array

arrayH = []
for ele in array:
	arrayH.append(hex(ele));
	
print arrayH
	
handler = open('Hexarray.txt', 'w');
for ele in arrayH:
	handler.write(ele);
	handler.write(" ");
	
handler.close();
arrayT.close()
print "array length: "+ str(len(array));
	
