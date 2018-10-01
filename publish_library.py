#! /usr/bin/python3
import sys,os
import shutil
import glob
print(sys.path)
print(sys.argv)

is_no_force = sys.argv.__len__() >1 and sys.argv[1] == "-f"
print("is_no_force",is_no_force)	

dir_path = os.path.dirname(os.path.realpath(__file__))
lib_path ="Release"

if sys.argv.__len__() >2 and sys.argv[2] == "-d":
	lib_path = sys.argv[3] 
	



list_path = [
"g3_io_lib",
"g3_api_library",

]
list_total_files = []
for tmp in list_path:
	list_total_files.extend([ file.replace("\\","/") for file in glob.glob(dir_path+'/'+lib_path+"/"+tmp+".dll") ])
	list_total_files.extend([ file.replace("\\","/") for file in glob.glob(dir_path+'/'+lib_path+"/"+tmp+".lib") ])
	list_total_files.extend([ file.replace("\\","/") for file in glob.glob(dir_path+'/'+lib_path+"/"+tmp+".pdb") ])



print(list_total_files)	
if not is_no_force:
	input("ready to copy?")


#exit()	
dst_path_dll = dir_path+"/publish"
if not os.path.exists(dst_path_dll):
	os.makedirs(dst_path_dll)
	
	
for org_file in list_total_files:
	base_name = os.path.basename(org_file)
	dst_file = dst_path_dll+"/"+base_name	
	print("copy",org_file,"to",dst_file)
	shutil.copy(org_file,dst_file)
	
if not is_no_force:
	input("ok")	

