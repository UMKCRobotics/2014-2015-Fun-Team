import subprocess

#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)
AddOption('--g',action='store_true',help='fetch newest from git and build that',default=False)

if GetOption('g'):
	subprocess.check_call(['git','fetch'])
	subprocess.check_call(['git','submodule','foreach','git','fetch'])

#Sets up an environment object
env = Environment()

#define some directories and common files
bins = "bins/"
srcs = "src/"
libs = "lib/"
build = "build/"
SConscript_name = "SConscript"
framework_name = "2014-2015-Framework/"
gpio_lib_name = "BeagleBoneBlack-GPIO/"
build_dirs 	= [build+"program/",build+"framework/",build+"gpio/"]
src_dirs	= [srcs,libs+framework_name+srcs,libs+gpio_lib_name+srcs]

zipped_dirs = zip(src_dirs,build_dirs)

#the default flags for all builds
flags = "-Wall "
#set up some differences between debug and release
if GetOption('d'):
	flags += "-g"
if GetOption('r'):
	flags += "-O3"
env.Append(CCFLAGS=flags)

#add the cpp path
env.Append(CPPPATH = ['../framework/','../gpio/'])


#i can't find a better way to do this
def copyanything(src, dst):
	subprocess.check_call(['rsync','-r','-i',src,dst])

def deleteFilesOfType(dir,type):
	subprocess.check_call(['find',dir,"-name","*"+type,"-delete"])

def deleteRecursivelyUnderDir(dir):
	subprocess.check_call(['rm','-rf',dir+"/*"])

if not GetOption("clean"):
	print("Copying Files...")	
	map(lambda zip: copyanything(*zip), zipped_dirs)
	deleteFilesOfType("build",".swp")

if GetOption("clean"):
	map(deleteRecursivelyUnderDir,build_dirs)
	

print("Building Library...")
#build the library
library_objects = SConscript(build+'framework/'+SConscript_name, exports = 'env')
env.Library(bins+'framework',library_objects)

print("Building GPIO library...")
gpio_library_objects = SConscript(build+"gpio/"+SConscript_name,exports='env')
env.Library(bins+"gpio", gpio_library_objects)

print("Building Program...")
#actually build the program
program_objects = SConscript(build+'program/'+SConscript_name, exports= 'env')
env.Program(target = 'robot_program',source=program_objects,LIBS=['framework','gpio'],variant_dir=build+"program",LIBPATH=bins)
