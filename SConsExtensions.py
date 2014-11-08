import sys
import subprocess


def getColorEnvironment(env):
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

    env.Append(
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


