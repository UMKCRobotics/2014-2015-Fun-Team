
#add debug and release builds
AddOption('--d',action='store_true',help='build a debug build',default=False)
AddOption('--r',action='store_true',help='build a release build',default=False)


#Sets up an environment object
env = Environment()


#the default flags for all builds
flags = "-Wall "
#set up some differences between debug and release
if GetOption('d'):
	flags += "-g"
if GetOption('r'):
	flags += "-O3"
env.Append(CCFLAGS=flags)

#setting the output dir to be build instead, 
#also making it so it doesn't copy the files
env.VariantDir('build/','src/',duplicate=0) 


#add the cpp path
#env.Append(CPPPATH = ['./2014-2015-Framework/lib'])

#build the library
SConscript('lib/2014-2015-Framework/Sconscript',
	exports = 'env')

#actually build the program
SConscript('src/SConscript',
	exports = 'env')
