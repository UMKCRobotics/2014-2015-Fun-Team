import subprocess
import os
import sys
from SConsExtensions import *

#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)
AddOption('--g',action='store_true',help='fetch newest from git and build that',default=False)
AddOption('--ocv',action='store_true',help='build with opencv',default=False)

if GetOption('g'):
	subprocess.check_call(['git','fetch'])
	subprocess.check_call(['git','submodule','foreach','git','fetch'])
env = Environment()
getColorEnvironment(env)

#Sets up an environment object

flags = "-Wall -std=c++0x "
#set up some differences between debug and release
if GetOption('d'):
	flags += "-g"
if GetOption('r'):
	flags += "-O3"
env.Append(CXXFLAGS=flags)

class ObjectCreator:
	build = "build/"
	def __init__(self,src_dir):
		self.src_dir = src_dir
		self.build_dir = ObjectCreator.build + src_dir
	
	def get_objects(self):
		return self.get_objects_alt_scons("SConscript")

	def get_objects_alt_scons(self,scons_file):
		self._copy_to_build_dir()
		return SConscript(self.build_dir+scons_file,exports='env')

	def _copy_to_build_dir(self):
		def make_build_dir(dir):
			subprocess.check_call(["mkdir","--parents",dir])
		def copyanytree(src, dst):
			subprocess.check_call(['rsync','-r',src,dst])
		make_build_dir(self.build_dir)
		copyanytree(self.src_dir ,self.build_dir)
bins = "bins/"

class ProgramBuilder:
	def __init__(self, name, src_dir,env):
		self.name = name
		self.src_dir = src_dir
		self.object_creator = ObjectCreator(src_dir)
		self.env = env
	def build(self):
		self.build_link([])
	def build_link(self,libs):
		print(" I am " + self.name + " " + str(libs))
		self.env.Program(self.name,self.object_creator.get_objects(),LIBS=libs,LIBPATH=bins)
class LibraryBuilder:
	def __init__(self,name,src_dir,env):
		self.name = name
		self.src_dir =src_dir
		self.object_creator = ObjectCreator(src_dir)
		self.env = env
	def build(self):
		self.env.Append(CPPPATH = ['../'+self.src_dir])
		self.env.Library(self.name,self.object_creator.get_objects())



framework = LibraryBuilder(bins+'framework',"lib/2014-2015-Framework/src/",env)
gpio = LibraryBuilder(bins+'gpio',"lib/BeagleBoneBlack-GPIO/src/",env)
dmcc = LibraryBuilder(bins+'dmcc',"lib/DMCC_Library/src/",env)

program = ProgramBuilder('robot_program','src/',env)

OPENCV_FORMATTED_LIBS = []
if GetOption('ocv'):
	#incoming hacky stuff to make openCV link
	OPENCV_FLAGS=subprocess.check_output(['pkg-config','--cflags','opencv'])
	OPENCV_LIBS=subprocess.check_output(['pkg-config','--libs-only-l','opencv'])
	OPENCV_LIBPATH=subprocess.check_output(['pkg-config','--libs-only-L','opencv'])
	env.Append(CCFLAGS=OPENCV_FLAGS)
	env.Append(LIBPATH=OPENCV_FLAGS)

	#this is a mess but it needs to be this way because i haev no better way for
	#string manipulation
	OPENCV_FORMATTED_LIBS = map(lambda a:  a[2:],OPENCV_LIBS.split(" ")[:-2]) + ['tesseract']
	#openCV hacky linking over

if GetOption("clean"):
	subprocess.check_call(['rm','-rf',bins])
	subprocess.check_call(['rm','-rf',"build/"])

if not GetOption("clean"):
	print('Building FRAMEWORK...')
	framework.build()
	print('Building GPIO...')
	gpio.build()
	print('Building DMCC...')
	dmcc.build()
	print('Building PROGRAM...')
	program.build_link(['framework','blacklib','dmcc']+OPENCV_FORMATTED_LIBS)




