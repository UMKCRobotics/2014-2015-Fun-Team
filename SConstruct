import subprocess
import os
import sys

#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)
AddOption('--g',action='store_true',help='fetch newest from git and build that',default=False)

if GetOption('g'):
	subprocess.check_call(['git','fetch'])
	subprocess.check_call(['git','submodule','foreach','git','fetch'])


##SETTING UP COLORS
colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s \t\t\t ==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s \t==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s \t\t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s \t\t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

java_library_message = '%sCreating Java Archive %s \t ==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

env = Environment(
  CXXCOMSTR = compile_source_message,
  CCCOMSTR = compile_source_message,
  SHCCCOMSTR = compile_shared_source_message,
  SHCXXCOMSTR = compile_shared_source_message,
  ARCOMSTR = link_library_message,
  RANLIBCOMSTR = ranlib_library_message,
  SHLINKCOMSTR = link_shared_library_message,
  LINKCOMSTR = link_program_message,
  JARCOMSTR = java_library_message,
  JAVACCOMSTR = compile_source_message
)
##END COLORIZER


#Sets up an environment object

#define some directories and common files
bins = "bins/"
srcs = "src/"
libs = "lib/"
build = "build/"
SConscript_name = "SConscript"

	
framework_name = "2014-2015-Framework/"
gpio_lib_name = "BeagleBoneBlack-GPIO/"
DMCC_lib_name = "DMCC_Library/"

build_dirs 	= [build+"program/",build+"framework/",build+"gpio/",build+"dmcc/"]
src_dirs	= [srcs,libs+framework_name+srcs,libs+gpio_lib_name+srcs,libs+DMCC_lib_name+srcs]

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
env.Append(CPPPATH = ['../framework/','../gpio/','../dmcc'])


#i can't find a better way to do this
def copyanytree(src, dst):
	subprocess.check_call(['rsync','-r','-i',src,dst])

def deleteFilesOfType(dir,type):
	subprocess.check_call(['find',dir,"-name","*"+type,"-delete"])

def deleteRecursivelyUnderDir(dir):
	subprocess.check_call(['rm','-rf',dir+"/*"])

if not GetOption("clean"):
	print("Copying Files...")	
	map(lambda zip: copyanytree(*zip), zipped_dirs)
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

print("Building DMCC library...")
dmcc_objs = SConscript(build+'dmcc/'+SConscript_name,exports='env')
env.Library(bins+"dmcc",dmcc_objs)

print("Building Program...")
#actually build the program
program_objects = SConscript(build+'program/'+SConscript_name, exports= 'env')
env.Program(target = 'robot_program',source=program_objects,LIBS=['framework','gpio','dmcc'],LIBPATH=bins)
