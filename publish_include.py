#! /usr/bin/python3
import sys,os
import shutil
import glob
print(sys.path)
print(sys.argv)

is_no_force = sys.argv.__len__() >1 and sys.argv[1] == "-f"
print("is_no_force",is_no_force)	

dir_path = os.path.dirname(os.path.realpath(__file__))
	

list_path = [
"g3_io_lib",
"g3_api_library",

]

list_include=[os.path.join(dir_path,path_,"include").replace("\\","/") for path_ in list_path]	
print(list_include)

list_total_files = []


for inc_file in list_include:
	list_total_files.extend([ file.replace("\\","/") for file in glob.glob(inc_file+"/*.h") ])
	
print(list_total_files)	
if not is_no_force:
	input("ready to copy?")


#exit()	
dst_path = dir_path+"/publish/include"

if not os.path.exists(dst_path):
	os.makedirs(dst_path)
	
	
for org_file in list_total_files:
	base_name = os.path.basename(org_file)
	dst_file = dst_path+"/"+base_name
	print("copy",org_file,"to",dst_file)
	shutil.copy(org_file,dst_file)
	
if not is_no_force:
	input("ok")	

